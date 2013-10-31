#include "RoutingProtocolImpl.h"

bool RoutingProtocolImpl::LSUpdate() {
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
			for (int j = 0; i < size - 12; j += 4) {
				*(unsigned short*)(toSend+12+j) = *(unsigned short*)(packet + 12 + j);
				*(unsigned short*)(toSend+14+j) = *(unsigned short*)(packet + 14 + j);
			}
			sys->send(i, toSend, size);
		}
}

void RoutingProtocolImpl::checkLSExp() {
	for (map<unsigned short, Vertice>::iterator it = nodeVec.begin(); it != nodeVec.end(); it++) {
		Vertice v = it->second;
		if (sys->time() - v.sequence >= 45000)
			nodeVec.erase(v.NodeID);
	}
}
