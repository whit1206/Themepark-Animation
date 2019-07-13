#ifndef EVENT_H
#define EVENT_H

// can't include eventhandler.h - would create circular include
class EventHandler;

// this class implements events that ParkElements (EventHandlers)
// use to wake-up themselves when they need to do something
class Event {

public:
	// construct a new Event with a given target and time
	Event(EventHandler* target, int time);

	EventHandler* getTarget() const;

	int getTime() const;

private:

	// the event taget that is the ParkElement that should be notified
	// normally ParkElements only request notifications for themselves not for other
	// objects
	EventHandler* target;
	
	// time is measured in ticks of the GP142 timer
	// a second is TICKS_IN_SEC (see eventscheduler.h) ticks
	int time;
};

#endif