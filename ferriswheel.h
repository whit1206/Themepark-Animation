#ifndef FERRISWHEEL_H
#define FERRISWHEEL_H

#include "attraction.h"
#include "globals.h"

const int FW_CAPACITY = 10;

const int FW_REFRESH_INTERVAL = 1;

// 4 is an important factor here for the illusion of rotation
const int FW_RIDE_TIME = 15 * FW_REFRESH_INTERVAL *  FW_CAPACITY;

const int FW_RADIUS = 40;

// this class implements a FerrisWheel that can serve several customers simultaneously
class FerrisWheel : public Attraction {

public:
	FerrisWheel(int r, int h, int a, int theta, QBox* qb);

	void handleEvent(const Event& e);
	
	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);


private:

	// if a cabin is empty; we have a NULL pointer
	const Visitor* riders[FW_CAPACITY];
	int riderCount, theta;

	// the moment the wheel starts spinning 
	int startTime;
};


#endif