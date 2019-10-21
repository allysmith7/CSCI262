/*
    hangman.cpp

    Method implementations for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman

    author:

    last modified: 3/7/2019
*/

#include <fstream>
#include <iostream>
#include "hangman.h"

using namespace std;

// constructor
hangman::hangman() {
	// fills the set with all words from ./cmake-build-debug/dictionary.txt
	reset_words();
}

// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int ws, int ng, bool s) {
	set_word_size(ws);
	set_remaining_guesses(ng);
	set_spoiled(s);
	guessed_chars = "";
	// fills the set with all words from ./cmake-build-debug/dictionary.txt
	reset_words();

	// sets display word to the correct number of dashes
	display_word = "";
	for (int i = 0; i < ws; i++) display_word += "-";

	// removes words from set if they aren't the right size
	set<string> new_word_set;

	for (auto word : words) {
		if (word.size()==_word_size) {
			new_word_set.insert(word);
		}
	}
	words = new_word_set;
}

// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word. If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
	// get word families
	map<string, set<string>> word_families = get_word_families(c);

	// finds the word family that has the most words and stores the key
	unsigned int max_family_size = 0;
	string key;
	for (const auto &set : word_families) {
		if ((set.second).size() > max_family_size) {
			max_family_size = (set.second).size();
			key = (set.first);
		}
	}

//	for (const auto& word : (word_families.at(key))) cout << word << endl;
	words = word_families.at(key);

	// updates display word
	display_word = key;

	// returns based on if the guess is in the new display word, aka the guess was in the word
	for (auto character : key) {
		if (character==c) return true;
	}
	return false;
}

// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
	return display_word;
}

// get_remaining_guesses()
//
// Return the number of guesses remaining for the player.
int hangman::get_remaining_guesses() {
	return _guesses_remaining;
}

// get_guessed_chars()
//
// What letters has the player already guessed? Return in alphabetic order.
string hangman::get_guessed_chars() {
	return guessed_chars;
}

// is_guessed()
//
// Return true if letter was already guessed.
bool hangman::is_guessed(char c) {
	for (char character : guessed_chars) {
		if (character==c) return true;
	}
	return false;
}

// is_won()
//
// Checks to see if the display word contains any unguessed letters, '-', and if it doesn't it returns true
bool hangman::is_won() {
	for (char character : display_word) {
		if (character=='-') return false;
	}
	return true;
}

// is_lost()
//
// Return true if there are no guesses remaining
bool hangman::is_lost() {
	return _guesses_remaining==0;
}

// get_hidden_words()
//
// Returns a (semi-)random word from the list of words that remains once all guesses have been used
string hangman::get_hidden_word() {
	auto iter = words.begin();
	int random = rand()%words.size();

	for (int i = 0; i < random; i++) {
		iter++;
		if (iter==words.end()) iter = words.begin();
	}

	return *iter;
}

void hangman::set_spoiled(bool s) {
	spoilers = s;
}

void hangman::set_word_size(int s) {
	_word_size = s;
}

void hangman::set_remaining_guesses(int g) {
	_guesses_remaining = g;
}

// get_word_families
//
// returns a map with a key of type string and a value of type set<string> that holds all different word families
map<string, set<string>> hangman::get_word_families(char guess) {
	map<string, set<string>> word_families;

	for (string word : words) {
		// loops through each word and determines which word family it belongs to
		string key = display_word;

		// if the letter in the real word is the guess, it is filled in
		for (int j = 0; j < word.size(); j++) {
			if (word[j]==guess) {
				key[j] = guess;
			}
		}

		// if a word family exists, the new word is added to the existing set
		if (word_families.count(key)!=0) {
			(word_families.at(key)).insert(word);
			// otherwise, a new pair is created with the key and a set with the word in it
		} else {
			word_families.emplace(key, set<string>{word});
		}
	}

	return word_families;
}

// sort_guessed_characters()
//
// takes all of the characters that have been guessed and puts them in alphabetical order using a set
void hangman::sort_guessed_characters() {
	string characters = get_guessed_chars();
	set<char> sorted;
	string sorted_characters;

	for (char character : characters) {
		sorted.insert(character);
	}

	for (auto character : sorted) {
		sorted_characters += character;
	}

	guessed_chars = sorted_characters;
}

// add_guess()
//
// adds a character to the string of guessed_chars and sorts it
void hangman::add_guess(char c) {
	guessed_chars += c;
	sort_guessed_characters();
}

bool hangman::is_spoiled() {
	return spoilers;
}

int hangman::get_remaining_word_count() {
	return words.size();
}

// reset_words()
//
// Takes every word from ./cmake-build-debug/dictionary.txt and puts it into the set<string> words
void hangman::reset_words() {
	fstream scanner("dictionary.txt");

	string word;
	while (!scanner.eof()) {
		getline(scanner, word);
		words.insert(word);
	}
}

// is_valid_size()
//
// Returns true if a word of the specified size exists in the set
bool hangman::is_valid_size(int size) {
	for (auto word : words) {
		if (word.size()==size) return true;
	}
	return false;
}

