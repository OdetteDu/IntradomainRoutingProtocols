#ifndef ROUTINGPROTOCOLIMPL_H
#define ROUTINGPROTOCOLIMPL_H

#include "RoutingProtocol.h"
#include "Node.h"
#include "Port.h"
#include <map>

using namespace std;

class RoutingProtocolImpl : public RoutingProtocol {
  public:
    RoutingProtocolImpl(Node *n);
    ~RoutingProtocolImpl();

    void init(unsigned short num_ports, unsigned short router_id, eProtocolType protocol_type);
    // As discussed in the assignment document, your RoutingProtocolImpl is
    // first initialized with the total number of ports on the router,
    // the router's ID, and the protocol type (P_DV or P_LS) that
    // should be used. See global.h for definitions of constants P_DV
    // and P_LS.

    void handle_alarm(void *data);
    // As discussed in the assignment document, when an alarm scheduled by your
    // RoutingProtoclImpl fires, your RoutingProtocolImpl's
    // handle_alarm() function will be called, with the original piece
    // of "data" memory supplied to set_alarm() provided. After you
    // handle an alarm, the memory pointed to by "data" is under your
    // ownership and you should free it if appropriate.

    void recv(unsigned short port, void *packet, unsigned short size);
    // When a packet is received, your recv() function will be called
    // with the port number on which the packet arrives from, the
    // pointer to the packet memory, and the size of the packet in
    // bytes. When you receive a packet, the packet memory is under
    // your ownership and you should free it if appropriate. When a
    // DATA packet is created at a router by the simulator, your
    // recv() function will be called for such DATA packet, but with a
    // special port number of SPECIAL_PORT (see global.h) to indicate
    // that the packet is generated locally and not received from 
    // a neighbor router.

 private:
    Node *sys; // To store Node object; used to access GSR9999 interfaces
	/* EDIT: by Yanfei Wu */
	/* variables */
	// currently using protocol
	eProtocolType protocol;

	// number of ports in this router
	unsigned short numOfPorts;

	// router ID
	unsigned short myID;

	// data for distinguishing types of alarm
	char* alarm_exp;	// expiration checking
	char* alarm_pp;		// ping-pong update
	char* alarm_update;	// protocol update

	// port informations
	Port *ports;

	// forwarding table informations
	Forward *forwards;

	map<short,DVCell> DVMap;

	// end time for the system
	// just for testing, will be removed
	unsigned int endTime;

	/* functions */
	// set the expiration checking alarm
	void setExpAlarm();
	// set the ping-pong message alarm
	void setPPAlarm();
	// set the protocol update alarm
	void setUpdateAlarm();

	// handle the expiration checking alarm; return true if succeed
	bool handleExp();
	// handle the ping-pong message alarm; return true if succeed
	bool handlePP();
	// handle the protocol update alarm; return true if succeed
	bool handleUpdate();

	// update status (tables) for Distance Vector Protocol
	bool DVUpdate();
	// update status (tables) for Link State Protocol
	bool LSUpdate();

	// initialize all ports
	void initPorts(int number);

	// find forwarding entry
	Forward* findForward(unsigned int dest);
	// update table entry
	void updateForward(unsigned short destID, unsigned short nextID, unsigned int nextPort);
	// disable a link in entry
	void disableForward(unsigned int destID);
	// forward DATA packet
	void forwardData(void* packet, unsigned short destID, unsigned short size);
	// free forwarding table
	void freeForward(Forward* toFree);

	// Deal with the DATA packet
	void recvDATA(unsigned short port, void *packet, unsigned short size);
	// Deal with PING or PONG packet
	void recvPP(unsigned short port, void *packet, unsigned short size);
	
	/* END EDIT: Yanfei Wu */

	void recvDV(unsigned short port, void *packet, unsigned short size);
	void updateDVTable(unsigned short nodeId, unsigned short cost, unsigned short sourceId);
	void sendDVUpdateMessage();
	void updateForwardUsingDV();
};

#endif

