#include <assert.h>
#include <math.h>

#include "rollercoaster.h"
#include "eventscheduler.h"

Rollercoaster::Rollercoaster(int r, int h, int a, int theta, QBox* qb) : Attraction(r, h, a, qb) {
	
	for (int i=0; i<RC_CAPACITY; i++)
	{
		carPos[i] = RC_CAPACITY - i - 1;
		riders[i] = 0;
	}

	this->theta = theta;
	riderCount = 0;
	startTime = -1;
}

void Rollercoaster::acceptVisitor(Visitor* v) {
	vq.enqueue(v);

	if (startTime < 0 && vq.getSize() >= RC_CAPACITY) {
		startTime = scheduler->getCurrentTime(); // current time
		generateNewEvent(0);
	}
}


void Rollercoaster::handleEvent(const Event& e) 
{


	if(riderCount == 0) {
	
		if(vq.getSize() >= RC_CAPACITY) {
			for(int i = 0; i < RC_CAPACITY; i++)
			{
				riders[i] = vq.getVisitorAt(i);
				carPos[i] = RC_CAPACITY - i - 1; 
				riderCount++;
			}	
			assert(riderCount == RC_CAPACITY);
		}

	}
	else { //has riders
		Visitor* v;
		for(int i = 0; i < RC_CAPACITY; i++)
		{
			if((carPos[i] < 40 && carPos[i] >= 20)||(carPos[i] < 80 && carPos[i] >= 60))
			carPos[i]++;
			carPos[i]++;
			if (carPos[i] > 79) { //next load or stop rolling
				carPos[i] = 0;
				v = vq.dequeue();
				assert(v == riders[i]);

				passVisitor(v);
				riders[i] = 0;
				riderCount--;
				assert(riderCount > -1);
			}
		}
		if(vq.getSize() >= RC_CAPACITY && riderCount == 0) {
			for(int i = 0; i < RC_CAPACITY; i++)
			{
				riders[i] = vq.getVisitorAt(i);
				riderCount++;
			}
			assert(riderCount == RC_CAPACITY);
		}

	}
	generateNewEvent(RC_REFRESH_INTERVAL);
}


