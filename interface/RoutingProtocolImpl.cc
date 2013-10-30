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
/* END EDIT: Yanfei Wu */

/* TODO: for Cheng Wan*/
bool RoutingProtocolImpl::LSUpdate() {
	return true;
}
