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

	if (nodeVec.find(srcID) == nodeVec.end()) {
		// add this new vertice
		Vertice toAdd;
		toAdd.NodeID = srcID;
		toAdd.sequence = seq;
		// insert the cost message in the packet to local vertice
		for (i = 0; i < size - 12; i += 4) {
			unsigned short nID = ntohs(*(unsigned short*)(pck + 12 + i));
			unsigned short cost = ntohs(*(unsigned short*)(pck + 14 + i));
			toAdd.neighbor.insert(pair<unsigned short, unsigned short>(nID, cost));
		}
		nodeVec.insert(pair<unsigned short, Vertice>(srcID, toAdd));
		// flood this packet
		sendReceivedLSPck(port, pck, size);
	}
	else if (nodeVec[srcID].sequence < seq) {
		// update this vertice
		Vertice *v = &nodeVec[srcID];
		v->sequence = seq;
		v->neighbor.clear();
		// insert the cost message in the packet to local vertice
		for (i = 0; i < size - 12; i += 4) {
			unsigned short nID = ntohs(*(unsigned short*)(pck + 12 + i));
			unsigned short cost = ntohs(*(unsigned short*)(pck + 14 + i));
			v->neighbor.insert(pair<unsigned short, unsigned short>(nID, cost));
		}
		// flood this packet
		sendReceivedLSPck(port, pck, size);
	}

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
    //initialization:
    Forwarding.clear();
    map<unsigned short, unsigned short> tempMap;
    /*For all nodes v;
     if v is adjacent to A
     then D(v) = c(A, v)
     else D(v) = infinity
     the algorithm above is kinda hard to achieve
     alternatively, we create a map where all nodes v have D(v) = infinity
     then, change the cost to an adjacent nodes v to c(A,v)
     */
    for(map<unsigned short,Vertice>::iterator _iterator = nodeVec.begin();_iterator != nodeVec.end();_iterator++){
        if(_iterator->first != myID){
            tempMap.insert(std::pair<unsigned short, unsigned short>(_iterator->first, INFINITY_COST));
        }
    }
    for (int i = 0; i < numOfPorts; i++) {
        if (ports[i].isAlive) {
            tempMap[ports[i].linkTo] = ports[i].cost;
        }
    }
    /*Loop
    find w not in S such that D(w) is a minimum
    add w to S
    update D(v) for all v adjacent to w and not in S
    unitl all nodes are in S
     */
    //setup a map of not-yet-visited nodes
    map<unsigned short, unsigned short> notVisited;
    notVisited = tempMap;
    notVisited.erase(myID);
    //doing the loop discribed above
    while (!notVisited.empty()) {
        pair<unsigned short, unsigned short> nodeW = nodeIDWithMinDistance(notVisited);
        unsigned short W = nodeW.first;
        unsigned short distanceToW = nodeW.second;
        notVisited.erase(W);
        map<unsigned short, unsigned short> tempNeighbor = nodeVec[W].neighbor;
        for (map<unsigned short, unsigned short>::iterator _iterator = tempNeighbor.begin(); _iterator != tempNeighbor.end(); ++_iterator) {
            if (notVisited.count(_iterator->first)) {
                unsigned short distanceToV = tempMap[_iterator->first];
                unsigned short newDistanceToV = _iterator->second + distanceToW;
                tempMap[_iterator->first] = !(newDistanceToV<distanceToV) ? newDistanceToV : distanceToV;
            }
        }
    }

    //update the generic forwarding table
    for (map<unsigned short, unsigned short>::iterator _iterator = tempMap.begin(); _iterator != tempMap.end(); ++_iterator) {
        for (int i = 0; i < numOfPorts; i++){
            if (ports[i].isAlive && ports[i].linkTo == _iterator->first) {
                updateForward(_iterator->first, i);
            }
        }
    }
}

//function used to find the minimum cost node
pair<unsigned short, unsigned short> RoutingProtocolImpl::nodeIDWithMinDistance(map<unsigned short, unsigned short> tempMap){
    unsigned short minID = -1;
    unsigned short minCost = INFINITY_COST;
    for(map<unsigned short,unsigned short>::iterator its = tempMap.begin(); its != tempMap.end(); ++its){
        if(its->second <= minCost) {
	    minID = its->first;
            minCost = its->second;
        }
    }
    
    return pair<unsigned short, unsigned short>(minID, minCost);
    
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

    int sequence_number = sys->time();
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
		if (sys->time() - v.sequence >= 45000)
			nodeVec.erase(v.NodeID);
	}
}
