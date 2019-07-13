#ifndef CENTRIFUGE_H
#define CENTRIFUGE_H

#include "attraction.h"
#include "globals.h"

const int CF_REFRESH_INTERVAL = 1;

// 4 is an important factor here for the illusion of rotation
const int CF_RIDE_TIME = 15 * CF_REFRESH_INTERVAL;

const int CF_RADIUS = 40;

class Centrifuge : public Attraction {

public:
	Centrifuge(int r, int h, int a, int theta, QBox* qb);


	void handleEvent(const Event& e);
	
	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);


private:

	// if a cabin is empty; we have a NULL pointer
	const Visitor* rider;
	bool hasRider;

	// the moment the wheel starts spinning 
	int startTime;
	int theta;
};


#endif