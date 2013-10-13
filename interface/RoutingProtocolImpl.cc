#include "RoutingProtocolImpl.h"

RoutingProtocolImpl::RoutingProtocolImpl(Node *n) : RoutingProtocol(n) {
  sys = n;
  // add your own code
}

RoutingProtocolImpl::~RoutingProtocolImpl() {
  // add your own code (if needed)
}

void RoutingProtocolImpl::init(unsigned short num_ports, unsigned short router_id, eProtocolType protocol_type) {
	/* EDIT: by Yanfei Wu */
	// remenber informations for this rounter
	protocol = protocol_type;
	numOfPorts = num_ports;
	myID = router_id;
	alarm_exp = new char[1];
	alarm_pp = new char[1];
	alarm_update = new char[1];
	alarm_exp[0] = 'e';
	alarm_pp[0] = 'p';
	alarm_update[0] = 'u';

	// set the expiration checking alarm
	sys->set_alarm(this, 900, (void*) alarm_exp);

	// set the ping-pong alarm
	sys->set_alarm(this, 10000, (void*) alarm_pp);

	// set the update alarm
	sys->set_alarm(this, 30000, (void*) alarm_update);
	/* END EDIT: Yanfei Wu */
}

void RoutingProtocolImpl::handle_alarm(void *data) {
	/* EDIT: by Yanfei Wu */
	char type = *(char*)data;
	switch (type) {
	case 'e':
		printf("Node %d: expiration checking! time: %d\n\n", myID, sys->time());
		break;
	case 'p':
		printf("Node %d: pingpong message! time: %d\n\n", myID, sys->time());
		break;
	case 'u':
		printf("Node %d: protocol update! time: %d\n\n", myID, sys->time());
		break;
	default:
		printf("Node %d: something goes wrong!!! time: %d\n\n", myID, sys->time());
		break;
	}
	/* END EDIT: Yanfei Wu */
}

void RoutingProtocolImpl::recv(unsigned short port, void *packet, unsigned short size) {
  // add your own code
}

// add more of your own code
