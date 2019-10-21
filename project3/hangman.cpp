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
    fill_words();
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int ws, int ng, bool s) {
    set_word_size(ws);
    set_remaining_guesses(ng);
    set_spoiled(s);
    guessed_chars = "";
    fill_words();

    // sets display word to the correct number of dashes
    display_word = "";
    for (int i = 0; i < ws; i++) display_word += "-";

    // removes words from set if they aren't the right size
    set<string> new_word_set;

    for (auto word : words) {
    	if (word.size() == ws) {
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
	// get biggest word family
	map<string, set<string>> word_families = get_word_families(c);

	unsigned int max_family_size = 0;
	string key;
	for (const auto& set : word_families) {
		if ((set.second).size() > max_family_size) {
			max_family_size = (set.second).size();
			key = (set.first);
		}
	}

	for (const auto& word : (word_families.at(key))) cout << word << endl;
	words = word_families.at(key);

	// updates display word
	display_word = key;

	for (auto character : key) {
		if (character == c) return true;
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


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return guesses_remaining;
}


// get_guessed_chars()
//
// What letters has the player already guessed? Return in alphabetic order.
string hangman::get_guessed_chars() {
    return guessed_chars;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for (char character : guessed_chars) {
    	if (character == c) return true;
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    for (char character : display_word) {
    	if (character == '-') return false;
    }
    return true;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    return guesses_remaining == 0;
}


// get_hidden_words()
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    auto iter = words.begin();
    int random = rand() % words.size();

    for (int i = 0; i < random; i++) {
    	iter++;
    	if (iter == words.end()) iter = words.begin();
    }

	return *iter;
}

// get_max_word_size()
//
// Returns the number of words in the set<string> words
int hangman::get_max_word_size() {
	unsigned int max_size = 0;
	for (const auto& word : words) {
		if (word.size() > max_size) {
			max_size = word.size();
		}
	}

	return (int)max_size;
}

void hangman::set_spoiled(bool s) {
	spoilers = s;
}

void hangman::set_word_size(int s) {
	word_size = s;
}

void hangman::set_remaining_guesses(int g) {
	guesses_remaining = g;
}

map<string, set<string>> hangman::get_word_families(char guess) {
	map<string, set<string>> word_families;

	for (string word : words) {
		// loops through each word and determines which word family it belongs to
		string key = display_word;

		for (int j = 0; j < word.size(); j++) {
			if (word[j] == guess) {
				key[j] = guess;
			}
		}

		if (word_families.count(key) != 0) {
			(word_families.at(key)).insert(word);
		} else {
			word_families.emplace(key, set<string>{word});
		}
	}

	return word_families;
}

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

void hangman::add_guess(char c) {
	guessed_chars += c;
	sort_guessed_characters();
}
bool hangman::is_spoiled() {
	return spoilers;
}

int hangman::get_remaining_words() {
	return words.size();
}
void hangman::fill_words() {
	fstream scanner("dictionary.txt");

	string word;
	while (!scanner.eof()) {
		getline(scanner, word);
		words.insert(word);
	}
}

