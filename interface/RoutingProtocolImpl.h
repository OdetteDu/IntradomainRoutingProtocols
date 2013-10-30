#ifndef ROUTINGPROTOCOLIMPL_H
#define ROUTINGPROTOCOLIMPL_H

#include "RoutingProtocol.h"

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
    struct package{
        char type;
        unsigned short size;
        unsigned short srcid;
        unsigned short dstid;
        int data;
        void *table;
        package(){};
        package(char type, unsigned short size, unsigned short srcid, unsigned short dstid, int data, void *table):type(type),size(size),srcid(srcid),dstid(dstid),data(data),table(table){};
    };

    struct Vertice{
        int sequence;
        unsigned short NodeID;
        map<unsigned short,portInfo> neighbor;
        Vertice(){};
        Vertice(int sequence, short NodeID) : sequence(sequence), NodeID(NodeID){};
    };
    struct forwardTableEntry{
        double cost;
        unsigned short nextHop;
        bool adjacency;
        forwardTableEntry() : cost(0), nextHop(0), direct(false){};
        forwardTableEntry(double cost, unsigned short nextHop, bool adjacency) : cost(cost), nextHop(nextHop), adjacency(adjacency){};
    };
    struct portInfo{
        unsigned short neighborID;
        double cost;
        portInfo(){};
        portInfo(short neighborID, double cost) : neighborID(neighborID), cost(cost){};
    };
    map<unsigned short, forwardTableEntry> fwdTable;
    map<unsigned short, Vertice> nodeVec;
    map<unsigned short,portInfo> portStatus;
    
    int sequence

 private:
    Node *sys; // To store Node object; used to access GSR9999 interfaces 
};

#endif

