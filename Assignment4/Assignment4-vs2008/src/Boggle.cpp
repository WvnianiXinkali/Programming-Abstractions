/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "hashset.h"
#include "vector.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const int BOGGLE_BOARD_COLUMN_SIZE = 4;
const int BOGGLE_BOARD_ROW_SIZE = 4;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

struct gameB{
	Grid<char> gameBoard;
	Lexicon usedWords;
};

/* Function prototypes */

void welcome();
void giveInstructions();
void playManyBoggle();
void playBoggle();
void fillTheBoard(gameB& game);
string askUserForLetters();
Vector<string> shuffleBoggleCubes();
void humansTurn(gameB& game, Lexicon& english);
bool wordCanBeFormed(gameB& game, string word);
bool helperWordCanBeFormed(gameB& game, string word,  int row, int collumn, Vector<Vector<int> >& usedBoxes);
bool vecContainsValue(Vector<Vector<int> >& vec, Vector<int>& value);
bool vecEqualsVec(Vector<int>& vec1, Vector<int>& vec2);
void showWordFormed(gameB& game, int length, Vector<Vector<int> >& usedBoxes);
void computersTurn(gameB& game, Lexicon& english);
void helperCompFindsWords(gameB& game,  int row, int collumn, Lexicon& english, string word, Vector<Vector<int> >& usedBoxes);

/* Main program */

int main() {
	//playManyBoggle(); 
	playBoggle();
	
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}



// [TODO: Fill in the rest of the code]
void playManyBoggle(){
	while(true){
		playBoggle();
		int playAgain = getInteger("If you want to play again input 1, otherwise 0: ");
		while(true){
			if(playAgain == 0 || playAgain == 1) {
				break;
			}
			cout << "Please enter 0 or 1;" << endl;
			playAgain = getInteger("If you want to play again input 1, otherwise 0: ");
		}
		if(playAgain == 0){
			cout << "Thanks for playing." << endl;
			break;
		}
	}
}
// This is whole 1 game Boggle match;
void playBoggle(){ 
	GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
	Lexicon english("EnglishWords.dat");
	drawBoard(BOGGLE_BOARD_ROW_SIZE, BOGGLE_BOARD_COLUMN_SIZE);
	Grid<char> gameBoard(BOGGLE_BOARD_ROW_SIZE, BOGGLE_BOARD_COLUMN_SIZE);
	gameB game;
	game.gameBoard = gameBoard;
	fillTheBoard(game);
	humansTurn(game, english);
	cout << "Start of Computer's turn; " << endl;
	computersTurn(game, english);
	cout << "Got Destroyed Didn't YA" << endl;
	cout << "GB LOOSER !!!" << endl;
}

void fillTheBoard(gameB& game){ // Fills grid board as well as fills board on canvas with random letters;
	bool fillAutomatic = getInteger("Please enter 0 if you want to fill the board or 1 if you want us to do it for you: ");
	if(fillAutomatic){
		Vector<string> shuffledCubes = shuffleBoggleCubes();
		for(int i = 0; i < BOGGLE_BOARD_COLUMN_SIZE; ++i){  
			for(int j = 0; j < BOGGLE_BOARD_ROW_SIZE; ++j){
				int index = randomInteger(0, shuffledCubes[0].length() - 1); 
				game.gameBoard[i][j] = shuffledCubes[0][index];
				labelCube(i, j, shuffledCubes[0][index]);
				shuffledCubes.remove(0);
			}
		}
	} else {
		string letters = askUserForLetters();
		for(int i = 0; i < BOGGLE_BOARD_COLUMN_SIZE; ++i){  
			for(int j = 0; j < BOGGLE_BOARD_ROW_SIZE; ++j){
				game.gameBoard[i][j] = letters[0];
				labelCube(i, j, letters[0]);
				letters = letters.substr(1);
			}
		}		
	}
}

