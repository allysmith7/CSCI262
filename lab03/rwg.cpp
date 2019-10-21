/*
    rwg.cpp

    Author: C. Painter-Wakefield

    Last modified: 1/25/2019

    Class method definitions for the rwg class.
*/

#include "rwg.h"

#include <limits>
#include <cstdlib>
#include <ctime>

// initialize(istream &in)
//
// Read in all words from the istream and populate our words collection,
// organized by the length of the words
void rwg::initialize(istream& in) {
	// initialize the random number generator to get a different
	// sequence every time
	srand(time(NULL));

	_min_length = 10000; // surely no words this long?
	_max_length = 0;

	string word;

	// first, find min/max lengths of words
	while (!in.eof()) {
		in >> word;
		int len = word.length();

		if (len != 0) {
			if (len < _min_length) _min_length = len;
			if (len > _max_length) _max_length = len;
		}

		// make sure we have a vector entry for this length!
		while (_words.size() < len + 1) {
			_words.push_back({});
		}
	}

	// now, rewind and fill our data structure
	in.clear();     // clear eof
	in.seekg(0);    // go to start
	while (!in.eof()) {
		in >> word;
		int len = word.length();

		if (len != 0) {
			_words[len].push_back(word);
		}
	}
}

// is_empty()
//
// Return whether or not the dictionary has no words.
bool rwg::is_empty() {
	return _max_length == 0;
}

// self_test()
//
// Just print out the first word of each length, to make sure we
// read in the dictionary correctly
void rwg::self_test() {
	cout << "Performing self test:" << endl;
	for (int i = _min_length; i <= _max_length; i++) {
		if (_words.at(i).size() > 0) {
			cout << "length " << i << ": ";
			cout << _words.at(i).at(0) << endl;
		}
	}
	cout << endl;
	cout << "Self test successful!" << endl << endl;
}

// generate(int n, ostream& out)
//
// Generate n random words and output on the provided ostream.
void rwg::generate(int n, ostream& out) {
	vector<int> lengths = _get_lengths(n);
	for (int len: lengths) {
		out << _get_word(len) << ' ';
	}
	out << endl;
}

// private helper methods

// _get_lengths(int n)
//
// Generate a vector of n random lengths between _min_length and _max_length
vector<int> rwg::_get_lengths(int n) {
	vector<int> lengths(n);
	for (int i = 0; i < n; i++) {
		// generate a random number between _min_length and _max_length
		int r = rand() % (_max_length - _min_length) + _min_length;
		while (_words[r].size() == 0) {
			r = rand() % (_max_length - _min_length) + _min_length;
		}
		lengths[i] = r;
	}
	return lengths;
}

// _get_word(int len)
//
// Return one randomly selected word of length len
string rwg::_get_word(int len) {
	vector<string> possible_words = _get_words(len);

	// get a random word
	int idx = rand() % (possible_words.size() + 1);
	return possible_words[idx];
}

// _get_words(int len)
//
// Return all words of the specified length
vector<string> rwg::_get_words(int len) {
	return _words.at(len);
}
