#include "RoutingProtocolImpl.h"

RoutingProtocolImpl::RoutingProtocolImpl(Node *n) : RoutingProtocol(n) {
	sys = n;

	/* EDIT: by Yanfei Wu */
	// initialize messages for alarm
	alarm_exp = new char[1];
	alarm_pp = new char[1];
	alarm_update = new char[1];
	alarm_exp[0] = 'e';
	alarm_pp[0] = 'p';
	alarm_update[0] = 'u';

	// port list
	ports = NULL;

	// forwarding table
	forwards = NULL;

	// time for ending the simulation (just for testing)
	endTime = 30000;

	/* END EDIT: Yanfei Wu */
}

RoutingProtocolImpl::~RoutingProtocolImpl() {
	/* EDIT: by Yanfei Wu */
	// free the memory allocated for ports and forwarding table
	if (ports != NULL)
		delete[] ports;
	if (forwards != NULL)
		freeForward(forwards);

	// free the memory allocated for alarm messages
	delete[] alarm_exp;
	delete[] alarm_pp;
	delete[] alarm_update;
	/* END EDIT: Yanfei Wu */
}

void RoutingProtocolImpl::init(unsigned short num_ports, unsigned short router_id, eProtocolType protocol_type) {
	/* EDIT: by Yanfei Wu */
	// remenber informations for this rounter
	protocol = protocol_type;
	numOfPorts = num_ports;
	myID = router_id;

	// initialize all the ports and forwarding table
	initPorts(numOfPorts);

	// set the first expiration checking alarm
	setExpAlarm();

	// set the first ping-pong alarm
	setPPAlarm();

	// set the first protocol update alarm
	setUpdateAlarm();
	/* END EDIT: Yanfei Wu */
}

void RoutingProtocolImpl::handle_alarm(void *data) {
	/* EDIT: by Yanfei Wu */
	if (sys->time() <= endTime) {	// this restriction is merely for testing

		char type = *(char*)data;
		switch (type) {
		case 'e':
			handleExp();
			setExpAlarm();		// finish expiration work, reset the alarm
			break;
		case 'p':
			handlePP();
			setPPAlarm();		// finish sending ping-pong message, reset the alarm
			break;
		case 'u':
			handleUpdate();
			setUpdateAlarm();	// finish update protocol tables, reset the alarm
			break;
		default:
			printf("Node %d:\n\t***Error*** Unknown alarm occurs\n\ttime: %d\n\n", myID, sys->time());
			break;
		} // end switch (type)

	} // end: if (sys->time() < endTime)
	/* END EDIT: Yanfei Wu */
}

void RoutingProtocolImpl::recv(unsigned short port, void *packet, unsigned short size) {
	// TODO: for EVERYONE!
	char type = *(char*)packet;
	switch (type)
	{
	case DATA:
		recvDATA(port, packet, size);
		break;
	case PING:
	case PONG:
		recvPP(port, packet, size);
		break;
	case DV:
		recvDV(port, packet, size);
		break;
	case LS:
		break;
	default:
		printf("Port %d:\n\t***Error*** Unknown packet occurs\n\ttime: %d\n\n", port, sys->time());
		break;
	}
}

/* Deal with PING or PONG packet */
void RoutingProtocolImpl::recvPP(unsigned short port, void *packet, unsigned short size) {
	char *receive = (char *)packet;
	ePacketType type = (ePacketType)(*(char *)packet);
	unsigned short srcID = *(unsigned short*)(receive + 4);

	if (type == PING) {
		char *pongpackage = (char *)malloc(12 * sizeof(char));
		ePacketType pongtype = PONG;
		*pongpackage = pongtype;			//packet type
		*(unsigned short *)(pongpackage+2) = 12;	// size
		*(unsigned short *)(pongpackage+4) = myID;	// sourceID is my ID
		*(unsigned short *)(pongpackage+6) = srcID;	// destinationID is the sender's ID
		*(int *)(pongpackage+8) = *(int*)(receive + 8);	// time stamp
		printf("\tReceive PING: from port %d, source: %d, time stamp: %d\n", port, 
			srcID, *(int *)(receive + 8));
		sys->send(port,pongpackage,size);
	} else if (type == PONG) {
		int currentTime = sys->time();
		int startsendtime = *(int*)(receive + 8);
		int duration = currentTime - startsendtime;
		// update port status
		ports[port].linkTo = srcID;
		ports[port].cost = duration;
		ports[port].update = currentTime;
		ports[port].isAlive = true;
		printf("\tReceive PONG: from port %d, source: %d, duration: %d, time: %d\n",
			port, srcID, duration, currentTime);
	}
	
	// free memory
	packet = NULL;
	delete receive;
}

