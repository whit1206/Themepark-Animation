#include <assert.h>

#include "eventqueue.h"


EventQueue::EventQueue() {

	// a dummy element
	head = new EventNode();
	head->event = 0;
	head->next = head;
}


EventQueue::~EventQueue() {
	while (! isEmpty()) {
		dequeue();
	}
}


bool EventQueue::isEmpty() const {
	return head->next == head;
}



void EventQueue::enqueue(Event* newEvent) {
	assert(newEvent != 0);

	// first find the right position
	EventNode* prev = head;
	for (EventNode* cur = head->next; cur != head; cur = cur->next) {
		if (newEvent->getTime() < cur->event->getTime())
			break;
		
		prev = cur;
	}

	insertAfter(prev, newEvent);
	assert(! isEmpty());
}


void EventQueue::insertAfter(EventNode* node, Event* newEvent) {
	assert (node != 0 && newEvent != 0);

	EventNode* newNode = new EventNode();

	newNode->event = newEvent;
	newNode->next = node->next;

	node->next = newNode;
}


Event* EventQueue::dequeue() {
	assert(! isEmpty());

	EventNode* firstNode = head->next;
	head->next = firstNode->next;
	
	Event* result = firstNode->event;
	delete firstNode;

	return result;
}


const Event* EventQueue::peek() const {
	assert(! isEmpty());
	EventNode* firstNode = head->next;
	return firstNode->event;
}