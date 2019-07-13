#include <assert.h>

#include "qbox.h"

QBox::QBox(int r, int h, int a, int theta, int q_length) {
	this->r=r;
	this->h=h;
	this->a=a;
	this->theta=theta;
	this->q_length=q_length;
}


void QBox::setQueue(VisitorQueue* vq) {
	this->vq = vq;
}


void QBox::paint(GP142Display& display, int visitorsToSkip) const{
	assert(vq != 0);

	int width = 10;
	int dx = (int)(sin((a+theta+viewdegree)*PI/180)*width);
	int dy = (int)(cos((a+theta+viewdegree)*PI/180)*width / global_y_ratio);
	int dyo = (int)(cos((a+theta+viewdegree)*PI/180)*width);

	int x = (int)(r * sin((a + viewdegree)*PI/180));
	int y = (int)((h  - FONT_SIZE / 2) * cos((viewangle) * PI /180) + (r * cos((a + viewdegree)*PI/180)) / global_y_ratio);
	int x2 = (int)(x - q_length * cos((a + theta + viewdegree) * PI/180));
	int y2 = (int)(y + (q_length * sin((a + theta + viewdegree) * PI/180)) / global_y_ratio);

	display.drawLine((int)((x+dx)*zoom_factor),(int)((y+dy)*zoom_factor),
		(int)((x-dx)*zoom_factor),(int)((y-dy)*zoom_factor),ForestGreen,1);
	display.drawLine((int)((x+dx)*zoom_factor),(int)((y+dy)*zoom_factor),
		(int)((x2+dx)*zoom_factor),(int)((y2+dy)*zoom_factor),ForestGreen,1);
	display.drawLine((int)((x-dx)*zoom_factor),(int)((y-dy)*zoom_factor),
		(int)((x2-dx)*zoom_factor),(int)((y2-dy)*zoom_factor),ForestGreen,1);

	//-used for debugging
	//display.drawLine(x+5,y,x-5,y,Black,1);
	//display.drawLine(x,y+5,x,y-5,Black,1);

	int visitorsToPaint = vq->getSize() - visitorsToSkip;
	if (visitorsToPaint <=0 )
		return;

	double stepX = ((double) (x-x2-dyo)) / visitorsToPaint;
	double stepY = ((double) (y-y2+dx/global_y_ratio)) / visitorsToPaint;

	for (int i=0; i<visitorsToPaint; i++) {
		char name = vq->getVisitorAt(i+visitorsToSkip)->getName();
		GP142Color color;
		if(vq->getVisitorAt(i+visitorsToSkip)->getSex())
			 color = Pink;
		else color = Blue;
		display.write((int) ((x-i*stepX-dyo)*zoom_factor), (int) ((y-i*stepY+dx/global_y_ratio)*zoom_factor), 
			name, color, (int)(FONT_SIZE*zoom_factor));
	}
}
