#include <assert.h>

#include "parkelement.h"
#include "globals.h"
#include "eventscheduler.h"

ParkElement::ParkElement() {
	connectedTo = 0;
}

void ParkElement::connectTo(ParkElement* pe) {
	connectedTo = pe;
}

void ParkElement::passVisitor(Visitor* v) {
	assert(connectedTo != 0);
	connectedTo->acceptVisitor(v);
}

void ParkElement::generateNewEvent(int ticksFromNow) {
	Event* e = new Event(this, scheduler->getCurrentTime() + ticksFromNow);
	scheduler->enqueueEvent(e);
}

void ParkElement::setXY() {
}