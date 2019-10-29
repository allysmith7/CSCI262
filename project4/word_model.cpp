/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Cole Smith

   Modified: 10/28/2019
*/

#include "word_model.h"

void word_model::initialize(string text, int order) {
	// stores text and order value for use in the generate method
	_text = text;
	_order = order;

	stringstream ss(_text);

	string currentWord;
	vector<string> kWords;
	string nextWord;

	// create first entry in the map
	for (int i = 0; i < order; i++) {
		if (!ss.eof()) ss >> currentWord;
		kWords.push_back(currentWord);
	}

	// adds first entry to map
	_map.emplace(kWords, vector<string>{nextWord});

	// loops through all words in the file
	while (!ss.eof()) {
		shiftKey(kWords, nextWord);

		ss >> nextWord;

		// if the key exists, the next word is added to the already existing vector
		// otherwise, it creates the entry
		if (_map.count(kWords)==0) {
			_map.emplace(kWords, vector<string>{nextWord});
		} else {
			_map.at(kWords).push_back(nextWord);
		}
	}
}

string word_model::generate(int size) {
	string results;

	// puts all words into a vector
	stringstream ss(_text);
	vector<string> words;
	string s;
	while (!ss.eof()) {
		ss >> s;
		words.push_back(s);
	}

	// finds the index of the word that will start the output
	unsigned int start = rand()%(words.size() + size);

	vector<string> seed;
	// adds the first 3 words to the seed vector
	for (int i = 0; i < _order; i++) seed.push_back(words[start + i]);

	// loops size times in order to generate the output
	for (int i = 0; i < size; i++) {
		// gets the possible words given the seed
		vector<string> possibleWords = _map.at(seed);

		// generates a random index
		int randomIndex = rand()%possibleWords.size();

		// stores the word from the vector at the index
		string nextWord = possibleWords[randomIndex];

		// appends the new word to the results
		results += " " + nextWord;

		shiftKey(seed, nextWord);
	}

	return results;
}

// This method is a helper method in order to move the 1st and 2nd index into the 0th and first, respectively, as well
// as putting str in the 2nd index
void word_model::shiftKey(vector<string> &vec, string &str) {
	for (int i = 0; i < vec.size() - 1; i++) {
		vec[i] = vec[i + 1];
	}
	vec[vec.size() - 1] = str;
}