void RoutingProtocolImpl::recvDV(unsigned short port, void *packet, unsigned short size)
{
	char *pck = (char *)packet;
	short packetSize = *(short*)(pck + 2);
	short sourceId = *(short*)(pck + 4);
	pck = pck+8;

	if(DVMap.find(sourceId)==DVMap.end())
	{
		int portNumber = -1;
		for(int j=0; j<numOfPorts; j++)
		{
			  if(ports[j].linkTo == sourceId)
			  {
				  portNumber = j;
				  break;
			  }
		 }

		if (portNumber != -1)
		{
			  
				DVMap[sourceId].destID = sourceId;
				DVMap[sourceId].cost = ports[portNumber].cost;
				DVMap[sourceId].nextHopID = myID;
		}
		else
		{
			printf("The sourceId is neither in DVMap nor in Ports");
			  return;
		}
	}

	for(int i=0; i<packetSize/4-2; i++)
	{
		short nodeId = *(short*)(pck + i*4);
		short cost = *(short*)(pck + 2 + i*4);
		updateDVTable(nodeId, cost, sourceId);
	}

	sendDVUpdateMessage();
	
	packet = NULL;
	delete(pck);
}

/* deal with the DATA packet */
void RoutingProtocolImpl::recvDATA(unsigned short port, void *packet, unsigned short size) {
	char *receive = (char *)packet;
	ePacketType type = (ePacketType)(*(char *)packet);
	unsigned short srcID = *(unsigned short*)(receive + 4);
	unsigned short destID = *(unsigned short*)(receive + 6);
	int i;

	if (type == DATA) { // forward DATA packet
		if (port == SPECIAL_PORT) { // the packet is generated locally
			printf("\tPacket generated locally, destination: %d.\n", destID);
			forwardData(packet, destID, size);
		}
		else { // the packet is from other ports
			if (myID == destID) { // reach destination
				// print data content
				printf("\tReceive data from %d, payload:\n\t", srcID);
				char *payload = receive + 8;
				for (i = 0; i < size - 8; i++) {
					printf("%c ", *payload);
					payload++;
				}
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
	
void RoutingProtocolImpl::updateDVTable(unsigned short nodeId, unsigned short cost, unsigned short sourceId)
{
	int newCost = cost + DVMap[sourceId].cost;
	if(DVMap.find(nodeId)==DVMap.end() && DVMap[nodeId].cost>newCost)
	{
		//update the table
		DVCell newCell;
		newCell.destID = nodeId;
		newCell.nextHopID = sourceId;
		newCell.cost = newCost;
		DVMap[nodeId] = newCell;
	}
}

void RoutingProtocolImpl::sendDVUpdateMessage()
{
	for(int i=0; i<numOfPorts; i++)
	{
		if(ports[i].isAlive)
		{
			char type = DV;
			short size = 8 + DVMap.size()*4;
			short sourceId = myID;
			short destinationId = ports[i].linkTo; 
	
			//put the message in a packet
			char * packet = (char *)malloc(sizeof(char) * size);
			*packet = type;
			*(short *)(packet+2) = size;
			*(short *)(packet+4) = sourceId;
			*(short *)(packet+6) = destinationId;

			int index = 8;
			for (map<short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); ++it)
			{
				DVCell newCell = it -> second;
				short nodeId = newCell.destID;
				short cost = newCell.cost;
				*(short *)(packet+index) = nodeId;
				*(short *)(packet+index+2) = cost;
				index += 4;
			}

			sys -> send(ports[i].number, packet, size);
		}
	}
}

/* set the alarm for expiration checking */
void RoutingProtocolImpl::setExpAlarm() {
	sys->set_alarm(this, 900, (void*) alarm_exp);
}

/* set the alarm for sending ping-pong message */
void RoutingProtocolImpl::setPPAlarm() {
	sys->set_alarm(this, 10000, (void*) alarm_pp);
}

/* set the alarm for updating protocol informations */
void RoutingProtocolImpl::setUpdateAlarm() {
	sys->set_alarm(this, 30000, (void*) alarm_update);
}

/* check every expiration (link failure, table update, etc.) */
bool RoutingProtocolImpl::handleExp() {
	printf("Node %d: expiration checking! time: %d\n\n", myID, sys->time());
	return true;
}

/* send ping-pong message to update costs of neighbours */
bool RoutingProtocolImpl::handlePP() {
	printf("Node %d: pingpong message! time: %d\n\n", myID, sys->time());
	/* TODO: for Kai Wu*/
	
	int count = numOfPorts;
	while (count > 0){
		//ports[count] do something
		count--;
		//----------------------------making ping package---------------
		char *pingpackage = (char*)malloc(12 * sizeof(char));
		*pingpackage = PING;					//packet type
		*(unsigned short *)(pingpackage+2) = 12; 		//size
		*(unsigned short *)(pingpackage+4) = myID; 			//sourceID
		*(int *)(pingpackage+8) = sys->time(); 				//time stamp
		//----------------------------end making------------------------
		sys->send(count, pingpackage, 12);
		printf("\tSend PING to port: %d, time stamp: %d\n", count, sys->time());
	}
	return true;
}

/* update status of protocol tables (depends on DV or LS)*/
bool RoutingProtocolImpl::handleUpdate() {
	printf("Node %d: protocol update! time: %d\n\n", myID, sys->time());
	if (protocol == P_DV)
		return DVUpdate();
	else if (protocol == P_LS)
		return LSUpdate();
	else
		printf("Node %d:\n\t***Error*** Unknown protocl when handling update\n\ttime: %d\n\n",
				myID, sys->time());

	return false;
}

/* initialize the list of ports */
void RoutingProtocolImpl::initPorts(int number) {
	ports = new Port[number];
	for (int i = 0; i < number; i++) {
		ports[i].number = i;
		ports[i].linkTo = 0;
		ports[i].cost = INFINITY_COST;
		ports[i].update = -1;
		ports[i].isAlive = false;
	}
}

/* find the forwarding entry with destination router ID */
Forward* RoutingProtocolImpl::findForward(unsigned int dest) {
	Forward* ret = forwards;
	while (ret != NULL) {
		if (ret->destID == dest)
			return ret;
		else
			ret = ret->next;
	}
	return NULL;
}

/* update a table entry with destination and the next router to get to it
 * if entry doen't exist, a new one will be created
 */
void RoutingProtocolImpl::updateForward(unsigned short destID, unsigned short nextID, unsigned int nextPort) {
	Forward* fw = findForward(destID);
	if (fw == NULL) {
		fw = new Forward;
		fw->destID = destID;
		fw->nextID = nextID;
		fw->nextPort = nextPort;
		fw->isAlive = true;
		fw->next = forwards;
		forwards = fw;
	}
	else {
		fw->destID = destID;
		fw->nextID = nextID;
		fw->nextPort = nextPort;
		fw->isAlive = true;
	}
}

/* disable a link in entry (set it as "not alive") */
void RoutingProtocolImpl::disableForward(unsigned int destID) {
	Forward* fw = findForward(destID);
	if (fw != NULL)
		fw->isAlive = false;
}

/* forward DATA packet to a specific destination ID */
void RoutingProtocolImpl::forwardData(void* packet, unsigned short destID, unsigned short size) {
	Forward *destEntry = findForward(destID);
	if (destEntry == NULL) { // not reachable, free the packet memory
		printf("\tCannot forward the packet (not reachable).\n");
		delete (char*)packet;
	}
	else { // reachable, so forward it
		printf("\tForward the packet through port %d.\n", destEntry->nextPort);
		sys->send(destEntry->nextPort, packet, size);
	}
}

/* a recursive function to free memory of forwarding table */
void RoutingProtocolImpl::freeForward(Forward* toFree) {
	if (toFree->next == NULL)
		delete toFree;
	else {
		freeForward(toFree->next);
		delete toFree;
	}
	toFree = NULL;
}

/* END EDIT: Yanfei Wu */

/* TODO: for Yang Du*/
bool RoutingProtocolImpl::DVUpdate() {
	
	int i;
	map<short, int> directConnection;

	for(i=0; i<numOfPorts; i++)
	{
		if(ports[i].isAlive)
		{
			directConnection.insert(pair<short, int>(ports[i].linkTo, ports[i].cost));
		}
	}

	//for all the ports, 
	for(i=0; i<numOfPorts; i++)
	{	
		Port port = ports[i];
		if(port.isAlive)
		{
			//did the cost change?
			DVCell *dv = &DVMap[ports[i].linkTo];

			//save the old cost
			int oldCost = dv->cost;

			if(dv->nextHopID != myID)
			{
				  if(dv->cost > ports[i].cost)
				  {
					    //update to use the direct link
						dv->cost = ports[i].cost;
						dv->nextHopID = myID;
				  }
				  else
				  {
					    continue;
				  }
			}
			//update the direct node to the new cost
			dv->cost = ports[i].cost;
			//find all the nextHop with the direct Node
			for(map<short, DVCell>::iterator it = DVMap.begin(); it!=DVMap.end(); ++it)
			{
				DVCell c = it->second;
				if(c.nextHopID == ports[i].linkTo)
				{
					//minus the old cost add the new cost
					c.cost -= oldCost;
					c.cost += ports[i].cost;

					//determine if the new cost is higher than the direct Node
					if(directConnection[c.destID] < c.cost)
					{
						  c.nextHopID = myID;
						  c.cost = directConnection[c.destID];
					}
				}
			}
		}
		else
		{
			for(map<short, DVCell>::iterator iter = DVMap.begin(); iter!=DVMap.end(); ++iter)
			{
				DVCell dvc = iter -> second;
				if(dvc.nextHopID == myID && directConnection.find(dvc.destID)!=directConnection.end())
				{
					//remove all the disconnected Node
					DVMap.erase(dvc.destID);
					//remove all the entry with nextHopID==disconnected node
					for(map<short, DVCell>::iterator it = DVMap.begin(); it!=DVMap.end(); ++it)
					{
						DVCell c = it->second;
						if(c.nextHopID == dvc.destID)
						{
							DVMap.erase(c.destID);
						}
					}
				}
			}
		}
	}

	return true;
}

/* TODO: for Cheng Wan*/
bool RoutingProtocolImpl::LSUpdate() {
	return true;
}
