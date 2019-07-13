#ifndef ROLLERCOASTER_H
#define ROLLERCOASTER_H

#include "attraction.h"
#include "globals.h"

const int RC_CAPACITY = 4;

const int RC_REFRESH_INTERVAL = 1;

// 4 is an important factor here for the illusion of rotation
const int RC_RIDE_TIME = 15 * RC_REFRESH_INTERVAL * RC_CAPACITY;

class Rollercoaster : public Attraction {

public:
	Rollercoaster(int r, int h, int a, int theta, QBox* qb);


	void handleEvent(const Event& e);
	
	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);


private:

	// if a cabin is empty; we have a NULL pointer
	const Visitor* riders[RC_CAPACITY];
	int riderCount;

	int carPos[RC_CAPACITY];

	int theta;

	// the moment the the cart gets filled up 
	int startTime;
};


#endif