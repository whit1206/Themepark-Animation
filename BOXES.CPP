

#include "boxes.h"
#include "eventscheduler.h"

#include <assert.h>
#include <math.h>


//*****************************************************************************************************

//*****************************************************************************************************



Bathroom::Bathroom(int r, int h, int a, int theta, bool is_women, QBox* qb) : Attraction(r, h, a, qb) {
	this->theta=theta;
	this->is_women=is_women;
	if(is_women)
		BR_TIME = 20;
	else
		BR_TIME = 10;
}


void Bathroom::acceptVisitor(Visitor* v) {
	vq.enqueue(v);
	
	// just one visitor in the queue; start helping him
	if (vq.getSize() == 1) {
		generateNewEvent(BR_TIME);
	}
}

void Bathroom::handleEvent(const Event& e) {

	Visitor* v = vq.dequeue();
	passVisitor(v);

	if (! vq.isEmpty()) {
		generateNewEvent(BR_TIME);
	}
}


void Bathroom::paint(GP142Display& display) const {
	
	// used to change coordinates with the view angle to provide 3d perspective
	double Xratio = sin((viewdegree + theta)*PI/180);
	double Yratio = cos((viewdegree + theta)*PI/180) / global_y_ratio;

	double size = 10*zoom_factor;
	int Ysize = (int)(size*cos((viewangle)*PI/180));
	GP142Color color, name_color;

	if(is_women)
	{
		name_color = Pink;
		color = Purple;
		display.write((int)((x-20)*zoom_factor), (int)((y+20)*zoom_factor), "Women", name_color, (int)(FONT_SIZE*zoom_factor));
	}
	else
	{
		name_color = Blue;
		color = NavyBlue;
		display.write((int)((x-11)*zoom_factor), (int)((y+20)*zoom_factor), "Men", name_color, (int)(FONT_SIZE*zoom_factor));
	}
	// the main block
	//-side 1
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	//-side 2
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), color, 1);
	//-connectors
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), color, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), color, 1);

	// do the roof now
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , color);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , color);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , color);
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), 
		(int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , color);


	// put the front visitor in the box
	if (! vq.isEmpty())
	{
		GP142Color color;
		if(vq.peek()->getSex())
			 color = Pink;
		else color = Blue;
		display.write((int)((x-5)*zoom_factor), (int)((y-5)*zoom_factor), 
			vq.peek()->getName(), color, (int)(FONT_SIZE*zoom_factor));
	}

	qb->paint(display, 1);
}


//*****************************************************************************************************

//*****************************************************************************************************



HotDogStand::HotDogStand(int r, int h, int a, int theta, QBox* qb) : Attraction(r, h, a, qb) {
	this->theta=theta;
}


void HotDogStand::acceptVisitor(Visitor* v) {
	vq.enqueue(v);
	
	// just one visitor in the queue; start helping him
	if (vq.getSize() == 1) {
		generateNewEvent(HOTDOG_PURCHASE_TIME);
	}
}

void HotDogStand::handleEvent(const Event& e) {

	Visitor* v = vq.dequeue();
	passVisitor(v);

	if (! vq.isEmpty()) {
		generateNewEvent(HOTDOG_PURCHASE_TIME);
	}
}


void HotDogStand::paint(GP142Display& display) const {
	
	// used to change coordinates with the view angle to provide 3d perspective
	double Xratio = sin((viewdegree + theta)*PI/180);
	double Yratio = cos((viewdegree + theta)*PI/180) / global_y_ratio;

	double size = 20*zoom_factor;
	int Ysize = (int)(size*cos((viewangle)*PI/180));
	// the main block
	//-side 1
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	//-side 2
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	//-connectors
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);

	// do the roof now
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);

	display.write((int)((x-20)*zoom_factor), (int)((y+40)*zoom_factor), "Hot Dogs", Black, (int)(FONT_SIZE*zoom_factor));

	// put the front visitor in the box
	if (! vq.isEmpty())
	{
		GP142Color color;
		if(vq.peek()->getSex())
			 color = Pink;
		else color = Blue;
		display.write((int)((x-5)*zoom_factor), (int)((y-5)*zoom_factor), vq.peek()->getName(), color, (int)(FONT_SIZE*zoom_factor));
	}

	qb->paint(display, 1);
}

//*****************************************************************************************************

//*****************************************************************************************************

TicketOffice::TicketOffice(int r, int h, int a, int theta, QBox* qb) : Attraction(r, h, a, qb) {
	this->theta=theta;
}


void TicketOffice::acceptVisitor(Visitor* v) {
	vq.enqueue(v);
	
	// just one visitor in the queue; start helping him
	if (vq.getSize() == 1) {
		generateNewEvent(TICKET_PURCHASE_TIME);
	}
}

void TicketOffice::handleEvent(const Event& e) {

	Visitor* v = vq.dequeue();
	passVisitor(v);

	if (! vq.isEmpty()) {
		generateNewEvent(TICKET_PURCHASE_TIME);
	}
}


void TicketOffice::paint(GP142Display& display) const {
	
	// used to change coordinates with the view angle to provide 3d perspective
	double Xratio = sin((viewdegree + theta)*PI/180);
	double Yratio = cos((viewdegree + theta)*PI/180) / global_y_ratio;

	double size = 15*zoom_factor;
	int Ysize = (int)(size*cos((viewangle)*PI/180));
	// the main block
	//-side 1
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	//-side 2
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), Black, 1);
	//-connectors
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor- Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), Black, 1);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), 
		(int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), Black, 1);

	// do the roof now
	display.drawLine((int)(x*zoom_factor+Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size +Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);
	display.drawLine((int)(x*zoom_factor+Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize +Yratio* size -Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);
	display.drawLine((int)(x*zoom_factor-Xratio* size -Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size +Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);
	display.drawLine((int)(x*zoom_factor-Xratio* size +Yratio* size * global_y_ratio ), (int)(y*zoom_factor+ Ysize -Yratio* size -Xratio* size / global_y_ratio ), (int)(x*zoom_factor), (int)(y*zoom_factor+2* Ysize) , Black);

	display.write((int)(x*zoom_factor), (int)((y+40)*zoom_factor), "Tickets", Black, (int)(FONT_SIZE*zoom_factor));

	// put the front visitor in the box
	if (! vq.isEmpty())
	{
		GP142Color color;
		if(vq.peek()->getSex())
			 color = Pink;
		else color = Blue;
		display.write((int)((x-5)*zoom_factor), (int)((y-5)*zoom_factor), vq.peek()->getName(), color, (int)(FONT_SIZE*zoom_factor));
	}

	qb->paint(display, 1);
}