/*
    lab07a.cpp

    Author: C. Painter-Wakefield

    Created: 10/10/2018

    Starter code for lab 7, provides initial code to load in a dictionary
    of words, and run time tests on how long it takes to search for them.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>      // for clock()
#include <algorithm>  // for find()
#include <vector>
#include <set>

using namespace std;


/*************/
/* CONSTANTS */
/*************/
static const int TEST_SIZE = 5000;	// how many trials will we time?


/********/
/* MAIN */
/********/
int main() {
    // open dictionary and read in all the words
	cout << "Reading dictionary... ";
    ifstream fins("dictionary.txt");
    if (!fins) {
        cerr << "Could not open 'dictionary.txt' for reading, exiting." << endl;
        return -1;
    }


    set<string> words_set;
    string word;
	clock_t start, stop;  // stores the start/stop clock values

	cout << "Timing Set...";
	start = clock();
    while (!fins.eof()) {
        getline(fins, word);
        words_set.insert(word);
    }
    fins.close();
    stop = clock();
	cout << "done." << endl;

	// This next line takes the elapsed "clock time" and converts to seconds
	double seconds = (stop - start) / double(CLOCKS_PER_SEC);

	cout << "Filled set in " << seconds << endl;

	cout << "Rereading dictionary... ";
	ifstream finv("dictionary.txt");
	if (!finv) {
		cerr << "Could not open 'dictionary.txt' for reading, exiting." << endl;
		return -1;
	}

	vector<string> words_vec;

	cout << "Timing Vector...";
	start = clock();
	while (!finv.eof()) {
		getline(finv, word);
		words_vec.push_back(word);
	}
	finv.close();
	stop = clock();
	cout << "done." << endl;

	// This next line takes the elapsed "clock time" and converts to seconds
	seconds = (stop - start) / double(CLOCKS_PER_SEC);

	cout << "Filled set in " << seconds << endl;

    return 0;
}
