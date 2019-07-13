#ifndef VISITOR_QUEUE
#define VISITOR_QUEUE

#include "visitor.h"

// this class implements a pure FIFO queue of customers
class VisitorQueue {

public:
	VisitorQueue();
	~VisitorQueue();

	// return true if i am empty
	bool isEmpty() const;

	// put a given visitor in the end of the queue
	void enqueue(Visitor* newVisitor);
	
	// return the front visiotr and remove him from the queue
	Visitor* dequeue();

	// return the first visitor without removing him from the queue
	const Visitor* peek() const;

	// return the size of the queue
	int getSize() const;

	// return the visitor at a given position>=0 in the queue
	const Visitor* getVisitorAt(int position) const;

private:

	struct VisitorNode {
		Visitor* v;
		VisitorNode* next;
	};

	// insert a given visitor after a given node
	void insertAfter(VisitorNode* node, Visitor* newVisitor);
	
	VisitorNode* head;
	int size;
};

#endif