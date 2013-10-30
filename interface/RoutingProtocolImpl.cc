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

	/* END EDIT: Yanfei Wu */
}

RoutingProtocolImpl::~RoutingProtocolImpl() {
	/* EDIT: by Yanfei Wu */
	// free the memory allocated for ports and forwarding table
	if (ports != NULL)
		delete[] ports;
	Forwarding.clear();

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
	}
	/* END EDIT: Yanfei Wu */
}

void RoutingProtocolImpl::recv(unsigned short port, void *packet, unsigned short size) {
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
	unsigned short srcID = ntohs(*(unsigned short*)(receive + 4));

	if (type == PING) {
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
	} else if (type == PONG) {
		unsigned int currentTime = sys->time();
		unsigned int startsendtime = ntohl(*(int*)(receive + 8));
		unsigned int duration = currentTime - startsendtime;
		// update port status
		ports[port].linkTo = srcID;
		ports[port].cost = duration;
		ports[port].update = currentTime;
		ports[port].isAlive = true;
		printf("\tReceive PONG: from port %d, source: %d, duration: %d, time: %d\n",
			port, srcID, duration, currentTime);
		// update forwarding table if it's a new link
		if (findForward(srcID) == SPECIAL_PORT)
			updateForward(srcID, port);
	}
	
	// free memory
	packet = NULL;
	delete receive;
}

void RoutingProtocolImpl::recvDV(unsigned short port, void *packet, unsigned short size)
{
	char *pck = (char *)packet;
	unsigned short sourceId = ntohs(*(short*)(pck + 4));
	bool isChange = false;
	int i;

	printf("\treceive from %d\n", sourceId);

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
			isChange = true;
			DVMap[sourceId].destID = sourceId;
			DVMap[sourceId].cost = ports[portNumber].cost;
			DVMap[sourceId].nextHopID = myID;
			DVMap[sourceId].update = sys->time();
		}
		else
		{
			printf("The sourceId is neither in DVMap nor in Ports");
			return;
		}
	}

	for (i=0; i< size/4 - 2; i++)
	{
		unsigned short nodeId = ntohs(*(short*)(pck + 8 + i*4));
		unsigned short cost = ntohs(*(short*)(pck + 10 + i*4));
		isChange = updateDVTable(nodeId, cost, sourceId) | isChange;
	}

	for (map<unsigned short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); it++) {
		DVCell dvc = it->second;
		if (dvc.nextHopID == sourceId && dvc.update < sys->time()) {
			isChange = true;
			DVMap.erase(dvc.destID);
			//determine if there is direct link
			for (i = 0; i < numOfPorts; i++)
				if (ports[i].isAlive && ports[i].linkTo == dvc.destID) {					
					DVCell newCell;
					newCell.cost = ports[i].cost;
					newCell.destID = dvc.destID;
					newCell.nextHopID = myID;
					newCell.update = sys->time();
					DVMap.insert(pair<unsigned short, DVCell>(dvc.destID, newCell));
					break;
				}
		}
	}

	if (isChange) {
		sendDVUpdateMessage();
		updateForwardUsingDV();
	}
	else
		printf("\trecvDV: nothing happens.\n");

	packet = NULL;
	delete(pck);
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
	
bool RoutingProtocolImpl::updateDVTable(unsigned short nodeId, unsigned short cost, unsigned short sourceId)
{
	if (nodeId == myID || cost == INFINITY_COST)
		return false;

	unsigned int newCost = cost + DVMap[sourceId].cost;
	if(DVMap.find(nodeId)==DVMap.end() || DVMap[nodeId].cost > newCost)
	{
		//update the table
		DVCell newCell;
		newCell.destID = nodeId;
		newCell.nextHopID = sourceId;
		newCell.cost = newCost;
		newCell.update = sys->time();
		DVMap[nodeId] = newCell;
		return true;
	}
	else {
		DVMap[nodeId].update = sys->time();
		return false;
	}
}

