#ifndef PARKELEMENT_H
#define PARKELEMENT_H

#include "gp142display.h"
#include "eventhandler.h"
#include "visitor.h"

// this class implements an abstract park element that is capable of handling events,
// know how to point itself, and can accept a visitor (from another park element)
// park elements are connected into a directed graph so that each park element has
// to know only its successors in the graph (not the predecessors). Most park elements
// are connected to only one successor. Connectors are connected to two.
class ParkElement : public EventHandler {

public:
	ParkElement();

	virtual void paint(GP142Display& display) const = 0;

	// a new visitor comes to this park element, accept the visitor
	virtual void acceptVisitor(Visitor* v) = 0;

	// connect myself to a given park element so that visitors that leave
	// me go to there
	virtual void connectTo(ParkElement* pe);

	virtual void setXY();

protected:
	// pass a given visitor to the ParkElement I am connected to
	void passVisitor(Visitor* v);

	// ask the scheduler for a new event for me in a given number of ticks from now
	void generateNewEvent(int ticksFromNow);

private:

	// the next parkElement a visitor will go to; typically a walkway
	ParkElement* connectedTo;
};

#endif