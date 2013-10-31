#include "RoutingProtocolImpl.h"

bool RoutingProtocolImpl::LSUpdate() {
	sendLSTable();
	dijkstra();
	return true;
}

void RoutingProtocolImpl::recvLS(unsigned short port, void *packet, unsigned short size) {
	char *pck = (char *)packet;
	unsigned short srcID = ntohs(*(unsigned short*)(pck + 4));
	unsigned int seq = ntohl(*(unsigned int*)(pck + 8));
	int i;

	printf("  receive LS table: from %d, sequence: %d\n", srcID, seq);

	if (nodeVec.find(srcID) == nodeVec.end()) {
		printf("  This is a new LS table:\n");
		// add this new vertice
		Vertice toAdd;
		toAdd.NodeID = srcID;
		toAdd.sequence = seq;
		toAdd.update = sys->time();
		// insert the cost message in the packet to local vertice
		for (i = 0; i < size - 12; i += 4) {
			unsigned short nID = ntohs(*(unsigned short*)(pck + 12 + i));
			unsigned short cost = ntohs(*(unsigned short*)(pck + 14 + i));
			printf("\tnode ID: %d, cost: %d\n", nID, cost);
			toAdd.neighbor.insert(pair<unsigned short, unsigned short>(nID, cost));
		}
		nodeVec.insert(pair<unsigned short, Vertice>(srcID, toAdd));
		// flood this packet
		sendReceivedLSPck(port, pck, size);
	}
	else if (nodeVec[srcID].sequence < seq) {
		printf("  Update existed LS table: (old seq: %d; new seq: %d)\n", nodeVec[srcID].sequence, seq);
		// update this vertice
		Vertice *v = &nodeVec[srcID];
		v->sequence = seq;
		v->neighbor.clear();
		v->update = sys->time();
		// insert the cost message in the packet to local vertice
		for (i = 0; i < size - 12; i += 4) {
			unsigned short nID = ntohs(*(unsigned short*)(pck + 12 + i));
			unsigned short cost = ntohs(*(unsigned short*)(pck + 14 + i));
			printf("\tnode ID: %d, cost: %d\n", nID, cost);
			v->neighbor.insert(pair<unsigned short, unsigned short>(nID, cost));
		}
		// flood this packet
		sendReceivedLSPck(port, pck, size);
	}
	else
		printf("  This is an old LS table. Ignore it.\n");

	packet = NULL;
	delete pck;
}

void RoutingProtocolImpl::sendReceivedLSPck(unsigned short port, char *packet, unsigned short size) {
	for (int i = 0; i < numOfPorts; i++)
		if (i != port) {
			char *toSend = (char*)malloc(sizeof(char) * size);
			*toSend = LS;
			*(unsigned short*)(toSend+2) = htons(size);
			*(unsigned short*)(toSend+4) = *(unsigned short*)(packet+4);
			*(unsigned int*)(toSend+8) = *(unsigned int*)(packet+8);
			for (int j = 0; j < size - 12; j += 4) {
				*(unsigned short*)(toSend+12+j) = *(unsigned short*)(packet + 12 + j);
				*(unsigned short*)(toSend+14+j) = *(unsigned short*)(packet + 14 + j);
			}
			sys->send(i, toSend, size);
		}
}

