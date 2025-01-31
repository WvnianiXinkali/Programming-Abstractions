

const int startSize = 10;
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	// TODO: Fill this in!
	allocatedSize = startSize;
	logicalSize = 0;
	list = new string[allocatedSize];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	// TODO: Fill this in!
	delete[] list;
}

int HeapPriorityQueue::size() {
	// TODO: Fill this in!
	return logicalSize;
}

bool HeapPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	return logicalSize == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	if(logicalSize == allocatedSize) {
		increaseQueueSize();
	}
	list[logicalSize++] = value;
	if(logicalSize != 1){
		int indexChild = logicalSize - 1;
		int indexMom = (logicalSize - 2) / 2;
		while(list[indexChild] < list[indexMom]){
			string temp = list[indexMom];
			list[indexMom] = list[indexChild];
			list[indexChild] = temp;
			indexChild = indexMom;
			indexMom = (indexChild - 1) / 2;
			if(indexMom < 0) break;
		}
	}
}

string HeapPriorityQueue::peek() {
	// TODO: Fill this in!
	if(isEmpty()) error("No elements");
	return list[0];
}

string HeapPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	string result = peek();

	string temp = list[0];
	list[0] = list[logicalSize - 1];
	list[logicalSize - 1] = temp;
	logicalSize--;
	if(!isEmpty()){
		int indexMom = 0;
		int indexChild1 = indexMom * 2 + 1;
		int indexChild2 = indexMom * 2 + 2;
		while(true){
			if(indexChild2 < logicalSize && indexChild1 < logicalSize){
				if(list[indexChild1] >= list[indexChild2]){
					if(list[indexMom] > list[indexChild2]){
						string temp = list[indexMom];
						list[indexMom] = list[indexChild2];
						list[indexChild2] = temp;
						indexMom = indexChild2;
						indexChild1 = indexMom * 2 + 1;
						indexChild2 = indexMom * 2 + 2;
					} else {
						break;
					}
				} else if(list[indexChild1] < list[indexChild2]){
					if(list[indexMom] > list[indexChild1]){
						string temp = list[indexMom];
						list[indexMom] = list[indexChild1];
						list[indexChild1] = temp;
						indexMom = indexChild1;
						indexChild1 = indexMom * 2 + 1;
						indexChild2 = indexMom * 2 + 2;
					} else {
						break;
					}
				}
			} else if(indexChild1 < logicalSize){
				if(list[indexMom] > list[indexChild1]){
						string temp = list[indexMom];
						list[indexMom] = list[indexChild1];
						list[indexChild1] = temp;
						indexMom = indexChild1;
						indexChild1 = indexMom * 2 + 1;
						indexChild2 = indexMom * 2 + 2;
				} else {
					break;
				}
			} else{
				break;
			}
		}
	}

	return result;
}

void HeapPriorityQueue::increaseQueueSize(){
	string* temp = new string[logicalSize * 2];
	for(int i = 0; i < logicalSize; i++){
		temp[i] = list[i];
	}
	list = temp;
	allocatedSize = logicalSize * 2;
}