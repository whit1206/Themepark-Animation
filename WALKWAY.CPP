#include <math.h>
#include <assert.h>

#include "walkway.h"
#include "eventscheduler.h"

WalkWay::WalkWay(int startR, int startH, int startA, int endR, int endH, int endA) {
	this->startR = startR;
	this->startH = startH;
	this->startA = startA;
	this->endR = endR;
	this->endH = endH;
	this->endA = endA;
	
	setXY();
	int length = (int) sqrt((endX-startX) * (endX-startX) + (endY-startY) * (endY-startY));
	timeToWalk = length / WALK_SPEED;
	walkerCount = 0;
	head = 0;
}

void WalkWay::setXY()
{
	endX = (int)(endR * sin((endA + viewdegree)*PI/180));
	startX = (int)(startR * sin((startA + viewdegree)*PI/180));
	endY = (int)(endH*cos((viewangle)*PI/180) + endR /global_y_ratio * cos((endA + viewdegree)*PI/180));
	startY = (int)(startH*cos((viewangle)*PI/180) + startR /global_y_ratio * cos((startA + viewdegree)*PI/180));
}


void WalkWay::paint(GP142Display& display) const {

	int Xb = (int)(endR * sin((endA + viewdegree)*PI/180));
	int Xa = (int)(startR * sin((startA + viewdegree)*PI/180));
	int Yb = (int)((endH-FONT_SIZE/2)*cos((viewangle)*PI/180) + endR /global_y_ratio * cos((endA + viewdegree)*PI/180));
	int Ya = (int)((startH-FONT_SIZE/2)*cos((viewangle)*PI/180) + startR /global_y_ratio * cos((startA + viewdegree)*PI/180));
	
	
	display.drawLine((int)(Xa*zoom_factor), (int)((Ya)*zoom_factor), 
		(int)(Xb*zoom_factor), (int)((Yb)*zoom_factor), Blue);

	int tail = head + walkerCount;
	//display.write(Xa, Ya, walkerCount, Black, FONT_SIZE);
	for (int i=head; i<tail; i++) {
		int index = i % MAX_PARK_OCCUPANCY;
		
		int x = Xa + (Xb - Xa) * walkerTimes[index] / timeToWalk;
		int y = Ya + (Yb - Ya) * walkerTimes[index] / timeToWalk;
		GP142Color color;
		if(walkers[index]->getSex())
			 color = Pink;
		else color = Blue;
		display.write((int)(x*zoom_factor), (int)((y)*zoom_factor), walkers[index]->getName(), color, (int)(FONT_SIZE*zoom_factor));
	}
}


void WalkWay::acceptVisitor(Visitor* v) {

	assert(0<=walkerCount && walkerCount <= MAX_PARK_OCCUPANCY);
	int index = (head + walkerCount) % MAX_PARK_OCCUPANCY;
	walkers[index] = v;
	walkerTimes[index] = 0;
	walkerCount++;
	
	// ask for refresh events only if not receiving them already
	if (walkerCount == 1)
		generateNewEvent(WALKWAY_REFRESH_INTERVAL);
}


void WalkWay::handleEvent(const Event& e) {

	assert(walkerCount > 0); // no events should be sent to me otherwise

	int tail = head + walkerCount;
	for (int i=head; i<tail; i++) {
		// wrap around if needed
		int index = i % MAX_PARK_OCCUPANCY;

		walkerTimes[index] += WALKWAY_REFRESH_INTERVAL; 
		
		// check if the walker is at the end of the walkway
		if (walkerTimes[index] > timeToWalk) {
			
			passVisitor(walkers[index]);
			
			head = (head + 1) % MAX_PARK_OCCUPANCY; // dequeue
			walkerCount--;
		}
	}

	// ask for a new event
	if (walkerCount > 0)
		generateNewEvent(WALKWAY_REFRESH_INTERVAL);
}
