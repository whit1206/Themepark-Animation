#include <assert.h>
#include <math.h>

#include "centrifuge.h"
#include "eventscheduler.h"

Centrifuge::Centrifuge(int r, int h, int a, int theta, QBox* qb) : Attraction(r, h, a, qb) {
	this->theta = theta;
	rider = 0;
	hasRider = false;
	startTime = -1;
}



void Centrifuge::acceptVisitor(Visitor* v) {
	vq.enqueue(v);
	
	// first visitor; spin the wheel
	if (startTime < 0) {
		startTime = scheduler->getCurrentTime(); // current time
		generateNewEvent(0);
	}
}


void Centrifuge::handleEvent(const Event& e) 
{
   	int t = (e.getTime() - startTime) % CF_RIDE_TIME;

	if (t % (CF_RIDE_TIME) == 0) {
		
		if (rider != 0) { //if there is a rider still on...
			assert(vq.getSize() > 0);
			Visitor* v = vq.dequeue();
			assert(v == rider);

			passVisitor(v);
			
			rider = 0;
			hasRider = false;
			if (vq.getSize() == 0)
			{
				startTime = -1;
				return;
			}
			else {
 				rider = vq.getVisitorAt(0);
				hasRider = true;
			}
		} else { // empty cabin
			if (vq.getSize() > 0) { // some visitors are waiting
				rider = vq.getVisitorAt(0);
   				hasRider = true;
			}
		}
	}
	generateNewEvent(CF_REFRESH_INTERVAL);

}


void Centrifuge::paint(GP142Display& display) const {
	
	int yo = y + (int)(30*cos(viewangle*PI/180));
	display.write((int)((x-20)*zoom_factor), (int)((yo + (CF_RADIUS + 7) / global_y_ratio + FONT_SIZE)*zoom_factor),
		"Centrifuge", Black, (int)(FONT_SIZE*zoom_factor));
	//main oval
	if(viewangle != 0)
		display.drawOval((int)((x+CF_RADIUS / 4)*zoom_factor), (int)((yo+CF_RADIUS / global_y_ratio /4)*zoom_factor),
			(int)((x-CF_RADIUS /4)*zoom_factor), (int)((yo-CF_RADIUS / global_y_ratio / 4)*zoom_factor), Black);
	else
		display.drawLine((int)((x+CF_RADIUS / 4)*zoom_factor), (int)(yo*zoom_factor), 
			(int)((x-CF_RADIUS / 4)*zoom_factor), (int)(yo*zoom_factor) , Black , 1);

	display.drawLine((int)((x-CF_RADIUS /4)*zoom_factor), (int)(yo*zoom_factor), 
		(int)((x-CF_RADIUS /4)*zoom_factor), (int)(y*zoom_factor), Black);
	display.drawLine((int)((x+CF_RADIUS /4)*zoom_factor), (int)(yo*zoom_factor), 
		(int)((x+CF_RADIUS /4)*zoom_factor), (int)(y*zoom_factor), Black);


	// position of cabin 0
	double a0 = (a+theta-viewdegree)*PI/180; // the lowest point
	if (startTime >= 0) { 
		int pos = (scheduler->getCurrentTime() - startTime) % CF_RIDE_TIME;
		a0 += 2* PI * pos / CF_RIDE_TIME;
	}

	int x1 = (int) (x + CF_RADIUS * cos(a0)); //bubble
	int y1 = (int) (yo + CF_RADIUS * sin(a0) / global_y_ratio);
	display.drawOval((int)((x + (CF_RADIUS + 7)* cos(a0) - 7)*zoom_factor), 
		(int)((yo + (CF_RADIUS + 7) * sin(a0) / global_y_ratio - 7)*zoom_factor), 
		(int)((x + (CF_RADIUS + 7)* cos(a0) + 7)*zoom_factor), 
		(int)((yo + (CF_RADIUS + 7) * sin(a0) / global_y_ratio + 7)*zoom_factor), Black);

	display.drawLine((int)(x*zoom_factor), (int)(yo*zoom_factor), (int)(x1*zoom_factor), (int)(y1*zoom_factor), Red);
	const Visitor* r = rider;
	if (r != 0) { // some one there
		GP142Color color;
		if(r->getSex())
			 color = Pink;
		else color = Blue;
		display.write((int)((x + (CF_RADIUS + 7)* cos(a0)-3)*zoom_factor), 
			(int)((yo + (CF_RADIUS + 7) * sin(a0) / global_y_ratio - 6)*zoom_factor), 
			r->getName(), color, (int)(FONT_SIZE*zoom_factor));
	}
	qb->paint(display, 1);
}