#include "event.h"

Event::Event(EventHandler* target, int time) {
	this->target = target;
	this->time = time;
}

EventHandler* Event::getTarget() const {
	return target;
}

int Event::getTime() const {
	return time;
}