void RoutingProtocolImpl::sendDVUpdateMessage()
{
	for(int i=0; i<numOfPorts; i++)
	{
		if(ports[i].isAlive)
		{
			char type = DV;
			unsigned short size = 8 + DVMap.size()*4;
			unsigned short sourceId = myID;
			unsigned short destinationId = ports[i].linkTo; 
	
			//put the message in a packet
			char * packet = (char *)malloc(sizeof(char) * size);
			*packet = type;
			*(short *)(packet+2) = ntohs(size);
			*(short *)(packet+4) = ntohs(sourceId);
			*(short *)(packet+6) = ntohs(destinationId);

			int index = 8;
			for (map<unsigned short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); ++it)
			{
				DVCell newCell = it->second;
				short nodeId = newCell.destID;
				short cost;
				if(ports[i].linkTo == newCell.nextHopID)
				{
					cost = INFINITY_COST;
				}
				else
				{
					cost = newCell.cost;
				}
				*(short *)(packet+index) = ntohs(nodeId);
				*(short *)(packet+index+2) = ntohs(cost);
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
	int i;
	for (i = 0; i < numOfPorts; i++)
		if (ports[i].isAlive && sys->time() - ports[i].update >= 15000) {
			ports[i].isAlive = false;
			disableForward(ports[i].linkTo);
		}

	bool isChange = false;
	for(map<unsigned short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); ++it)
	{		
		DVCell dvc = it->second;
		if (sys->time() - dvc.update >= 45000) {
			isChange = true;
			DVMap.erase(dvc.destID);
			for (i = 0; i < numOfPorts; i++)
				if (ports[i].isAlive && ports[i].linkTo == dvc.destID) {					
					DVCell newCell;
					newCell.cost = ports[i].cost;
					newCell.destID = dvc.destID;
					newCell.nextHopID = myID;
					newCell.update = sys->time();
					DVMap.insert(pair<unsigned short, DVCell>(dvc.destID, newCell));
					break;
				}
		}
	}

	if (isChange) {
		printf("\tDV table has been updated. Flood the change.\n");
		sendDVUpdateMessage();
		updateForwardUsingDV();
	}

	return true;
}

/* send ping-pong message to update costs of neighbours */
bool RoutingProtocolImpl::handlePP() {
	printf("  Node %d: pingpong message!\n", myID);
	/* TODO: for Kai Wu*/
	
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
unsigned short RoutingProtocolImpl::findForward(unsigned int dest) {
	if (Forwarding.find(dest) == Forwarding.end())
		return SPECIAL_PORT;
	else
		return Forwarding[dest];
}

/* update a table entry with destination and the next port to reach it
 * if entry doen't exist, a new one will be created
 */
void RoutingProtocolImpl::updateForward(unsigned short destID, unsigned int fwdPort) {
	Forwarding[destID] = fwdPort;
}

/* disable a link in entry (set it as "not alive") */
void RoutingProtocolImpl::disableForward(unsigned int destID) {
	unsigned short fwdPort = findForward(destID);
	if (fwdPort < SPECIAL_PORT)
		Forwarding.erase(destID);
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
/* print the forwarding table */
void RoutingProtocolImpl::printForward() {
	printf("  Forwarding table: \n");
	for (map<unsigned short, unsigned short>::iterator it = Forwarding.begin(); it != Forwarding.end(); it++)
		printf("\tDest: %d, Port: %d\n", it->first, it->second);
}

/* END EDIT: Yanfei Wu */

/* TODO: for Yang Du*/
void RoutingProtocolImpl::updateForwardUsingDV()
{
	map<unsigned short, unsigned int> portTable; //of destId nextPort

	for(int i=0; i<numOfPorts; i++)
		if (ports[i].isAlive)
			portTable.insert(pair<unsigned short, unsigned int>(ports[i].linkTo, ports[i].number));
	
	Forwarding.clear();
	for (map<unsigned short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); ++it)
	{
		DVCell dv = it->second;
		if (dv.nextHopID == myID)
			updateForward(dv.destID, portTable[dv.destID]);
		else
			updateForward(dv.destID, portTable[dv.nextHopID]);
	}
	printForward();
	printf("  print DV:\n");
	for(map<unsigned short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); ++it)
	{
		DVCell dvc = it -> second;
		printf("  DestID: %d, Cost: %d, NextHop: %d, update: %d\n", dvc.destID, dvc.cost, dvc.nextHopID, dvc.update);
	}
}

bool RoutingProtocolImpl::DVUpdate() {
	
	int i;
	map<unsigned short, unsigned int> directConnection;

	for(i=0; i<numOfPorts; i++)
	{
		if(ports[i].isAlive)
		{
			directConnection.insert(pair<unsigned short, unsigned int>(ports[i].linkTo, ports[i].cost));
		}
	}
	
	//for all the ports
	for(i=0; i<numOfPorts; i++)
	{	
		Port port = ports[i];
		if(port.isAlive)
		{	
			if (DVMap.find(ports[i].linkTo) == DVMap.end()) {
				DVCell newCell;
				newCell.cost = ports[i].cost;
				newCell.destID = ports[i].linkTo;
				newCell.nextHopID = myID;
				newCell.update = sys->time();
				DVMap.insert(pair<unsigned short, DVCell>(ports[i].linkTo, newCell));
			}
			else {
				//did the cost change?
				DVCell *dv = &DVMap[ports[i].linkTo];
				dv->update = sys->time();

				//save the old cost
				unsigned int oldCost = dv->cost;

				if(dv->nextHopID != myID)
				{
					  if(dv->cost > ports[i].cost)
					  {
						//update to use the direct link
						dv->cost = ports[i].cost;
						dv->nextHopID = myID;
					  }
					  else
						    continue;
				}
				else if (oldCost == ports[i].cost)
					continue;

				//update the direct node to the new cost
				dv->cost = ports[i].cost;
				//find all the nextHop with the direct Node
				for(map<unsigned short, DVCell>::iterator it = DVMap.begin(); it!=DVMap.end(); ++it)
				{
					DVCell *c = &(it->second);
					if(c->nextHopID == ports[i].linkTo)
					{
						//minus the old cost add the new cost
						c->cost -= oldCost;
						c->cost += ports[i].cost;
						c->update = sys->time();

						//determine if the new cost is higher than the direct Node
						if(directConnection.find(c->destID) != directConnection.end()
							&& directConnection[c->destID] < c->cost)
						{
							  c->nextHopID = myID;
							  c->cost = directConnection[c->destID];
						}
					}
				}
			}
		}
		else
		{
			for(map<unsigned short, DVCell>::iterator iter = DVMap.begin(); iter!=DVMap.end(); ++iter)
			{
				DVCell dvc = iter -> second;
				if(dvc.nextHopID == myID && directConnection.find(dvc.destID)==directConnection.end())
				{
					//remove all the disconnected Node
					DVMap.erase(dvc.destID);
					//remove all the entry with nextHopID==disconnected node
					for(map<unsigned short, DVCell>::iterator it = DVMap.begin(); it!=DVMap.end(); ++it)
					{
						DVCell c = it->second;
						if(c.nextHopID == dvc.destID)
						{
							DVMap.erase(c.destID);
							//determine if there is direct link
							if(directConnection.find(c.destID) != directConnection.end())
							{
								DVCell newCell;
								newCell.cost = directConnection[c.destID];
								newCell.destID = c.destID;
								newCell.nextHopID = myID;
								newCell.update = sys->time();
								DVMap.insert(pair<unsigned short, DVCell>(c.destID, newCell));
							}
						}
					}
				}
			}
		}
	}

	sendDVUpdateMessage();
	updateForwardUsingDV();
	return true;
}

/* TODO: for Cheng Wan*/
bool RoutingProtocolImpl::LSUpdate() {
	return true;
}
