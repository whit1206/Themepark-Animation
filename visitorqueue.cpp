#include <assert.h>

#include "visitorqueue.h"


VisitorQueue::VisitorQueue() {

	// a dummy element
	head = new VisitorNode();
	head->v = 0;
	head->next = head;
	size = 0;
}


VisitorQueue::~VisitorQueue() {
	while (! isEmpty()) {
		dequeue();
	}
}


bool VisitorQueue::isEmpty() const {
	return size == 0;
}


int VisitorQueue::getSize() const {
	return size;
}


void VisitorQueue::enqueue(Visitor* newVisitor) {
	assert(newVisitor != 0);

	// first find the tail
	VisitorNode* cur = head;
	for (; cur->next != head; cur = cur->next) {
		continue;
	}

	insertAfter(cur, newVisitor);
	assert(! isEmpty());
}


void VisitorQueue::insertAfter(VisitorNode* node, Visitor* newVisitor) {
	assert (node != 0 && newVisitor != 0);

	VisitorNode* newNode = new VisitorNode();

	newNode->v = newVisitor;
	newNode->next = node->next;

	node->next = newNode;
	size++;
}


Visitor* VisitorQueue::dequeue() {
	assert(! isEmpty());

	VisitorNode* firstNode = head->next;
	head->next = firstNode->next;
	
	Visitor* result = firstNode->v;
	delete firstNode;

	size--;
	return result;
}


const Visitor* VisitorQueue::peek() const {
	assert(! isEmpty());
	VisitorNode* firstNode = head->next;
	return firstNode->v;
}


const Visitor* VisitorQueue::getVisitorAt(int position) const {
	assert(0 <= position && position < size);
	
	VisitorNode* cur = head->next;

	for (int i=0; i<position; i++) {
		cur = cur->next;
	}

	return cur->v;
}