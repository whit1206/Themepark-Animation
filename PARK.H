#ifndef PARK_H
#define PARK_H

#include "gp142.h"
#include "gp142display.h"

#include "parkelement.h"
#include "parkgates.h"
#include "globals.h"

const int MAX_PARK_SIZE = 200;

// this class implements a park that is a collection of park elements
// it is responsible for periodic repainting of park elements
class Park {

public:

	Park();
	~Park();

	// open the park (start simulation)
	void open();

	// pause for a given number of ticks
	void pause(int ticks);

	// reapint the entire park
	void repaint();

private:

	// build park's structure
	void build();

	// add a new park element to park so that it can be re-painted when needed
	void addElement(ParkElement* pe);
	
	// these are park gates that count the number of visitors
	ParkGates* gates;

	ParkElement* parkElements[MAX_PARK_SIZE];
	int parkSize;

	GP142Display display;
};

#endif
