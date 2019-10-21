#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h

    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman

    author:

    last modified: 9/24/2017
*/

#include <string>
#include <set>
#include <map>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
  	string guessed_chars;
  	string display_word;
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int word_size, int num_guesses, bool spoilers);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

    // Sets the spoilers variable
    void set_spoiled(bool s);

    // Sets the word size
    void set_word_size(int s);

    // returns number of words
    int get_max_word_size();

	// Sets remaining guesses
	void set_remaining_guesses(int g);

	// Adds a guess to the guessed characters
  	void add_guess(char c);

	// returns the value of spoilers
	bool is_spoiled();

	// returns how many words remain in the set
	int get_remaining_words();


private:
	// holds all of the words
	set<string> words;
	bool spoilers;

	int word_size;

	int guesses_remaining;

	// Holds a map based on the word family as the key and a set of words  that fall under that family
	map<string, set<string>> get_word_families(char guess);
	// Sorts the guessed characters
	void sort_guessed_characters();
  void fill_words();
};

#endif
