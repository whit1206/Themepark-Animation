#include "attraction.h"

Attraction::Attraction(int r, int h, int a, QBox* qb) {
	this->r = r;
	this->h = h;
	this->a = a;
	this->setXY();
	this->qb = qb;
	qb->setQueue(&vq);
}


Attraction::~Attraction() {
	delete qb;
}

void Attraction::setXY() {
	x = (int)(r * sin((a + viewdegree)*PI/180));
	y = (int)((h + r * cos((a + viewdegree)*PI/180)) / global_y_ratio);
}
