#include <assert.h>

#include "connector.h"
#include "globals.h"

Connector::Connector(ParkElement* out1, ParkElement* out2, 
										 double probOfFirst) {
	this->probOfFirst = probOfFirst;
	connectedTo1 = out1;
	connectedTo2 = out2;
}


void Connector::connectTo(ParkElement* out) {
	// has to be connected to 2 outs
	assert(false);
}


void Connector::acceptVisitor(Visitor* v) {
	assert(connectedTo1 != 0 && connectedTo2 != 0);

	if (generateRandomBool(probOfFirst))
		connectedTo1->acceptVisitor(v);
	else
		connectedTo2->acceptVisitor(v);
}


void Connector::paint(GP142Display& display) const {
	// do nothing
}


void Connector::handleEvent(const Event&) {
	// never asked for events!
	assert(false);
}