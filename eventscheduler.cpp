#include "eventscheduler.h"


EventScheduler::EventScheduler(Park* park) {
	this->park = park;
	currentTime = 0;
}


int EventScheduler::getCurrentTime() const {
	return currentTime;
}


void EventScheduler::enqueueEvent(Event* event) {
	eq.enqueue(event);
}


void EventScheduler::run() {
	
	// infinite loop
	while (! eq.isEmpty()) {
		Event* e = eq.dequeue();
		
		if (e->getTime() > currentTime) {
			park->pause(e->getTime() - currentTime);
		}
		
		currentTime = e->getTime();
		
		EventHandler* target = e->getTarget();
		target->handleEvent(*e);

		// let's not repaint the same thing twice
		// if the next event will happen at the same moment we will repaint after
		// that event
		if (! eq.isEmpty() && eq.peek()->getTime() > currentTime)
			park->repaint();
		
		// e is no longer needed
		delete e;
	}
}