string askUserForLetters(){
	string res = getLine("Enter a string of letters you want to play with: ");
	while(res.length() < BOGGLE_BOARD_COLUMN_SIZE*BOGGLE_BOARD_ROW_SIZE){
		cout << "String you entered is too short enter again." << endl;
		res = getLine("Enter a string of letters you want to play with: ");
	}
	return res.substr(0, BOGGLE_BOARD_COLUMN_SIZE*BOGGLE_BOARD_ROW_SIZE);
}

Vector<string> shuffleBoggleCubes(){ // Jams the array;
	Vector<string> tmpCubes;
	for(int i = 0; i < BOGGLE_BOARD_COLUMN_SIZE*BOGGLE_BOARD_ROW_SIZE; ++i){
		tmpCubes.add(STANDARD_CUBES[i]);
	}

	for (int i = 0; i < tmpCubes.size(); ++i) {
		int randPos = randomInteger(i, tmpCubes.size() - 1);
		string temp = tmpCubes[i];
		tmpCubes[i] = tmpCubes[randPos];
		tmpCubes[randPos] = temp;
	}
	cout << tmpCubes << endl;
	return tmpCubes;
}
/*
Lets user input word and checks if the word is available and reacts accordingly,
if it is not formable lets player know it, if it is formable than adds human a score;
*/
void humansTurn(gameB& game, Lexicon& english){ 
	cout << endl;
	cout << endl;
	cout << "Start of HUMAN's turn." << endl;
	while(true){
		string word = getLine("Please enter a guessing word: ");
		word = toUpperCase(word);
		if(word.empty()){
			cout << "End of HUMAN's turn." << endl;
			break;
		}
		if(word.length() < 4){
			cout << "Word rejected cuz too small." << endl;
			continue;
		}
		if(!english.contains(word)){
			cout << "Word rejected because it is not in da dictionary." << endl;
			continue;
		}
		if(game.usedWords.contains(word)){
			cout << "Word rejected because you have already used it." << endl;
			continue;
		}
		
		if(!wordCanBeFormed(game, word)){
			cout << "Word rejected because it cannot be formmed on the board." << endl;
			continue; 
		}
		game.usedWords.add(word);
		recordWordForPlayer(word, HUMAN);
	}
}
// This function checks if the word human guessed can be formed on the board; 
bool wordCanBeFormed(gameB& game, string word) {
	Vector<Vector<int> > usedBoxes;
	for(int i = 0; i < BOGGLE_BOARD_COLUMN_SIZE; ++i){
		for(int j = 0; j < BOGGLE_BOARD_ROW_SIZE; ++j){
			if(helperWordCanBeFormed(game, word, i, j, usedBoxes)){
				showWordFormed(game, word.length(), usedBoxes);
				return true;
			}
		}
	}
	return false;
}
/* This function helps to check if the word human guessed can be formed on the board,
   by checking every ward form a point on the grid;
*/	
bool helperWordCanBeFormed(gameB& game, string word,  int row, int collumn, Vector<Vector<int> >& usedBoxes){
	Vector<int> currBox;
	currBox.add(row);
	currBox.add(collumn);
	if(word.empty()){
		return true;
	}else if (!(row >= 0 && row < BOGGLE_BOARD_ROW_SIZE && collumn >= 0 && collumn < BOGGLE_BOARD_COLUMN_SIZE)){
		return false;
	}else if(!startsWith(word, game.gameBoard[row][collumn])){
		return false;
	}else if(!vecContainsValue(usedBoxes, currBox)){
		usedBoxes.add(currBox);
		bool up = helperWordCanBeFormed(game, word.substr(1), row, collumn - 1, usedBoxes);
		bool down = helperWordCanBeFormed(game, word.substr(1), row, collumn  + 1, usedBoxes);
		bool right = helperWordCanBeFormed(game, word.substr(1), row + 1, collumn, usedBoxes);
		bool left = helperWordCanBeFormed(game, word.substr(1), row - 1, collumn, usedBoxes);
		bool diagTopR = helperWordCanBeFormed(game, word.substr(1), row + 1, collumn - 1, usedBoxes);
		bool diagTopL = helperWordCanBeFormed(game, word.substr(1), row - 1, collumn - 1, usedBoxes);
		bool diagBotR = helperWordCanBeFormed(game, word.substr(1), row + 1, collumn + 1, usedBoxes);
		bool diagBotL = helperWordCanBeFormed(game, word.substr(1), row - 1, collumn + 1, usedBoxes);
		bool answ = up || down || right || left || diagTopR || diagTopL || diagBotR || diagBotL;
		if(!answ){
			usedBoxes.remove(usedBoxes.size() - 1);
		}
		return answ;
	}
	return false;
}
// returns true if vec contains a value, false otherwise;
bool vecContainsValue(Vector<Vector<int> >& vec, Vector<int>& value){
	for(int i = 0; i < vec.size(); ++i){
		if(vecEqualsVec(vec[i], value)){
			return true;
		}
	}
	return false;
}
// returns true if vec equals vec, false otherwise;
bool vecEqualsVec(Vector<int>& vec1, Vector<int>& vec2){
	if(vec1.size() != vec2.size()){
		return false;
	}
	if(vec1.size() == 0 || vec2.size() == 0){
		return true;
	}
	for(int i = 0; i < vec1.size(); i ++){
		if(vec1[i] != vec2[i]){
			return false;
		}
	}
	return true;
}
// shows human guessed words with highlight marker;
void showWordFormed(gameB& game, int length, Vector<Vector<int> >& usedBoxes){
	for(int i = 0; i < length; i ++){
		highlightCube(usedBoxes[i][0], usedBoxes[i][1], true);
		pause(500);
		highlightCube(usedBoxes[i][0], usedBoxes[i][1], false);
	}
}
// calculates all the words on the board available and adds to computer score accordignly;
void computersTurn(gameB& game, Lexicon& english){
	string word = "";
	for(int i = 0; i < BOGGLE_BOARD_COLUMN_SIZE; ++i){
		for(int j = 0; j < BOGGLE_BOARD_ROW_SIZE; ++j){
			Vector<Vector<int> > usedBoxes;
			helperCompFindsWords(game, i, j, english, word, usedBoxes);
		}
	}
}
// This function helps finding every word on the board by finding every  word on the grid from a specific point that comes from computersTurn function;
void helperCompFindsWords(gameB& game,  int row, int collumn, Lexicon& english, string word, Vector<Vector<int> >& usedBoxes){
	Vector<int> currBox;
	currBox.add(row);
	currBox.add(collumn);
	if(word.length() > 3 && english.contains(word) && !game.usedWords.contains(word)){
		game.usedWords.add(word);
		recordWordForPlayer(word, COMPUTER);	
	}else if (row >= 0 && row < BOGGLE_BOARD_ROW_SIZE && collumn >= 0 && collumn < BOGGLE_BOARD_COLUMN_SIZE && english.containsPrefix(word)){
		if(!vecContainsValue(usedBoxes, currBox)){
			usedBoxes.add(currBox);
			helperCompFindsWords(game, row, collumn - 1, english, word + game.gameBoard[row][collumn], usedBoxes);
			helperCompFindsWords(game, row, collumn  + 1, english, word + game.gameBoard[row][collumn], usedBoxes);
			helperCompFindsWords(game, row + 1, collumn, english, word + game.gameBoard[row][collumn],usedBoxes);
			helperCompFindsWords(game, row - 1, collumn, english, word + game.gameBoard[row][collumn],usedBoxes);
			helperCompFindsWords(game, row + 1, collumn - 1, english, word + game.gameBoard[row][collumn],usedBoxes);
			helperCompFindsWords(game, row - 1, collumn - 1, english, word + game.gameBoard[row][collumn],usedBoxes);
			helperCompFindsWords(game, row + 1, collumn + 1, english, word + game.gameBoard[row][collumn],usedBoxes);
			helperCompFindsWords(game, row - 1, collumn + 1, english, word + game.gameBoard[row][collumn],usedBoxes);
			usedBoxes.remove(usedBoxes.size() - 1);
		}
	}
}