#include <assert.h>
#include <math.h>

#include "gondola.h"
#include "eventscheduler.h"

Gondola::Gondola(int r, int h, int a, QBox* qb) : Attraction(r, h, a, qb) 
{	
	riderCount = 0;
	startTime = 0;
	for (int i=0; i<4; i++)
	riders[i] = 0;
	initialized = false;

}



void Gondola::acceptVisitor(Visitor* v) {
	vq.enqueue(v);

	if(vq.getSize() == 1 && initialized == false)
	{
		generateNewEvent(1);
		initialized = true;
	}
}


void Gondola::handleEvent(const Event& e) 
{
	int t = (scheduler->getCurrentTime()-startTime) % 160;

	if (t % (40) == 0) {

		int currentCabin =  (t/40);

		assert (0 <= currentCabin && currentCabin < 4);

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
	generateNewEvent(1);

}


void Gondola::paint(GP142Display& display) const {

	int i;

	int ym = (int)((100*cos(viewangle*PI/180))*zoom_factor);
	int yo = (int)(y*zoom_factor);
	int xo = (int)(x*zoom_factor);
	double Yratio = (sin((viewdegree + a)*PI/180) / global_y_ratio );
	double Xratio = (-cos((viewdegree + a)*PI/180));
	int dx = (int)((8*Xratio)*zoom_factor);
	int dy = (int)((8*Yratio)*zoom_factor);

	//set the pole & name color
	GP142Color pole_color = Black;

	//draw the name
	display.write(xo-(int)(20*zoom_factor),(int)(yo+ym/4+(10/global_y_ratio*zoom_factor)),"Gondolas",pole_color,(int)(FONT_SIZE*zoom_factor));
	//draw the poles- check
	display.drawLine(xo,yo,xo,yo+ym/4,pole_color,2);
	display.drawLine(-xo,-yo,-xo,-yo+ym/4,pole_color,2);
	display.drawLine(xo/2,yo/2,xo/2,yo/2+ym,pole_color,2);
	display.drawLine(-xo/2,-yo/2,-xo/2,-yo/2+ym,pole_color,2);

	//draw the crossbars- check
	display.drawLine(xo+dx,yo+ym/4+dy,xo-dx,yo+ym/4-dy,pole_color,2);
	display.drawLine(-xo+dx,-yo+ym/4+dy,-xo-dx,-yo+ym/4-dy,pole_color,2);
	display.drawLine(xo/2+dx,yo/2+ym+dy,xo/2-dx,yo/2+ym-dy,pole_color,2);
	display.drawLine(-xo/2+dx,-yo/2+ym+dy,-xo/2-dx,-yo/2+ym-dy,pole_color,2);

	//set the cable color
	GP142Color cable_color = NavyBlue;

	//draw side 1 -check
	{
		//draw the first segment
		for(i = 4; i < 8; i++)
		{
			display.drawLine((i*xo/8)+dx,(i*yo/8)+ym/4+3*ym/4*(8-i)*(8-i)/16+dy,
				(i+1)*xo/8+dx,(i+1)*yo/8+ym/4+3*ym/4*(7-i)*(7-i)/16+dy,cable_color,1);
		}

		//draw the second segment
		for(i = -4; i < 4; i++)
		{
			display.drawLine((i*xo/8)+dx,(i*yo/8)+3*ym/4+ym/4*(i)*(i)/16+dy,
				((i+1)*xo/8)+dx,((i+1)*yo/8)+3*ym/4+ym/4*(i+1)*(i+1)/16+dy,cable_color,1);
		}

		//draw the third segment
		for(i = -8; i < -4; i++)
		{
			display.drawLine((i*xo/8)+dx,(i*yo/8)+ym/4+3*ym/4*(8+i)*(8+i)/16+dy,
				(i+1)*xo/8+dx,(i+1)*yo/8+ym/4+3*ym/4*(9+i)*(9+i)/16+dy,cable_color,1);
		}

	}

	//draw side 2 -check
	{
		//draw the first segment
		for(i = 4; i < 8; i++)
		{
			display.drawLine((i*xo/8)-dx,(i*yo/8)+ym/4+3*ym/4*(8-i)*(8-i)/16-dy,(i+1)*xo/8-dx,(i+1)*yo/8+ym/4+3*ym/4*(7-i)*(7-i)/16-dy,cable_color,1);
		}

		//draw the second segment
		for(i = -4; i < 4; i++)
		{
			display.drawLine((i*xo/8)-dx,(i*yo/8)+3*ym/4+ym/4*(i)*(i)/16-dy,((i+1)*xo/8)-dx,((i+1)*yo/8)+3*ym/4+ym/4*(i+1)*(i+1)/16-dy,cable_color,1);
		}

		//draw the third segment
		for(i = -8; i < -4; i++)
		{
			display.drawLine((i*xo/8)-dx,(i*yo/8)+ym/4+3*ym/4*(8+i)*(8+i)/16-dy,(i+1)*xo/8-dx,(i+1)*yo/8+ym/4+3*ym/4*(9+i)*(9+i)/16-dy,cable_color,1);
		}
		
	}

	//draw ends
	for(i = 0; i < 8; i++)
	{
		int dy1 = (int)(8*(sin(i*PI/8+(viewdegree + a)*PI/180) / global_y_ratio )*zoom_factor);
		int dx1 = (int)(8*(-cos(i*PI/8+(viewdegree + a)*PI/180))*zoom_factor);
		int dy2 = (int)(8*(sin((i+1)*PI/8+(viewdegree + a)*PI/180) / global_y_ratio )*zoom_factor);
		int dx2 = (int)(8*(-cos((i+1)*PI/8+(viewdegree + a)*PI/180))*zoom_factor);
		display.drawLine(xo+dx1,yo+ym/4+dy1,xo+dx2,yo+ym/4+dy2,cable_color,1);
		display.drawLine(-xo-dx1,-yo+ym/4-dy1,-xo-dx2,-yo+ym/4-dy2,cable_color,1);
	}

	//draw the cars

	double k, theta;
	int x1=0,y1=200;
	int dh = (int)(10*cos(viewangle*PI/180)*zoom_factor);
	k = (double)((scheduler->getCurrentTime())%40)/10;
	{
		for(int j = 0; j < 5; j++)
		{
			theta = 0;
			if(0<=(k+4*j)&&(k+4*j)<4)
			{
				theta = 0;
				x1 = (int)(((8-(k+4*j))*xo/8)+dx);
				y1 = (int)(((8-(k+4*j))*yo/8)+ym/4+3*ym/4*(-(k+4*j))*(-(k+4*j))/16+dy-dh);
			}
			if(4<=(k+4*j)&&(k+4*j)<12)//check
			{
				theta = 0;
				x1 = (int)(((8-(k+4*j))*xo/8)+dx);
				y1 = (int)(((8-(k+4*j))*yo/8)+3*ym/4+ym/4*(8-(k+4*j))*(8-(k+4*j))/16+dy-dh);
			}
			if(12<=(k+4*j)&&(k+4*j)<16)
			{
				theta = 0;
				x1 = (int)(((8-(k+4*j))*xo/8)+dx);
				y1 = (int)(((8-(k+4*j))*yo/8)+ym/4+3*ym/4*(16-(k+4*j))*(16-(k+4*j))/16+dy-dh);
			}
			if(16<=(k+4*j)&&(k+4*j)<20)
			{
				theta = (24-(k+4*j))*PI/4;
				int dy1 = (int)(8*(sin((16-(k+4*j))*PI/4+(viewdegree + a)*PI/180) / global_y_ratio )*zoom_factor);
				int dx1 = (int)(8*(-cos((16-(k+4*j))*PI/4+(viewdegree + a)*PI/180))*zoom_factor);
				x1 = -xo+dx1;
				y1 = -yo+ym/4+dy1-dh;
			}
			if(20<=(k+4*j)&&(k+4*j)<24)
			{
				theta = PI;
				x1 = (int)(-((28-(k+4*j))*xo/8)-dx);
				y1 = (int)(-((28-(k+4*j))*yo/8)+ym/4+3*ym/4*(20-(k+4*j))*(20-(k+4*j))/16-dy-dh);
			}
			if(24<=(k+4*j)&&(k+4*j)<32)//check
			{
				theta = PI;
				x1 = (int)(-((28-(k+4*j))*xo/8)-dx);
				y1 = (int)(-((28-(k+4*j))*yo/8)+3*ym/4+ym/4*(28-(k+4*j))*(28-(k+4*j))/16-dy-dh);
			}
			if(32<=(k+4*j)&&(k+4*j)<36)
			{
				theta = PI;
				x1 = (int)(-((28-(k+4*j))*xo/8)-dx);
				y1 = (int)(-((28-(k+4*j))*yo/8)+ym/4+3*ym/4*(36-(k+4*j))*(36-(k+4*j))/16-dy-dh);
			}
			if(36<=(k+4*j)&&(k+4*j)<40)
			{
				theta = (40-(k+4*j))*PI/4;
				int dy1 = (int)(8*(sin((36-(k+4*j))*PI/4+(viewdegree + a + 180)*PI/180) / global_y_ratio )*zoom_factor);
				int dx1 = (int)(8*(-cos((36-(k+4*j))*PI/4+(viewdegree + a + 180)*PI/180))*zoom_factor);
				x1 = xo+dx1;
				y1 = yo+ym/4+dy1-dh;
			}

			
			// used to change coordinates with the view angle to provide 3d perspective
			double Xratio = sin(theta +(viewdegree +  a)*PI/180);
			double Yratio = cos(theta +(viewdegree +  a)*PI/180) / global_y_ratio;

			// calculates sizes according to zoom and perspective
			double size = 6*zoom_factor;
			int Ysize = (int)(size*cos((viewangle)*PI/180));

			// box color
			GP142Color box_color = ForestGreen;

			// the main block
			//-side 1
			display.drawLine((int)(x1-Xratio* size +Yratio* size * global_y_ratio ), (int)(y1- Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
				(int)(x1+Xratio* size +Yratio* size * global_y_ratio ), (int)(y1- Ysize +Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1+Xratio* size +Yratio* size * global_y_ratio ), (int)(y1- Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
				(int)(x1+Xratio* size +Yratio* size * global_y_ratio ), (int)(y1+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1+Xratio* size +Yratio* size * global_y_ratio ), (int)(y1+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
				(int)(x1-Xratio* size +Yratio* size * global_y_ratio ), (int)(y1+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1-Xratio* size +Yratio* size * global_y_ratio ), (int)(y1+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
				(int)(x1-Xratio* size +Yratio* size * global_y_ratio ), (int)(y1- Ysize -Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			//-side 2
			display.drawLine((int)(x1-Xratio* size -Yratio* size * global_y_ratio ), (int)(y1- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1+Xratio* size -Yratio* size * global_y_ratio ), (int)(y1- Ysize +Yratio* size +Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1+Xratio* size -Yratio* size * global_y_ratio ), (int)(y1- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1+Xratio* size -Yratio* size * global_y_ratio ), (int)(y1+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1+Xratio* size -Yratio* size * global_y_ratio ), (int)(y1+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1-Xratio* size -Yratio* size * global_y_ratio ), (int)(y1+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1-Xratio* size -Yratio* size * global_y_ratio ), (int)(y1+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1-Xratio* size -Yratio* size * global_y_ratio ), (int)(y1- Ysize -Yratio* size +Xratio* size / global_y_ratio ), box_color, 1);
			//-connectors
			display.drawLine((int)(x1-Xratio* size -Yratio* size * global_y_ratio ), (int)(y1- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1-Xratio* size +Yratio* size * global_y_ratio ), (int)(y1- Ysize -Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1+Xratio* size -Yratio* size * global_y_ratio ), (int)(y1- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1+Xratio* size +Yratio* size * global_y_ratio ), (int)(y1- Ysize +Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1+Xratio* size -Yratio* size * global_y_ratio ), (int)(y1+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1+Xratio* size +Yratio* size * global_y_ratio ), (int)(y1+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			display.drawLine((int)(x1-Xratio* size -Yratio* size * global_y_ratio ), (int)(y1+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
				(int)(x1-Xratio* size +Yratio* size * global_y_ratio ), (int)(y1+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), box_color, 1);
			//-hang wire
			display.drawLine(x1,y1+Ysize, x1,y1+dh, box_color,1);
		}
	}

	//draw the people
	if(riderCount>0)
	for(i = 0; i < 4; i++)
	{
		double position = (double)((scheduler->getCurrentTime()-i*40)%160)/10;
			if(0<=position&&position<4)
			{
				theta = 0;
				x1 = (int)(((8-position)*xo/8)+dx);
				y1 = (int)(((8-position)*yo/8)+ym/4+3*ym/4*(-position)*(-position)/16+dy-dh);
			}
			if(4<=position&&position<12)//check
			{
				theta = 0;
				x1 = (int)(((8-position)*xo/8)+dx);
				y1 = (int)(((8-position)*yo/8)+3*ym/4+ym/4*(8-position)*(8-position)/16+dy-dh);
			}
			if(12<=position&&position<16)
			{
				theta = 0;
				x1 = (int)(((8-position)*xo/8)+dx);
				y1 = (int)(((8-position)*yo/8)+ym/4+3*ym/4*(16-position)*(16-position)/16+dy-dh);
			}
		int index = ((scheduler->getCurrentTime()%160-scheduler->getCurrentTime()%40)/40);
		const Visitor* r = riders[i];
		if(riderCount!=0)
		if (r != NULL) { // some one there
			GP142Color person_color;
			if(r->getSex())
				 person_color = Pink;
			else person_color = Blue;
		display.write(x1-(int)(FONT_SIZE/4*zoom_factor) ,y1-(int)((FONT_SIZE/2)*zoom_factor),r->getName(),person_color,(int)(FONT_SIZE*zoom_factor));
		}
	}
	//paint the QBox
	qb->paint(display, riderCount);

}