void Rollercoaster::paint(GP142Display& display) const {

	int i;

	//3d transforms
	double ym = ((50*cos(viewangle*PI/180))*zoom_factor);
	double yo = (y*zoom_factor);
	double xo = (x*zoom_factor);
	double Yratio = (sin((viewdegree + theta + a)*PI/180) / global_y_ratio );
	double Xratio = (-cos((viewdegree + theta + a)*PI/180));
	double dx = 8*Xratio*zoom_factor;
	double dy = 8*Yratio*zoom_factor;

	display.write((int)(x*zoom_factor), (int)((y + 60)*zoom_factor), 
		"Roller Coaster", Black, (int)(FONT_SIZE*zoom_factor));


	//draw the first segment
	const int maxpieces = 20; //for each of the 4 peices
	int pathX[maxpieces * 4], pathY[maxpieces * 4];

	double x2 = (xo-54*sin((viewdegree+theta+a)*PI/180)*zoom_factor);
	double y2 = (yo-54*cos((viewdegree+theta+a)*PI/180)/global_y_ratio*zoom_factor);

	GP142Color track_color = Black;
	GP142Color support_color = Brown;

	display.drawLine((int)xo,(int)yo,(int)xo,(int)(yo+ym),support_color,1);
	display.drawLine((int)x2,(int)y2,(int)x2,(int)(y2+ym),support_color,1);

	for(i = 1;i < maxpieces + 1;i++)
	{
		//back track,40-59
		pathX[maxpieces * 3 - i] = (int)(xo-(i-1)*dx); 
		pathY[maxpieces * 3 - i] = (int)(yo-(i-1)*dy+(cos((i-1)*2*PI/maxpieces)+1)*ym/2); 
		display.drawLine((int)(xo-(i-1)*dx),(int)(yo-(i-1)*dy+(cos((i-1)*2*PI/maxpieces)+1)*ym/2),
			(int)(xo-i*dx),(int)(yo-i*dy+(cos(i*2*PI/maxpieces)+1)*ym/2), track_color,1);
		//supports
		display.drawLine((int)(xo-i*dx),(int)(yo-i*dy+(cos(i*2*PI/maxpieces)+1)*ym/2),
			(int)(xo-i*dx),(int)(yo-i*dy), support_color,1);

		//forward track,0-19
		pathX[i - 1] = (int)(x2-(i-1)*dx); 
		pathY[i - 1] = (int)(y2-(i-1)*dy+(cos((i-1)*2*PI/maxpieces)+1)*ym/2); 
		display.drawLine((int)(x2-(i-1)*dx),(int)(y2-(i-1)*dy+(cos((i-1)*2*PI/maxpieces)+1)*ym/2),
			(int)(x2-i*dx),(int)(y2-i*dy+(cos(i*2*PI/maxpieces)+1)*ym/2), track_color,1);
		//supports
		display.drawLine((int)(x2-i*dx),(int)(y2-i*dy+(cos(i*2*PI/maxpieces)+1)*ym/2),
			(int)(x2-i*dx),(int)(y2-i*dy), support_color,1);

		
		//draw ends
		double dy1 = 27*(cos(i*PI/20+PI+(viewdegree + theta + a)*PI/180) / global_y_ratio )*zoom_factor;
		double dx1 = 27*(sin(i*PI/20+PI+(viewdegree + theta + a)*PI/180))*zoom_factor;
		double dy2 = 27*(cos((i-1)*PI/20+PI+(viewdegree + theta + a)*PI/180) / global_y_ratio )*zoom_factor;
		double dx2 = 27*(sin((i-1)*PI/20+PI+(viewdegree + theta + a)*PI/180))*zoom_factor;
		
		//drawl left end,60-79
		pathX[maxpieces * 4 - i] = (int)((xo+x2)/2+dx1); 
		pathY[maxpieces * 4 - i] = (int)((yo+y2)/2+ym+dy1); 
		display.drawLine((int)((xo+x2)/2+dx1),(int)((yo+y2)/2+ym+dy1),
			(int)((xo+x2)/2+dx2),(int)((yo+y2)/2+ym+dy2),track_color,1);

		//draw right end, 20-39
		pathX[maxpieces * 2 - i] = (int)((xo+x2)/2-dx1-maxpieces*dx); 
		pathY[maxpieces * 2 - i] = (int)((yo+y2)/2+ym-dy1-maxpieces*dy); 
		display.drawLine((int)((xo+x2)/2-dx1-maxpieces*dx),(int)((yo+y2)/2+ym-dy1-maxpieces*dy),
			(int)((xo+x2)/2-dx2-maxpieces*dx),(int)((yo+y2)/2+ym-dy2-maxpieces*dy),track_color,1);
		
		//draw spokes for round ends
		if (i % 2 == 0) {
			display.drawLine((int)((xo+x2)/2+dx1),(int)((yo+y2)/2+ym+dy1),
				(int)((xo+x2)/2+dx1),(int)((yo+y2)/2+dy1),support_color,1);
			display.drawLine((int)((xo+x2)/2-dx1-maxpieces*dx),(int)((yo+y2)/2+ym-dy1-maxpieces*dy),
				(int)((xo+x2)/2-dx1-maxpieces*dx),(int)((yo+y2)/2-dy1-maxpieces*dy),support_color,1);
		}
	}
	pathX[0] = pathX[79]; pathY[0] = pathY[79];
	GP142Color people_color = Blue;
	for(i = 0; i < RC_CAPACITY; i++)
	{
		display.drawOval((int)(pathX[carPos[i]]-5*zoom_factor),(int)(pathY[carPos[i]]-5*zoom_factor + ym/4),
			(int)(pathX[carPos[i]]+5*zoom_factor),(int)(pathY[carPos[i]]+5*zoom_factor + ym/4),track_color);
		if (riderCount >= i + 1)
		{
			if ((vq.getVisitorAt(i))->getSex())
				people_color = Pink;
			else
				people_color = Blue;
			display.write(pathX[carPos[i]]-(int)(FONT_SIZE/4*zoom_factor), pathY[carPos[i]]-(int)((FONT_SIZE/2*zoom_factor)-ym/4), 
				(vq.getVisitorAt(i))->getName(), people_color, (int)(FONT_SIZE*zoom_factor));
		}
	}
	
	//paint the QBox
	qb->paint(display, riderCount);

}