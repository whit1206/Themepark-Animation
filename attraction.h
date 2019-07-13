#ifndef ATTRACTION_H
#define ATTRACTION_H

#include "parkelement.h"
#include "qbox.h"

// Attractions are abstract ParkElements with a queue
class Attraction : public ParkElement {

public:
	Attraction(int r, int h, int a, QBox* qb);
	~Attraction();
	virtual void setXY();

protected:
	VisitorQueue vq;
	QBox* qb;

	// coordinates of the attraction on the screen
	int a,r,h,x,y;
};

#endif