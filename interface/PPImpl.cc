#include "RoutingProtocolImpl.h"

/* Deal with PING or PONG packet */
void RoutingProtocolImpl::recvPP(unsigned short port, void *packet, unsigned short size) {
	char *receive = (char *)packet;
	ePacketType type = (ePacketType)(*(char *)packet);
	unsigned short srcID = ntohs(*(unsigned short*)(receive + 4));

	if (type == PING) {	// received a PING packet
		char *pongpackage = (char *)malloc(12 * sizeof(char));
		ePacketType pongtype = PONG;
		*pongpackage = pongtype;				//packet type
		*(unsigned short *)(pongpackage+2) = htons(12);		// size
		*(unsigned short *)(pongpackage+4) = htons(myID);	// sourceID is my ID
		*(unsigned short *)(pongpackage+6) = htons(srcID);	// destinationID is the sender's ID
		*(int *)(pongpackage+8) = *(int*)(receive + 8);		// time stamp
		printf("\tReceive PING: from port %d, source: %d, time stamp: %d\n", port, 
			srcID, ntohl(*(int *)(receive + 8)));
		sys->send(port,pongpackage, 12);
	} else if (type == PONG) {	// received a PONG packet
		unsigned int currentTime = sys->time();
		unsigned int startsendtime = ntohl(*(int*)(receive + 8));
		unsigned int duration = currentTime - startsendtime;
		// update port status
		bool isChange = false;
		if (ports[port].linkTo != srcID) {
			isChange = true;
			ports[port].linkTo = srcID;
		}
		if (ports[port].cost != duration) {
			isChange = true;
			ports[port].cost = duration;
		}
		ports[port].update = currentTime;
		if (!ports[port].isAlive) {
			isChange = true;
			ports[port].isAlive = true;
		}
		printf("\tReceive PONG: from port %d, source: %d, duration: %d, time: %d\n",
			port, srcID, duration, currentTime);

		// LS mode: send LS table if this port state is changed
		if (protocol == P_LS && isChange)
			sendLSTable();

		// update forwarding table if it's a new link
		if (findForward(srcID) == SPECIAL_PORT)
			updateForward(srcID, port);
	}
	
	// free memory
	packet = NULL;
	delete receive;
}

/* send ping-pong message to update costs of neighbours */
bool RoutingProtocolImpl::handlePP() {
	printf("  Node %d: pingpong message!\n", myID);
	
	int count = numOfPorts;
	while (count > 0){
		//ports[count] do something
		count--;
		//----------------------------making ping package---------------
		char *pingpackage = (char*)malloc(12 * sizeof(char));
		*pingpackage = PING;						//packet type
		*(unsigned short *)(pingpackage+2) = htons(12); 		//size
		*(unsigned short *)(pingpackage+4) = htons(myID); 		//sourceID
		*(int *)(pingpackage+8) = htonl(sys->time()); 			//time stamp
		//----------------------------end making------------------------
		sys->send(count, pingpackage, 12);
		printf("\tSend PING to port: %d, time stamp: %d\n", count, sys->time());
	}
	return true;
}
