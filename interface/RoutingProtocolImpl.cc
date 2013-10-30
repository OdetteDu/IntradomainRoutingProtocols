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
    map<short, double> dijkstraMap;
    vector<short> S;
    forwardTableEntry tempEntry;
    
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
    for(map<int,Vertice>::iterator its = nodeVec.begin();its != nodeVec.end();its++){
        if(its->first != sys->id){
            forwardTableEntry[its->first].cost=INFINITY_COST;
        }
    }
    for (map<short, portInfo>::iterator _iterator = nodeVec.begain(); _iterator != nodeVec.end(); ++_iterator) {
        if(!fwdTable.count(its->second.neighborID)){
            tempEntry=forwardTableEntry(its->second.cost, its->second.neighborID, true);
            fwdTable[its->second.neighborID]=cur_record;
        }
        else{
            if(fwdTable[its->second.neighborID].cost>its->second.cost){
                tempEntry=forwardTableEntry(its->second.cost, its->second.neighborID, true);
                fwdTable[its->second.neighborID]=cur_record;
            }
        }
    }
    for (map<short, forwardTableEntry>::iterator _iterator = fwdTable.begain(); _iterator != fwdTable.end(); ++_iterator){
        dijkstraMap[_iterator->first] = _iterator->second.cost;
    }
    /*Loop
    find w not in S such that D(w) is a minimum
    add w to S
    update D(v) for all v adjacent to w and not in S
    unitl all nodes are in S
     */
    //setup a map of not-yet-visited nodes
    map<short, double> notVisited;
    notVisited = dijkstraMap;
    notVisited.erase(sys->myID);
    //doing the loop discribed above
    while (!notVisited.empty()) {
        pair<short, double> nodeW = nodeIDWithMinDistance(notVisited);
        short W = nodeW->first;
        double distanceToW = nodeW->second;
        notVisited.erase(w);
        map<int, portInfo> tempNeighbor = nodeVec[w].neighbor;
        for (map<int, portInfo>::iterator _iterator = tempNeighbor.begin(); _iterator != tempNeighbor.end(); ++_iterator) {
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



