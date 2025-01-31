//*************************************************************
// * File: pqueue-doublylinkedlist.cpp
// *
// * Implementation file for the DoublyLinkedListPriorityQueue
// * class.
// */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	list = NULL;
	min = NULL;
	logLength = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	if(list != NULL){
		while(true){
			if(list -> front == NULL){
				delete list;
				break;
			}
			list = list -> front;
			delete list -> back;
		}
	}
}

int DoublyLinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	return logLength;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	return list == NULL;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	if(!isEmpty()){
		Node* newElem = new Node;
		newElem -> value = value;
		newElem -> back = NULL;
		newElem -> front = list;
		list -> back = newElem;
		list = newElem;
	} else {
		list = new Node;
		list -> value = value;
		list -> front = NULL;
		list -> back = NULL;
	}

	logLength++;
}

string DoublyLinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) error("Nothing to peek at.");

	string value = list -> value;
	Node* temp = list;
	min = temp;
	while(temp != NULL){
		if(temp -> value < value) {
			value = temp -> value;
			min = temp;
		}
		temp = temp -> front;
	}
	return value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	string value = peek();

	if(min -> front == NULL && min -> back == NULL){
		delete min;
		list = NULL;
	} else if(min -> front == NULL){
		min = min -> back;
		delete min -> front;
		min -> front = NULL;
	} else if(min -> back == NULL){
		min = min -> front;
		delete min -> back;
		min -> back = NULL;
		list = min;
	} else {
		min = min -> back;
		min -> front = min -> front -> front;
		delete min -> front -> back;
		min -> front -> back = min;
	}

	logLength--;
	return value;
}