void RoutingProtocolImpl::dijkstra(){
	set<unsigned short> visited;				// nodes that have been visited
	set<unsigned short> visiting;				// nodes that will be visited
	map<unsigned short, unsigned short> reachable;		// reachable nodes: nodeID -> port number
	map<unsigned short, unsigned short> curCost;		// the cost of reachable nodes: nodeID -> cost
	int i;
	set<unsigned short>::iterator seti;			// set interator
	map<unsigned short, unsigned short>::iterator mapi;	// map interator

	// construct initial maps
	visited.insert(myID);
	for (i = 0; i < numOfPorts; i++)
		if (ports[i].isAlive) {
			unsigned short nID = ports[i].linkTo;
			unsigned short nCost = ports[i].cost;
			if (nodeVec.find(nID) != nodeVec.end())	// neighbors that have Vertice table should be in visiting set
				visiting.insert(nID);			
			reachable.insert(pair<unsigned short, unsigned short>(nID, i));
			curCost.insert(pair<unsigned short, unsigned short>(nID, nCost));
		}

	// Dijkstra Algorithm
	while (!visiting.empty()) {
		unsigned short minCost = INFINITY_COST;		// minimal cost to the current visited node
		unsigned short curVisit;			// current visited node
		// get the node that is in visiting set and also has the shortest cost
		for (seti = visiting.begin(); seti != visiting.end(); seti++)
			if (curCost[*seti] < minCost) {
				minCost = curCost[*seti];
				curVisit = *seti;
			}
		// move current visited node into visited set
		visiting.erase(curVisit);
		visited.insert(curVisit);

		Vertice *v = &nodeVec[curVisit];
		for (mapi = v->neighbor.begin(); mapi != v->neighbor.end(); mapi++) {
			if (visited.find(mapi->first) == visited.end()) {	// not in visited set
				if (curCost.find(mapi->first) == curCost.end()) {
					// never reached before
					curCost.insert(pair<unsigned short, unsigned short>(mapi->first, minCost + mapi->second));
					reachable.insert(pair<unsigned short, unsigned short>(mapi->first, reachable[curVisit]));
					if (nodeVec.find(mapi->first) != nodeVec.end())
						visiting.insert(mapi->first);	// add to visiting set if it's possible
				}
				else if (curCost[mapi->first] > minCost + mapi->second) {
					// update the cost and nexthop
					curCost[mapi->first] = minCost + mapi->second;
					reachable[mapi->first] = reachable[curVisit];
				}
			}
		}
	}

    	//update the generic forwarding table
	Forwarding.clear();
    	for (mapi = reachable.begin(); mapi != reachable.end(); mapi++) {
		updateForward(mapi->first, mapi->second);
	}
}

void RoutingProtocolImpl::sendLSTable(){
    //prepare creation of a P_LS packet
    char type = LS;
    unsigned short size;
    unsigned short sourceId = myID;
    
    map<unsigned short, unsigned short> _portInfo;
    //get neighbors
    for (int i = 0; i < numOfPorts; i++) {
        if (ports[i].isAlive) {
            _portInfo.insert(pair<unsigned short, unsigned short>(ports[i].linkTo, ports[i].cost));
        }
    }

    int sequence_number = mySequence;
    mySequence++;
    size = 12 + (_portInfo.size() * 4);
    
	bool printed = false;
    for (int i = 0; i < numOfPorts; i++) {
        if (ports[i].isAlive) {
		printf("\tSend LS table to port %d.\n", i);
            char * packet = (char *) malloc(sizeof(char) * size);
            *packet = type;
            *(short *)(packet + 2) = htons(size);
            *(short *)(packet + 4) = htons(sourceId);
            *(int *)(packet + 8) = htonl(sequence_number);
            
            int index = 12;
            for (map<unsigned short, unsigned short>::iterator it = _portInfo.begin(); it != _portInfo.end(); it++) {
                unsigned short neighborID = it->first;
                unsigned short newCost = it->second;
		if (!printed)
			printf("neighbor ID: %d, cost: %d\n", neighborID, newCost);
                *(short *)(packet + index) = htons(neighborID);
                *(short *)(packet + index + 2) = htons(newCost);
                index += 4;
            }
		printed = true;
            sys->send(i, packet, size);
        }
    }
}

void RoutingProtocolImpl::checkLSExp() {
	for (map<unsigned short, Vertice>::iterator it = nodeVec.begin(); it != nodeVec.end(); it++) {
		Vertice v = it->second;
		if (sys->time() - v.update >= 45000)
			nodeVec.erase(v.NodeID);
	}
}
