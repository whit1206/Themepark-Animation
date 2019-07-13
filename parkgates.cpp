#include "parkgates.h"
#include "eventscheduler.h"
#include "globals.h"

ParkGates::ParkGates() {
	visitorCount = 0;
}

void ParkGates::open() {

	// create a kick-off event
	generateNewEvent(1);
	
	// go!
	scheduler->run();
}


void ParkGates::paint(GP142Display& display) const {

	display.write(-290, -220, "Park occupancy: ", Black, FONT_SIZE);
	display.write(-200, -220, visitorCount, Black, FONT_SIZE);
}


void ParkGates::acceptVisitor(Visitor* v) {
	// v is leaving
	delete v;

	visitorCount--;
}


void ParkGates::handleEvent(const Event&) {
	

	if (visitorCount < MAX_PARK_OCCUPANCY) {
		// time to send in another visitor
		admitOne();
	} // else the angry visitor goes back home

	int t = generateRandomNumber(AVG_VISITOR_INTERVAL);
	generateNewEvent(t);
}


void ParkGates::admitOne() {

	char name = generateRandomChar();
	bool is_female = generateRandomBool(.5);
	
	Visitor* v = new Visitor(name, scheduler->getCurrentTime(), is_female);

	passVisitor(v);

	visitorCount++;
}