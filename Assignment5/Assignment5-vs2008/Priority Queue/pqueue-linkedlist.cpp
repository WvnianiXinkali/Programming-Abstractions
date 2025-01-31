/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	// TODO: Fill this in!
	list = NULL;
	logLength = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	// TODO: Fill this in!
	while(true){
		if(list == NULL) break;
		Node* temp = list -> next;
		delete list;
		list = temp;
	}
}


int LinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	return logLength;
}

bool LinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	return list == NULL;
}

void LinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	if(!isEmpty()){ // 
		Node* currElem = list;
		Node* temp = list -> next; 
		if(currElem -> value > value){ 
			Node* newElem = new Node;
			newElem -> value = value;
			newElem -> next = currElem;
			list = newElem;
		} else {
			while(true){  
				if(temp == NULL) break;
				if(temp -> value > value) break;
				temp = temp -> next;
				currElem = currElem -> next;
			} 
			Node* newElem = new Node;
			newElem -> value = value;
			newElem -> next = temp;
			currElem ->next = newElem;
		}
	} else {
		list = new Node;
		list -> next = NULL;
		list -> value = value;
	}

	logLength++;
}

string LinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) error("No elements.");
	return list -> value;
}

string LinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!

	string result = peek();
	Node* temp = list -> next;
	delete list;
	list = temp;

	logLength--;
	return result;
}

