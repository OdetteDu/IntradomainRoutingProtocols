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
/*
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
                //do nothing
            } else {
                // v does not contain x
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
*/
bool RoutingProtocolImpl::LSUpdate() {
    //Upon reveiving LSP
    sendLSTable();
    //updating the forwading table using Dijkstra's algorithm
    dijkstra();

    
}
                
void RoutingProtocolImpl::dijkstra(){
    //initialization:
    Forwarding.clear();
    map<unsigned short, unsigned short> tempMap；
    /*For all nodes v;
     if v is adjacent to A
     then D(v) = c(A, v)
     else D(v) = infinity
     the algorithm above is kinda hard to achieve
     alternatively, we create a map where all nodes v have D(v) = infinity
     then, change the cost to an adjacent nodes v to c(A,v)
     */
    for(map<unsigned short,Vertice>::iterator _iterator = nodeVec.begin();_iterator != nodeVec.end();_iterator++){
        if(_iterator->first != myID){
            tempMap.insert(std::pair<unsigned short, unsigned short>(_iterator->first, INFINITY_COST));
        }
    }
    for (int i = 0; i < numOfPorts; i++) {
        if (port[i].isAlive) {
            tempMap[port[i].linkTo]->second = port[i].cost;
        }
    }
    /*Loop
    find w not in S such that D(w) is a minimum
    add w to S
    update D(v) for all v adjacent to w and not in S
    unitl all nodes are in S
     */
    //setup a map of not-yet-visited nodes
    map<unsigned short, unsigned short> notVisited;
    notVisited = tempMap;
    notVisited.erase(myID);
    //doing the loop discribed above
    while (!notVisited.empty()) {
        pair<unsigned short, unsigned short> nodeW = nodeIDWithMinDistance(notVisited);
        unsigned short W = nodeW->first;
        unsigned short distanceToW = nodeW->second;
        notVisited.erase(w);
        map<unsigned short, unsigned short> tempNeighbor = nodeVec[w]->second.neighbor;
        for (map<unsigned short, unsigned short>::iterator _iterator = tempNeighbor.begin(); _iterator != tempNeighbor.end(); ++_iterator) {
            if (notVisited.count(_iterator->first)) {
                unsigned short distanceToV = tempMap[_iterator->sfirst]->second;
                unsigned short newDistanceToV = _iterator->second + distanceToW;;
                tempMap[_iterator->first].cost = !(newDistanceToV<distanceToV)?newDistanceToV:distanceToV
            }
        }
    }
    //update the generic forwarding table
    for (map<unsigned short, unsigned short> iterator::_iterator = tempMap.begin(); _iterator != tempMap.end(); ++_iterator) {
        for (int i = 0; i < numOfPorts; i++){
            if (ports[i].isAlive && ports[i].linkTo == _iterator->first) {
                updateForward(_iterator->first, i);
            }
        }
    }
}
//function used to find the minimum cost node
pair<unsigned short, unsigned short> RoutingProtocolImpl::nodeIDWithMinDistance(map<unsigned short, unsigned short> tempMap){
    pair<unsigned short, unsigned short> minPair;
    unsigned short minCost = INFINITY_COST;
    for(map<unsigned short,unsigned short>::iterator _iterator = tempMap.begin();_iterator != tempMap.end();++_iterator){
        if(_iterator->second < minCost) {
            minCost=its->second;
            minPair = _iterator;
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
    char type = LS;
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
            *(short *)(packet + 8) = htonl(sequence_number)
            
            int index = 12;
            for (map<unsigned short, unsigned short> iterator it = _portInfo.begin(); it != _portInfo.end(); it++) {
                unsigned short neighborID = it->first;
                unsigned short newCost = it->second;
                *(short *)(packet + index) = htons(neighborID);
                *(short *)(packet + index + 2) = htons(newCost);
                index += 4;
                
            }
            sys->send(i, packet, size);
        }
    }
}
