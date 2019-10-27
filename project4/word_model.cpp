/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019
*/

#include "word_model.h"

void word_model::initialize(string text, int order) {
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

//	ss >> nextWord;
//	cout << "kWORDS: " << " ";
//	for (auto word : kWords) cout << word << " ";
//	cout << " NEXTWORD: " << nextWord << endl;

	_map.emplace(kWords, vector<string>{nextWord});

	while (!ss.eof()) {
		shiftKey(kWords, nextWord);

		ss >> nextWord;
//		cout << "kWORDS: " << " ";
//		for (auto word : kWords) cout << word << " ";
//		cout << " NEXTWORD: " << nextWord << endl;

		if (_map.count(kWords)==0) {
			_map.emplace(kWords, vector<string>{nextWord});
		} else {
			_map.at(kWords).push_back(nextWord);
		}
	}

//	prints out pairs
	int count = 0;
	for (auto pair : _map) {
		if ((pair.second).size() > 1) {
			count++;
			cout << "KEY: ";
			for(auto word : pair.first) cout << word << " ";
			cout << " WORDS: ";
			for (auto word : pair.second) cout << word << " ";
			cout << endl;
		}
	}
	cout << "COUNT: " << count << endl;
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

	unsigned int start = (rand() % words.size() - size) % words.size();

//	cout << "START: " << start << endl;

	vector<string> seed;
	for (int i = 0; i < _order; i++) seed.push_back(words[start + i]);

	for (int i = 0; i < size; i++) {
		vector<string> possibleWords = _map.at(seed);
		int randomIndex = rand() % possibleWords.size();
		string nextWord = possibleWords[randomIndex];

//		cout << "SEED: ";
//		for (auto word : seed) cout << word << " ";
//		cout << " RANDOM INDEX: " << randomIndex << " NEXT WORD: " << nextWord << endl;


		results += " " + nextWord;

		shiftKey(seed, nextWord);
	}

    return results;
}
void word_model::shiftKey(vector<string> &vec, string &str) {
	for (int i = 0; i < vec.size() - 1; i++) {
		vec[i] = vec[i + 1];
	}
	vec[vec.size() - 1] = str;
}
