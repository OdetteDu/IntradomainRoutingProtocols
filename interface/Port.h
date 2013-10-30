#ifndef PORT_H
#define PORT_H

class Port {
  public:
	unsigned int number;
	unsigned short linkTo;
	unsigned int cost;
	unsigned int update;
	bool isAlive;
};

/*
struct _Forward;

typedef struct _Forward {
	unsigned short destID;
	unsigned short nextID;
	unsigned int nextPort;
	bool isAlive;
	struct _Forward *next;
} Forward;
*/

struct _DVCell;

typedef struct _DVCell {
	unsigned short destID;
	unsigned short nextHopID;
	unsigned int cost;
	unsigned int update;
} DVCell;

#endif
