#ifndef SMARTCONNECTOR_H
#define SMARTCONNECTOR_H

#include "parkelement.h"

class SmartConnector : public ParkElement {

public:

	SmartConnector(ParkElement* out1, ParkElement* out2);
	
	void paint(GP142Display& display) const;

	void handleEvent(const Event&);

	void connectTo(ParkElement*);

	void acceptVisitor(Visitor* v);	

private:

	ParkElement* connectedTo1;
	ParkElement* connectedTo2;
};

#endif