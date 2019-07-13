#include "visitor.h"

Visitor::Visitor(char name, int arrivalTime, bool is_female) {
	this->name = name;
	this->arrivalTime = arrivalTime;
	this->is_female = is_female;
}


char Visitor::getName() const {
	return name;
}


int Visitor::getArrivalTime() const {
	return arrivalTime;
}

bool Visitor::getSex() const {
	return is_female;
}