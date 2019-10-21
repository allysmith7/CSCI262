/*
    rwg.h

    Author: C. Painter-Wakefield

    Last modified: 1/25/2019

    Class declaration for the rwg class. rwg == random word generator.  An
    rwg object is initialized with a dictionary and then generates words of
    different lengths, at random.

    The basic algorithm is as follows:
    given a dictionary of words and the number of words to generate,
    rwg will randomly generate a vector of integers representing the
    lengths of the words to generate (from the min length to the max
    length stored in the dictionary).  It will then proceed to generate,
    for each length, a random word of that length from the dictionary.

    This is a silly algorithm.
*/

#ifndef _RWG_H
#define _RWG_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class rwg {
public:
	// constructors - either create an rwg and then initialize with an
	// istream to a dictionary, or do in one step.
	rwg() { _min_length = 0; _max_length = 0; }
	rwg(istream &in) { initialize(in); }

	// read in words from the provide istream for our dictionary
	void initialize(istream &);

    // do a simple self-test to make sure we read in the dictionary
    void self_test();   

	// generate n words on the provided ostream out (cout by default)
	void generate(int n, ostream& out = cout);

	// return whether or not the dictionary is empty
	bool is_empty();

	// get the min/max lengths available
	// Note: inline functions like these are often not accessible within 
	// the debugger :(  Have to look at the actual private vars.
	int get_min_length() { return _min_length; }
	int get_max_length() { return _max_length; }

private:
	// holds the dictionary - _words[len] holds all words of length len 
	vector<vector<string>> _words;
	int _min_length;
	int _max_length;

	// helper methods
	vector<int> _get_lengths(int n);  // get n random lengths in [min, max]
	string _get_word(int length);  // get a random word of size length
	vector<string> _get_words(int length); // get all words of size length
};

#endif
