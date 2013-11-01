#include "RoutingProtocolImpl.h"

void RoutingProtocolImpl::recvDV(unsigned short port, void *packet, unsigned short size)
{
	char *pck = (char *)packet;
	unsigned short sourceId = ntohs(*(short*)(pck + 4));
	bool isChange = false;
	int i;
	printf("\treceive from %d\n", sourceId);

	int portNumber = -1;
	for(int j=0; j<numOfPorts; j++)
		if(ports[j].linkTo == sourceId) {
			portNumber = j;
			break;
		}

	if(DVMap.find(sourceId) == DVMap.end())
	{
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
	/*
	else if (portNumber > -1 && ports[portNumber].cost < DVMap[sourceId].cost) {
		isChange = true;
		DVMap[sourceId].destID = sourceId;
		DVMap[sourceId].cost = ports[portNumber].cost;
		DVMap[sourceId].nextHopID = myID;
		DVMap[sourceId].update = sys->time();
	}*/

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
	
	/*
	for (i = 0; i < numOfPorts; i++)
		if (ports[i].isAlive) {
			if (DVMap.find(ports[i].linkTo) == DVMap.end()) {
				DVMap[ports[i].linkTo].destID = ports[i].linkTo;
				DVMap[ports[i].linkTo].cost = ports[i].cost;
				DVMap[ports[i].linkTo].nextHopID = myID;
				DVMap[ports[i].linkTo].update = sys->time();
			}
			else if (DVMap[ports[i].linkTo].nextHopID != myID && DVMap[ports[i].linkTo].cost >= ports[i].cost) {
				
			}			
		}
	*/
	if (isChange)
		DVUpdate();
	else
		printf("\trecvDV: nothing happens.\n");

	packet = NULL;
	delete(pck);
}

bool RoutingProtocolImpl::updateDVTable(unsigned short nodeId, unsigned short cost, unsigned short sourceId)
{
	if (nodeId == myID || cost == INFINITY_COST)
		return false;

	unsigned int newCost = cost + DVMap[sourceId].cost;
	if(DVMap.find(nodeId)==DVMap.end() || DVMap[nodeId].cost > newCost
		|| (DVMap[nodeId].nextHopID == sourceId && newCost != DVMap[nodeId].cost))
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
			*(short *)(packet+2) = htons(size);
			*(short *)(packet+4) = htons(sourceId);
			*(short *)(packet+6) = htons(destinationId);

			int index = 8;
			for (map<unsigned short, DVCell>::iterator it = DVMap.begin(); it != DVMap.end(); ++it)
			{
				DVCell newCell = it->second;
				unsigned short nodeId = newCell.destID;
				unsigned short cost;
				if(ports[i].linkTo == newCell.nextHopID)
				{
					cost = INFINITY_COST;
				}
				else
				{
					cost = newCell.cost;
				}
				*(short *)(packet+index) = htons(nodeId);
				*(short *)(packet+index+2) = htons(cost);
				index += 4;
			}

			sys -> send(ports[i].number, packet, size);
		}
	}
}

void RoutingProtocolImpl::updateForwardUsingDV()
{
	map<unsigned short, unsigned int> portTable; //of destId nextPort

	for(int i=0; i<numOfPorts; i++)
		if (ports[i].isAlive)
			portTable.insert(pair<unsigned short, unsigned short>(ports[i].linkTo, ports[i].number));
	
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

	updateForwardUsingDV();
	sendDVUpdateMessage();
	return true;
}
