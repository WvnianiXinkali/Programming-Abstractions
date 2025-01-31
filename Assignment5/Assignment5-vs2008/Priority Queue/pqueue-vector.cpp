/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	
	return queue.size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return queue.isEmpty();
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	queue.add(value);
}

string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	string temp = queue[0];
	for(int i = 0; i < size(); i ++){
		if(temp > queue[i]){
			temp = queue[i];	
		}
	}
	return temp;
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	string temp = queue[0];
	int index = 0;
	for(int i = 0; i < size(); i ++){
		if(temp > queue[i]){
			temp = queue[i];
			index = i;
		}
	}
	queue.remove(index);
	return temp;
}

