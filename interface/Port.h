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

struct _Forward;

typedef struct _Forward {
	unsigned short destID;
	unsigned short nextID;
	bool isAlive;
	struct _Forward *next;
} Forward;

#endif
