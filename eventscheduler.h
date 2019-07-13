#ifndef EVENTSCHEDULER_H
#define EVENTSCHEDULER_H

#include "park.h"
#include "eventqueue.h"

// GP142 can send periodic notifications approx. 10-20 times per second
const int TICKS_IN_SEC = 10;

// this class implements an evetn scheduler that is responsible for enqueueing and
// scheduling events (notifying event targets according to event times)
class EventScheduler {

public:

	// create a new event scheduler for a given park
	// park is used to synchronize the scheduler's timer with the real time 
	// (see Park::pause) and to repaint the screen periodically (after each event)
	EventScheduler(Park* park);

	// run the simulation forever
	// assumes that at least one event has been enqeueued already
	void run();

	// enqueue a given event in the scheduler's event queue
	void enqueueEvent(Event* event);

	// return the current simulation time (in ticks of the gp142 timer)
	int getCurrentTime() const;

private:
	EventQueue eq;
	
	int currentTime; // time is measured in ticks of the GP142 timer

	Park* park;
};

#endif