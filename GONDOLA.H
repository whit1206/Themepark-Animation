#ifndef GONDOLA_H
#define GONDOLA_H

#include "attraction.h"
#include "globals.h"

const int GD_CAPACITY = 4;

const int GD_REFRESH_INTERVAL = 1;

const int GD_RIDE_TIME = 160;

class Gondola : public Attraction {

public:
	Gondola(int r, int h, int a, QBox* qb);

	void handleEvent(const Event& e);
	
	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);


private:

	// if a cabin is empty; we have a NULL pointer
	const Visitor* riders[GD_CAPACITY];
	int riderCount;

	// the moment the wheel starts spinning 
	int startTime;
	bool initialized;
};


#endif