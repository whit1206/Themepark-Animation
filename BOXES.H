
#ifndef BOXES_H
#define BOXES_H

#include "attraction.h"
#include "globals.h"




const int BR_CAPACITY = 2;

class Bathroom : public Attraction {

public:
	Bathroom(int r, int h, int a, int theta, bool is_women, QBox* qb);

	void handleEvent(const Event& e);

	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);

private:
	int theta;
	bool is_women;
	int BR_TIME;
};



const int HOTDOG_PURCHASE_TIME = 20;

class HotDogStand : public Attraction {

public:
	HotDogStand(int r, int h, int a, int theta, QBox* qb);

	void handleEvent(const Event& e);

	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);

private:
	int theta;
};



const int TICKET_PURCHASE_TIME = AVG_VISITOR_INTERVAL;

class TicketOffice : public Attraction {

public:
	TicketOffice(int r, int h, int a, int theta, QBox* qb);

	void handleEvent(const Event& e);

	void paint(GP142Display& display) const;

	void acceptVisitor(Visitor* v);

private:
	int theta;
};

#endif