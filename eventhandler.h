#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "event.h"

// this is an abstract class that is the parent of all classes that can handle events
class EventHandler {

public:

	// the empty default constructor is fine

	// =0 means has to be defined in derived classes
	// else no object can be constructed
	virtual void handleEvent(const Event& event) = 0;

private:

};

#endif