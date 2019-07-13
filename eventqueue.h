#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "event.h"

// this queue is not FIFO; it is proritized by event time
class EventQueue {

public:
	EventQueue();
	~EventQueue();

	bool isEmpty() const;

	// insert a given event in the right place in the event queue
	void enqueue(Event* newEvent);

	// remove the head event and return it
	Event* dequeue();

	// return the head event without removing it from the queue
	const Event* peek() const;

private:

	struct EventNode {
		Event* event;
		EventNode* next;
	};

	void insertAfter(EventNode* node, Event* newEvent);
	
	EventNode* head;
	
};

#endif