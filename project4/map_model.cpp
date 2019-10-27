/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019
*/

#include "map_model.h"

void map_model::initialize(string text, int order) {
	/*
	 * This function loops through text and creates a map of substrings of size order with a vector<char> as the value
	 * that contains the letters that are to follow said substring
	 */

	_text = text;
	_order = order;

	for (int i = 0; i < text.size() - order; i++) {
		string substr = text.substr(i, order);
		string nextChar = text.substr(i + order, 1);
//		cout << "SUBSTR: " << substr << " NEXTCHAR: " << nextChar << endl;

		if (_map.count(substr)==0) {
			_map.emplace(substr, vector<string>{nextChar});
		} else {
			_map.at(substr).push_back(nextChar);
		}
	}
}

string map_model::generate(int size) {
	// This function will take the seed and use it to generate a random block of text of the specified size
	string results;

	// pick random k-character substring as initial seed
	int start = rand() % (_text.length() - _order);
	string seed = _text.substr(start, _order);

	// loops size times
	for (int i = 0; i < size; i++) {
//		cout << "RUNNING " << i << " SEED: " << seed << " RESULTS: " << results << endl;
		if (_map.count(seed) > 0) {
			vector<string> possibleChars = _map.at(seed);

			int randomIndex = rand() % possibleChars.size();
			string nextChar = possibleChars[randomIndex];
//			cout << "SEED: " << seed << " RANDOM INDEX: " << randomIndex << " NEXT CHAR: " << nextChar << endl;

			results += nextChar;

			seed = seed.substr(1) + nextChar;
		}
	}

	return results;
}
