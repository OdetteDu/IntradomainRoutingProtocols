#include "RoutingProtocolImpl.h"

RoutingProtocolImpl::RoutingProtocolImpl(Node *n) : RoutingProtocol(n) {
	sys = n;

	// initialize messages for alarm
	alarm_exp = new char[1];
	alarm_pp = new char[1];
	alarm_update = new char[1];
	alarm_exp[0] = 'e';
	alarm_pp[0] = 'p';
	alarm_update[0] = 'u';

	// port list
	ports = NULL;
}

RoutingProtocolImpl::~RoutingProtocolImpl() {
	// free the memory allocated for ports and forwarding table
	if (ports != NULL)
		delete[] ports;
	Forwarding.clear();

	// free the memory allocated for alarm messages
	delete[] alarm_exp;
	delete[] alarm_pp;
	delete[] alarm_update;
}

void RoutingProtocolImpl::init(unsigned short num_ports, unsigned short router_id, eProtocolType protocol_type) {
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
}

void RoutingProtocolImpl::handle_alarm(void *data) {
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
		recvLS(port, packet, size);
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
	bool isChange = false;
	/* check expiration of port status */
	for (i = 0; i < numOfPorts; i++)
		if (ports[i].isAlive && sys->time() - ports[i].update >= 15000) {
			isChange = true;
			ports[i].isAlive = false;
			disableForward(ports[i].linkTo);
		}
	// LS mode: send LS table if port status has changed
	if (protocol == P_LS && isChange)
		sendLSTable();

	/* check expiration of DV status */
	isChange = false;
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

	/* check expiration of LS status */
	checkLSExp();

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
