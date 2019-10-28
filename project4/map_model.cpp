/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Lucas Henke

   Modified: 10/24/2019
*/

#include "map_model.h"

/*
 * This function loops through text and creates a map of substrings of size order with a vector<char> as the value
 * that contains the letters that are to follow said substring
 */
void map_model::initialize(string text, int order) {
	// stores values for use in the generate function
	_text = text;
	_order = order;

	// loops through the whole text
	for (int i = 0; i < text.size() - order; i++) {
		// stores a substring of size order
		string substr = text.substr(i, order);

		// gets the subsequent character
		string nextChar = text.substr(i + order, 1);

		// if the key exists in the map, the next character is appended to the already existing vector
		// otherwise, a new entry is created
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
	int start = rand() % (_text.length() + _order);
	string seed = _text.substr(start, _order);

	// loops size times
	for (int i = 0; i < size; i++) {
		if (_map.count(seed) > 0) {
			// gets possible subsequent characters
			vector<string> possibleChars = _map.at(seed);

			// generates a random index and gets the character at that index
			int randomIndex = rand() % possibleChars.size();
			string nextChar = possibleChars[randomIndex];

			results += nextChar;

			// set the new seed to be the seed without the 0th index + the next character
			seed = seed.substr(1) + nextChar;
		}
	}

	return results;
}
