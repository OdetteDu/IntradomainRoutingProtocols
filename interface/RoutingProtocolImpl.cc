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
}

	/*EDIT: by Yanfei Wu */

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
	int count = 
	while ()
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
	return true;
}

/* TODO: for Cheng Wan*/
bool RoutingProtocolImpl::LSUpdate() {
	return true;
}
