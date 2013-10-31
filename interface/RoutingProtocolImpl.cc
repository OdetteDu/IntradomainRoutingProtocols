#include "RoutingProtocolImpl.h"

RoutingProtocolImpl::RoutingProtocolImpl(Node *n) : RoutingProtocol(n) {
  sys = n;
  // add your own code
}

RoutingProtocolImpl::~RoutingProtocolImpl() {
  // add your own code (if needed)
}

void RoutingProtocolImpl::init(unsigned short num_ports, unsigned short router_id, eProtocolType protocol_type) {
  // add your own code
}

void RoutingProtocolImpl::handle_alarm(void *data) {
  // add your own code
}

void RoutingProtocolImpl::recv(unsigned short port, void *packet, unsigned short size) {
  // add your own code
      //START Cheng-------------------------------------------------------------------------
    package *p = (package *)packet;
    if(packet->type == LSP){
        int LS_change=0;
        map<int,Vertice> * passVec=(map<int,Vertice> *)(p->table);
        for(map<int,Vertice>::iterator its = passVec->begin();its != passVec->end();its++){
            if(!nodeVec.count(its->second.NodeID)){
                nodeVec[its->second.NodeID]=its->second;
                nodeVec[its->second.NodeID].sequence_number=sim->global_time;
                LS_change=1;
                
            }
            else if(its->second.sequence_number>nodeVec[its->second.NodeID].sequence_number){
                nodeVec[its->second.NodeID]=its->second;
                nodeVec[its->second.NodeID].sequence_number=sim->global_time;
                LS_change=1;
                
            }
        }
        
        
        if(LS_change==1){
            void *nodeVec_2= &(nodeVec);
            for(int k = 0; k < port_status.size(); k++){
                int dst = port_status[k].neiNodeID;
                if(dst!=port){
                    p = new package(4,12,sys->id,dst,0,nodeVec_2);
                    sys->send(k,p,sizeof(struct package));
                }
            }
        }
    }
    //END Cheng------------------------------------------------------------------------------
}

// add more of your own code
/*----------------------------------------------- TODO: for Cheng Wan--------------------------------------------------*/

void RoutingProtocolImpl::init_forwarding_table(){
    queue<Node *> q;
    vector<int> visited;
    vector<Node *> curNei;
    q.push(sys);
    visited.push_back(sys->id);
    Forwarding_record cur_record;
    while(!q.empty()){
        Node * cur=q.front();
        q.pop();
        curNei=getNeibor(cur);
        for(std::vector<Node *>::iterator it = curNei.begin(); it != curNei.end(); ++it) {
            if(std::find(visited.begin(), visited.end(), (*it)->id) != visited.end()) {
                /* v contains x *///do nothing
            } else {
                /* v does not contain x */
                cout<<"node id is"<<(*it)->id<<endl;
                if(!forwarding_table.count((*it)->id)){
                    cur_record=Forwarding_record(INFINITY_COST, -1, false);
                    forwarding_table[(*it)->id]=cur_record;
                }
                visited.push_back((*it)->id);
                q.push(*it);
            }
        }
    }
    
}
bool RoutingProtocolImpl::updateLS() {
    //Upon reveiving LSP
    packet *p;
    Vertice v;
    v= Vertice( sim->global_time, sys->id);
    v.neighbors=port_status;
    v.sequence = sim->global_time;
    nodeVec[sys->id]=v;
    
    void *nodeVec2= &(nodeVec);
    
    for(int i=0; i<sys->link_vector.size();i++){
        if((sys->link_vector[i])->get_is_alive()){
            p = new package(4,12,sys->id,-1,(int)sys->time(),nodeVec2);
            sys->send(i, p, sizeof(struct package));
        }
        
    }
    //updating the forwading table using Dijkstra's algorithm
    dijkstra();

    
}
                
