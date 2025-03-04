/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {
    /* TODO: Add testing code here! */
	Set<string> cities;
	cities.add("A");
	cities.add("B");
	cities.add("C");
	cities.add("D");
	cities.add("E");
	cities.add("F");
	Vector <Set<string> > locations;
	Set<string> x;
	x.add("A");
	x.add("B");
	x.add("C");
	Set<string> y;
	y.add("A");
	y.add("C");
	y.add("D");
	Set<string> z;
	z.add("B");
	z.add("F");
	Set<string> k;
	k.add("C");
	k.add("E");
	k.add("F");
	locations.add(x);
	locations.add(y);
	locations.add(z);
	locations.add(k);
	int numHospitals = 3;
	Vector <Set<string> > result;
	cout << canOfferUniversalCoverage(cities, locations, numHospitals, result) << endl;
	cout << result << endl;
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
							   Vector< Set<string> >& result){
		if(cities.isEmpty()){
			return true;
		} else if(numHospitals <= 0){
			return false;
		} 	else {
			for(int i = 0; i < locations.size(); i ++){
				Set <string> p = locations[i];
				locations.remove(i);
				result.add(p);
				cities = cities - p;
				bool res = canOfferUniversalCoverage(cities, locations, numHospitals  - 1, result);	
				if(res) return true;
				locations.add(p);
				result.remove(result.size() - 1);
				cities = cities + p;
			}	
		}
		return false;
}