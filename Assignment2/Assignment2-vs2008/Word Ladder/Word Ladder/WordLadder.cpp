/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
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

using namespace std;

void wordLadder();
string findWordLadder(string startW, string endW);
string ladderToString(Stack <string> stack);
HashSet <string> getWordsWithin1Step(string word, string endW, Lexicon& lex);
bool is1StepApart(string word1, string word2);

int main() {
	wordLadder();
    return 0;
}	

void wordLadder(){ // Comunicates with user;
	string startW = getLine("Enter the starting word (or nothing to quit): ");
	if(startW != "") {
		string endW = getLine("Enter the ending word: ");
		cout << "Searching... " << endl;
		cout << findWordLadder(startW, endW) << endl;
	} else {
		cout << "Goodbye!" << endl;
	}
	while (startW != ""){
		startW = getLine("Enter the starting word (or nothing to quit): ");
		if(startW != "") {
			string endW = getLine("Enter the ending word: ");
			cout << "Searching... " << endl;
			cout << findWordLadder(startW, endW) << endl;
		} else {
			cout << "Goodbye!" << endl;
			break;
		}
	}
}

string findWordLadder(string startW, string endW){ // Finds shortest ladder with breadth-first search algorithm;
		Lexicon lex("EnglishWords.dat");
		
		Queue <Stack <string>> queue;
		Stack <string> startLadder;
		startLadder.push(startW);
		queue.enqueue(startLadder);

		HashSet <string> usedWords;
		usedWords.add(startW);

		if(startW.length() != endW.length()){
			return "No Word ladder could be found.";
		}

		while(!queue.isEmpty()){
			Stack <string> ladder = queue.dequeue();
			if(ladder.peek() == endW){
				return "Ladder found: " + ladderToString(ladder);
			}
			HashSet <string> wordsWithin1Step = getWordsWithin1Step(ladder.peek(), endW, lex);
			foreach(string word in wordsWithin1Step){
				if(!usedWords.contains(word)){
					usedWords.add(word);
					Stack <string> tempLadder = ladder;
					tempLadder.push(word);
					if(tempLadder.peek() == endW){
						return "Ladder found: " + ladderToString(tempLadder);
					}
					queue.enqueue(tempLadder);
					//cout << ladderToString(tempLadder) << endl;
				}
			}
		} // corn
		return "No Word ladder could be found.";
}

string ladderToString(Stack <string> stack){ // Makes ladder printable;
	Stack <string> reverseStack;
	while(!stack.isEmpty()){
		reverseStack.push(stack.pop());
	}
	
	string ladderToString = reverseStack.pop();
	while(!reverseStack.isEmpty()){
		ladderToString = ladderToString + " -> " + reverseStack.pop();
	}

	return ladderToString;
} // lake bake bale ball // ball bale bake lake // lake -> bake -> bale -> ball;

HashSet <string> getWordsWithin1Step(string word, string endW, Lexicon& lex){
	
	HashSet <string> set;
	if(!lex.contains(word) || !lex.contains(endW)) return set;
	string alphabet = "";
	for(char i = 'a'; i <= 'z'; i++){
		alphabet += i;
	}
	string tempWord = word;
	for (int i = 0; i < word.length(); i ++){
		for (int j = 0; j < alphabet.length(); j++){
			word[i] = alphabet[j];
			if(lex.contains(word)){
				set.add(word);
			}
		}
		word = tempWord;
	}
	return set;
}

bool is1StepApart(string word1, string word2){
	int count = 0;
	for(int i = 0; i < word1.length(); i ++){
		if(word1[i] != word2[i]){
			count ++;
		}
	}
	return count == 1;
}


