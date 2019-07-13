#ifndef VISITOR_H
#define VISITOR_H
#include "globals.h"


// objects of this class represent visitors that has a one-letter name 
// and known arrival time
class Visitor {

public:
	Visitor(char name, int arrivalTime, bool is_female);

	char getName() const;
	int getArrivalTime() const;
	bool getSex() const;

private:
	char name;
	int arrivalTime;
	bool is_female;
};

#endif