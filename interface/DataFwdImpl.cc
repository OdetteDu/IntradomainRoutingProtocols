#include "RoutingProtocolImpl.h"

/* find the forwarding entry with destination router ID */
unsigned short RoutingProtocolImpl::findForward(unsigned short dest) {
	if (Forwarding.find(dest) == Forwarding.end())
		return SPECIAL_PORT;
	else
		return Forwarding[dest];
}

/* update a table entry with destination and the next port to reach it
 * if entry doen't exist, a new one will be created
 */
void RoutingProtocolImpl::updateForward(unsigned short destID, unsigned short fwdPort) {
	Forwarding[destID] = fwdPort;
}

/* disable a link in entry (set it as "not alive") */
void RoutingProtocolImpl::disableForward(unsigned short destID) {
	unsigned short fwdPort = findForward(destID);
	if (fwdPort < SPECIAL_PORT)
		Forwarding.erase(destID);
}

/* print the forwarding table */
void RoutingProtocolImpl::printForward() {
	printf("  Forwarding table: \n");
	for (map<unsigned short, unsigned short>::iterator it = Forwarding.begin(); it != Forwarding.end(); it++)
		printf("\tDest: %d, Port: %d\n", it->first, it->second);
}

/* deal with the DATA packet */
void RoutingProtocolImpl::recvDATA(unsigned short port, void *packet, unsigned short size) {
	char *receive = (char *)packet;
	ePacketType type = (ePacketType)(*(char *)packet);
	unsigned short srcID = ntohs(*(unsigned short*)(receive + 4));
	unsigned short destID = ntohs(*(unsigned short*)(receive + 6));
	int i;

	if (type == DATA) { // forward DATA packet
		if (port == SPECIAL_PORT) { // the packet is generated locally
			printf("\tPacket generated locally, destination: %d.\n", destID);
			forwardData(packet, destID, size);
		}
		else { // the packet is from other ports
			if (myID == destID) { // reach destination
				// print data content
				printf("\tReceive data from %d, ", srcID);
				char *payload = receive + 8;
				if (size > 8) {
					printf("payload:\n\t");
					for (i = 0; i < size - 8; i++) {
						printf("%c ", *payload);
						payload++;
					}
				}
				else
					printf("No payload in the message.");
				printf("\n");
				// free the memory
				payload = NULL;
				packet = NULL;
				delete receive;
			}
			else	// for somebody else
				forwardData(packet, destID, size);
		}
	}
}

/* forward DATA packet to a specific destination ID */
void RoutingProtocolImpl::forwardData(void* packet, unsigned short destID, unsigned short size) {
	unsigned short fwdPort = findForward(destID);
	if (fwdPort == SPECIAL_PORT) { // not reachable, free the packet memory
		printf("\tCannot forward the packet (not reachable).\n");
		delete (char*)packet;
	}
	else { // reachable, so forward it
		printf("\tForward the packet through port %d.\n", fwdPort);
		sys->send(fwdPort, packet, size);
	}
}
