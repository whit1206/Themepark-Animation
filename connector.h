#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "parkelement.h"

// connectors allow visitors to choose one of two possible ways to go next
// the number of "in" ParkElements is not limited (anyone can call acceptCustomer)
// the number of "out" ParkElements is always 2
// normally connectors are used to connect two intersecting walkways
// but theoretically one could connect any park elements anywhere in the park
// which will make visitors "jump" from one place to another
class Connector : public ParkElement {

public:
	// construct a new connector that would pass customers to a given out1
	// with probability probOfFirst and to out2 with probability 1-probOfFirst
	Connector(ParkElement* out1, ParkElement* out2, double probOfFirst=0.5);
	
	// connectors are not visible; still must define paint()
	void paint(GP142Display& display) const;


	// connectors never get any events; this is implemented as assert(false)
	void handleEvent(const Event&);

	// override it; it is not legal; calls assert(false)
	void connectTo(ParkElement*);

	// pass a given visitor to the ParkElements I am connected to
	// the visitor will go to out1 with probability probOfFirst;
	// otherwise it goes to out2
	void acceptVisitor(Visitor* v);	

private:
	// the probability that a visitor will go to the first of my outs
	double probOfFirst;

	// these are the park elements are am passing visitors to
	ParkElement* connectedTo1;
	ParkElement* connectedTo2;
};

#endif