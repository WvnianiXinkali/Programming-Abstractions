/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "strlib.h"
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    string s1 = "IOI";
	string s2 = "GioRGI";
	cout << isSubsequence(s2,s1) << endl;
    return 0;
}

bool isSubsequence(string text, string subsequence){ // giorgi ioi
	if(subsequence.length() == 0){
		return true;
	} else if(text.length() == 0){
		return false;
	} else {
		text = toLowerCase(text);
		subsequence = toLowerCase(subsequence);
		if(text[0] == subsequence[0]){
			return isSubsequence(text.substr(1), subsequence.substr(1));
		} else {
			return isSubsequence(text.substr(1), subsequence);
		}
	}
}