void RoutingProtocolImpl::dijkstra(){
    //initialization:
    map<unsigned short, double> dijkstraMap;
    vector<unsigned short> S;
    forwardTableEntry tempEntry;
    map<unsigned short, unsigned short> newForwarding;
    //S={A}
    S.push_back(sys->myID);
    /*For all nodes v;
     if v is adjacent to A
     then D(v) = c(A, v)
     else D(v) = infinity
     the algorithm above is kinda hard to achieve
     alternatively, we create a map where all nodes v have D(v) = infinity
     then, change the cost to an adjacent nodes v to c(A,v)
     */
    for(map<unsigned short,Vertice>::iterator its = nodeVec.begin();its != nodeVec.end();its++){
        if(its->first != sys->id){
            forwardTableEntry[its->first].cost=INFINITY_COST;
        }
    }
    for (map<unsigned short, portInfo>::iterator _iterator = nodeVec.begain(); _iterator != nodeVec.end(); ++_iterator) {
        if(!fwdTable.count(its->second.neighborID)){
            tempEntry=forwardTableEntry(_iterator->second.cost, _iterator->second.neighborID, true);
            fwdTable[_iterator->second.neighborID]=tempEntry;
        }
        else{
            if(fwdTable[its->second.neighborID].cost>its->second.cost){
                tempEntry=forwardTableEntry(_iterator->second.cost, _iterator->second.neighborID, true);
                fwdTable[_iterator->second.neighborID]=tempEntry;
            }
        }
    }
    for (map<unsigned short, forwardTableEntry>::iterator _iterator = fwdTable.begain(); _iterator != fwdTable.end(); ++_iterator){
        dijkstraMap[_iterator->first] = _iterator->second.cost;
    }
    /*Loop
    find w not in S such that D(w) is a minimum
    add w to S
    update D(v) for all v adjacent to w and not in S
    unitl all nodes are in S
     */
    //setup a map of not-yet-visited nodes
    map<unsigned short, double> notVisited;
    notVisited = dijkstraMap;
    notVisited.erase(sys->myID);
    //doing the loop discribed above
    while (!notVisited.empty()) {
        pair<unsigned short, double> nodeW = nodeIDWithMinDistance(notVisited);
        unsigned short W = nodeW->first;
        double distanceToW = nodeW->second;
        notVisited.erase(w);
        map<unsigned short, portInfo> tempNeighbor = nodeVec[w].neighbor;
        for (map<unsigned short, portInfo>::iterator _iterator = tempNeighbor.begin(); _iterator != tempNeighbor.end(); ++_iterator) {
            if (notVisited.count(_iterator->second.neighborID)) {
                double distanceToV = fwdTable[_iterator->second.neighborID].cost;
                double newDistanceToV = _iterator->second.cost + distanceToW;;
                fwdTable[_iterator->first].cost = !(newDistanceToV<distanceToV)?newDistanceToV:distanceToV
            }
        }
    }
}
//function used to find the minimum cost node
pair<short, double> RoutingProtocolImpl::nodeIDWithMinDistance(map<short, double> tempMap){
    pair<short, double> minPair;
    double minCost = INFINITY_COST;
    for(map<int,double>::iterator _iterator = tempMap.begin();_iterator != tempMap.end();++_iterator){
        if(_iterator->second < minCost) {
            minCost=its->second;
            min=_iterator;
        }
    }
    
    return minPair;
    
}

// set the alarm to mark inactive nodes
void RoutingProtocolImpl::setInactiveAlarm() {
	sys->set_alarm(this, 45000, (void*) alarm_inactive);
}


void RoutingProtocolImpl::sendLSTable(){
    //prepare creation of a P_LS packet
    char type = P_LS;
    unsigned short size;
    unsigned short sourceId = myID;
    
    map<unsigned short, unsigned short> _portInfo;
    //get neighbors
    for (int i = 0; i < numOfPorts; i++) {
        if (port[i].isAlive) {
            _portInfo.insert(port[i].linkTo, port[i].cost);
        }
    }

    int sequence_number = sys->time();
    size = 12 + (_portInfo.size() * 4);
    
    for (int i = 0; i < numOfPorts; i++) {
        if (port[i].isAlive) {
            char * packet = (char *) malloc(sizeof(char) * size);
            *packet = type;
            *(short *)(packet + 2) = htons(size);
            *(short *)(packet + 4) = htons(sourceId);
            *(short *)(packet + 8) = htons(sequence_number)
            
            int index = 12;
            for (map<unsigned short, unsigned short> iterator it = _portInfo.begin(); it != _portInfo.end(); it++) {
                unsigned short neighborID = it->first;
                unsigned short newCost = it->second;
                *(short *)(packet + index) = htons(neighborID);
                *(short *)(packet + index) = htons(newCost);
                index += 4;
                
            }
            sys->send(i, packet, size);
        }
    }
}
