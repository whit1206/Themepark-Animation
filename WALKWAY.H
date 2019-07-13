#ifndef WALKWAY_H
#define WALKWAY_H

#include "parkelement.h"
#include "globals.h"

// pixels per tick
const int WALK_SPEED = 4;

// refresh picture every n ticks
const int WALKWAY_REFRESH_INTERVAL = 1;

// this class implements a walkway - a park element that connects two other park 
// elements. Walkways can compute positions of their visitors at any given moment.
// This allows for nice animation
class WalkWay : public ParkElement {

public:

	WalkWay(int startR, int startH, int startA, int endR, int endH, int endA);

	void paint(GP142Display& display) const;

	void handleEvent(const Event& e);

	void acceptVisitor(Visitor* v);
	void setXY();


private:
	// screen position; also determine the direction of the walkway
	int endX, endY, startX, startY,	endR, endH, endA, startR, startH, startA;

	// how much time it takes to walk this walkway
	int timeToWalk;

	// current number of walkers on the walkway
	int walkerCount;

	// walkers are in FIFO order
	Visitor* walkers[MAX_PARK_OCCUPANCY];

	// how much time each walker has been walking on this walkway
	int walkerTimes[MAX_PARK_OCCUPANCY];

	// since our queue is implemented as an array we need to know where the head is
	// we use one head for both walkers[] and walkerTimes[]
	int head;
};

#endif