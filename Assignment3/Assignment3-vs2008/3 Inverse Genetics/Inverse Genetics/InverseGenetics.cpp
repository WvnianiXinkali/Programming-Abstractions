/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();
void Helper1(Vector<Set<string> >& v, string protein, Map<char, Set<string> >& codons);
void HelperListAllRNAStrandsFor(Vector<Set<string> >& v, int index, Set<string>& temp);
void printRNAstrand(Set<string>& temp);

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	listAllRNAStrandsFor("NKWL", codons);
    /* [TODO: Implement this!] */
    return 0;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){ // KWL [UUA UUU,] UUG,] UUP UUC GGA]
	Vector<Set<string> > v;
	Helper1(v, protein, codons);
	int index = 0;
	cout << v << endl;
	Set<string> temp;
	HelperListAllRNAStrandsFor(v, index, temp);
}

void HelperListAllRNAStrandsFor(Vector<Set<string> >& v, int index, Set<string>& temp){// This function calculates all RNA strands and prints them;
	if(index >= v.size()){
		printRNAstrand(temp);
	} else {	
		foreach (string comb in v[index]){
				v[index].remove(comb);
				temp.add(comb);
				HelperListAllRNAStrandsFor(v, index + 1, temp);
				v[index].add(comb);
				temp.remove(comb);
		}
	}
}

void printRNAstrand(Set<string>& temp){
	cout << temp << ": ";
	string temp1;
	foreach (string tempStr in temp){
		temp1 += tempStr;
	}
	cout << temp1 << endl;
}

void Helper1(Vector<Set<string> >& v, string protein, Map<char, Set<string> >& codons){ // This function converts protein string to Vector that contains all combination sets of protein letters;
	if(protein.length() != 0){	
		v.add(codons.get(protein[0]));
		Helper1(v, protein.substr(1), codons);
	}
}




/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
