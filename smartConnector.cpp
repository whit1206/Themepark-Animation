#include <assert.h>

#include "smartConnector.h"
#include "globals.h"

SmartConnector::SmartConnector(ParkElement* out1, ParkElement* out2)
{
	connectedTo1 = out1;
	connectedTo2 = out2;
}


void SmartConnector::connectTo(ParkElement* out) {
	// has to be connected to 2 outs
	assert(false);
}


void SmartConnector::acceptVisitor(Visitor* v) {
	assert(connectedTo1 != 0 && connectedTo2 != 0);

	if (v->getSex())
		connectedTo1->acceptVisitor(v);
	else
		connectedTo2->acceptVisitor(v);
}


void SmartConnector::paint(GP142Display& display) const {
	// do nothing
}


void SmartConnector::handleEvent(const Event&) {
	// never asked for events!
	assert(false);
}