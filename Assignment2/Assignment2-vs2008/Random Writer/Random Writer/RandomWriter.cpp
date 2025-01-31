/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "queue.h"
#include "lexicon.h"
#include "stack.h"
#include "hashset.h"
#include "random.h"
#include "map.h"
#include "hashmap.h"
#include "fstream"

using namespace std;


void randomWriting();
string calculateMarkovText(HashMap <string, Vector <char>>& data, int textSize, string& startingSeed);
string calculateSeed(HashMap <string, int>& seedNum);
void dataInit(HashMap <string, Vector <char>>& data, ifstream& input, int& markovOrder, HashMap <string, int>& seedNum);
void enterValidMarkovOrder(int& markovOrder);
void safeFileOpen(ifstream& input);




int main() {
	randomWriting();
    return 0;
}



void randomWriting(){ // opens file and reads the text; sheitanos mnishvnelobebi data struqturashi; moxdes teqstis shqmna; da moxdes teqstis dabechvda;
	ifstream input;
	safeFileOpen(input);

	int markovOrder = 2;
	enterValidMarkovOrder(markovOrder);
	
	cout << "Processing file... " << endl;
	
	HashMap <string, Vector <char>> data;
	
	HashMap <string, int> seedNum;
	
	dataInit(data, input, markovOrder, seedNum);

	string startingSeed = calculateSeed(seedNum);
		
	const int textSize = 2000;
	
	cout << calculateMarkovText(data, textSize - markovOrder, startingSeed) << endl;
}

string calculateMarkovText(HashMap <string, Vector <char>>& data, int textSize, string& startingSeed){
		string markovText = startingSeed;
		string currentSeed = startingSeed; // data string vector
		for(int i = 0; i < textSize; i++){
			int randomElement = randomInteger(0, data.get(currentSeed).size() - 1);
			char nextChar = data.get(currentSeed).get(randomElement);
			markovText += nextChar;
			currentSeed = currentSeed.substr(1) + nextChar;
			if(data.get(currentSeed).isEmpty()){
				return markovText;
			}
		}
		return markovText;
}

string calculateSeed(HashMap <string, int>& seedNum){
	int common = 0;
	string startingSeed = "";
	foreach(string seed in seedNum){
		int seedCount = seedNum.get(seed);
		if(seedCount > common){
			startingSeed = seed;
			common = seedCount;
		}
	}
	return startingSeed;
}

void dataInit(HashMap <string, Vector <char>>& data, ifstream& input, int& markovOrder, HashMap <string, int>& seedNum){
	char ch; // merabi
	string seed;
	string source;
	int count = 0;
	bool switcher = true;
	while (input.get(ch)) {
		count++;
		source += ch;
		if(count == markovOrder + 1 && switcher){ //4
			count = 0;
			switcher = false;
		}
		if(!switcher){
			if(source.length() < markovOrder){
				cout << "Not enough room for this order Markov." << endl;
				break;
			}
			seed = source.substr(count, markovOrder);
			//cout << seed << endl;
			if(!data.containsKey(seed)){
				Vector <char> followUp;
				data.put(seed, followUp);
				data[seed].add(ch);
				int count1 = 0;
				seedNum.put(seed, count1);
				int temp = seedNum.get(seed);
				temp++;
				seedNum[seed] = temp;
			} else {
				data[seed].add(ch);
				int temp = seedNum.get(seed);
				temp++;
				seedNum[seed] = temp;
			}
			
		}
	}
	seed = source.substr(source.length() - markovOrder, markovOrder); // 0123456
	if(!data.containsKey(seed)){
		Vector <char> followUp;
		data.put(seed, followUp);
	} else {
		int temp = seedNum.get(seed);
		temp++;
		seedNum[seed] = temp;
	}
}



void enterValidMarkovOrder(int& markovOrder1){ // opens file safely, doesn't let user to input wrong file name;
	markovOrder1 = getInteger("Enter the Markov order (1-10): ");
	while(markovOrder1 < 1 || markovOrder1 > 10){
		cout << "That value is out of range." << endl;
		markovOrder1 = getInteger("Enter the Markov order (1-10): ");
	}
}

void safeFileOpen(ifstream& input){ // opens file safely, doesn't let user to input wrong file name;
	string filename = getLine("Enter the source text: ");
	input.open(filename.c_str());

	while(input.fail()){
		cout << "Unable to open that file. Try again." << endl;
		filename = getLine("Enter the source text: ");
		input.clear();
		input.open(filename.c_str());
	}
}