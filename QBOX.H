#ifndef QBOX_H
#define QBOX_H

#include "gp142display.h"
#include "visitorqueue.h"

#include <math.h>


// this class implements a visual view of a queue
// vertical, horizontal and even diagonal queue boxes should work
class QBox {

public:
	// construct a new QBox using given mid points position at each end of the q
	QBox(int r, int h, int a, int theta, int q_length);

	// set the queue that I am visualizing to a given one. Should be called only once
	// before simulation is started
	void setQueue(VisitorQueue* vq);

	// paint the queue and its contents skipping a given number of visitors in the
	// head of the queue
	void paint(GP142Display& display, int visitorsToSkip = 0) const;


private:
	VisitorQueue* vq;

	int r,h,a,theta,length;
	int q_length; // in pixels
};

#endif