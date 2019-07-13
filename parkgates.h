#ifndef PARKGATES_H
#define PARKGATES_H

#include "parkelement.h"

// Park gates are an invisible park element that generates new visitors and
// takes care of leaving visitors
class ParkGates : public ParkElement {

public:

	ParkGates();

	// open the gates; starts the simulation
	void open();

	// does nothing; our gates are invisible
	void paint(GP142Display& display) const;

	// causes a new customer to be admitted to the park
	void handleEvent(const Event& e);

	// in the context of ParkGates acceptVisitor means:
	// "let the visitor get out of here"
	void acceptVisitor(Visitor* v);

private:
	
	// generate a new visitor and let him in the park
	void admitOne();

	// number of visitors in park; decremented when a visitor leaves
	int visitorCount;
};

#endif
