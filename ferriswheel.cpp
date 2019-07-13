#include <assert.h>
#include <math.h>

#include "ferriswheel.h"
#include "eventscheduler.h"

FerrisWheel::FerrisWheel(int r, int h, int a, int theta, QBox* qb) : Attraction(r, h, a, qb) {
	this->theta=theta;
	for (int i=0; i<FW_CAPACITY; i++)
		riders[i] = 0;

	riderCount = 0;
	startTime = -1;
}



void FerrisWheel::acceptVisitor(Visitor* v) {
	vq.enqueue(v);
	
	// first visitor; spin the wheel
	if (startTime < 0) {
		startTime = scheduler->getCurrentTime(); // current time
		generateNewEvent(0);
	}
}


void FerrisWheel::handleEvent(const Event& e) {

	int t = (e.getTime() - startTime) % FW_RIDE_TIME;

	if (t % (FW_RIDE_TIME / FW_CAPACITY) == 0) {

		int currentCabin =  (FW_CAPACITY - FW_CAPACITY * t / FW_RIDE_TIME) % FW_CAPACITY;

		assert (0 <= currentCabin && currentCabin < FW_CAPACITY);

		if (riders[currentCabin] != 0) {
			Visitor* v = vq.dequeue();
			assert(v == riders[currentCabin]);

			passVisitor(v);
			riders[currentCabin] = 0;
			riderCount--;
			if (vq.getSize() > riderCount)
			{
 				riders[currentCabin] = vq.getVisitorAt(riderCount);
				riderCount++;
			}
		} else { // empty cabin
			if (vq.getSize() > riderCount) { // some visitors are waiting
				riders[currentCabin] = vq.getVisitorAt(riderCount);
				riderCount++;
			}
			
		}
	}

	generateNewEvent(FW_REFRESH_INTERVAL);
}


void FerrisWheel::paint(GP142Display& display) const {

	double ratio = sin((viewdegree + theta)*PI/180);
	double Yratio = 1;//(cos((viewdegree + theta)*PI/180)*sin(viewangle*PI/180)+cos(viewangle*PI/180));
	int dx = (int)(sin((viewdegree + theta)*PI/180));
	int dy = (int)(cos((viewdegree + theta)*PI/180)*sin(viewangle*PI/180)+cos(viewangle*PI/180));

	int yo=(int)(y+(FW_RADIUS+FONT_SIZE)*Yratio);
	display.write((int)((x-30)*zoom_factor), (int)(((yo + (FW_RADIUS)*Yratio) + FONT_SIZE)*zoom_factor), 
		"FerrisWheel", Black, (int)(FONT_SIZE*zoom_factor));

	display.drawOval((int)((x-ratio*FW_RADIUS)*zoom_factor),(int)((yo-(FW_RADIUS)*Yratio)*zoom_factor), 
		(int)((x+ratio*FW_RADIUS)*zoom_factor), (int)((yo+(FW_RADIUS)*Yratio)*zoom_factor), Black);
	
	double step = 2*PI / FW_CAPACITY;
	
	// position of cabin 0
	double a0 = 3*PI/2; // the lowest point
	if (startTime >= 0) { 
		// will animate the spokes too
		// how many ticks since the beginning of a new revolution
		int pos = (scheduler->getCurrentTime() - startTime) % FW_RIDE_TIME;
		
		a0 += 2* PI * pos / FW_RIDE_TIME;
	}

	// draw spokes now
	for (int i=0; i<FW_CAPACITY; i++) {
		int x1 = (int) (x + ratio*FW_RADIUS * cos(a0 + step*i));
		int y1 = (int) (yo + (FW_RADIUS * sin(a0 + step*i))*Yratio);
		if (i == 0)
			display.drawLine((int)(x*zoom_factor), (int)(yo*zoom_factor), 
				(int)(x1*zoom_factor), (int)(y1*zoom_factor), Red);
		else
			display.drawLine((int)(x*zoom_factor), (int)(yo*zoom_factor), 
				(int)(x1*zoom_factor), (int)(y1*zoom_factor), Black);
		const Visitor* r = riders[i];
		if (r != 0) { // some one there
			GP142Color color;
			if(r->getSex())
				 color = Pink;
			else color = Blue;
			int x2 = (int) (x + ratio*(FW_RADIUS+FONT_SIZE) * cos(a0 + step*i));
			int y2 = (int) (yo + (FW_RADIUS * sin(a0 + step*i))*Yratio - FONT_SIZE/2);
			display.write((int)(x2*zoom_factor), (int)(y2*zoom_factor), r->getName(), color, (int)(FONT_SIZE*zoom_factor));
		}
	}
	qb->paint(display, riderCount);
}