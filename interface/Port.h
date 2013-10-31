#ifndef PORT_H
#define PORT_H

#include <map>

class Port {
  public:
	unsigned short number;
	unsigned short linkTo;
	unsigned int cost;
	unsigned int update;
	bool isAlive;
};

struct _DVCell;

typedef struct _DVCell {
	unsigned short destID;
	unsigned short nextHopID;
	unsigned int cost;
	unsigned int update;
} DVCell;

struct _Vertice;

typedef struct _Vertice {
        unsigned int sequence;
        unsigned short NodeID;
        map<unsigned short, unsigned short> neighbor;
} Vertice;

#endif
