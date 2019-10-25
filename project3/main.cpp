/*
    main.cpp

    Implements the user interface for hangman.

    assignment: CSCI 262 Project - Evil Hangman

    author:

    last modified: 3/7/2019
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

#include "hangman.h"

using namespace std;

// helper function prototypes
int get_integer(string prompt); // return a positive integer
char get_letter(string prompt); // return a valid lowercase letter
bool get_yesno(string prompt);  // return true == yes / false == no
string trim(string s);          // remove leading/trailing whitespace

int main() {
	cout << "Welcome to Hangman!" << endl;
	cout << "===================" << endl << endl;

	// get the hangman object
	hangman game;

	// Keep playing the game until the user decides otherwise
	while (true) {
		// each time the game starts, the list of words is reset, aka filled with each word from dictionary.txt
		game.reset_words();
		int word_size = 0;

		// loops until the word size provided is valid, aka a word of the given size exists in the set
		for (;;) {
			word_size = get_integer("How long of a word would you like?");
			if (game.is_valid_size(word_size)) break;
			cout << "No words of that size found. Try again. ";
		}

		int num_guesses = get_integer("How many guesses would you like? ");
		cout << endl;

		bool spoiled = get_yesno("Do you want the illusion of a fair game to be ruined by being able to see how many words remain?");

		game.start_new_game(word_size, num_guesses, spoiled);

		while (!game.is_won() && !game.is_lost()) {
			cout << "Your word is: " << game.get_display_word() << endl;

			string already_guessed = game.get_guessed_chars();
			if (already_guessed.empty()) {
				cout << "You have not yet guessed any letters." << endl;
			} else {
				cout << "You have already guessed these letters: ";
				cout << already_guessed << endl;
			}

			cout << "You have " << game.get_remaining_guesses();
			cout << " guesses remaining." << endl << endl;

			char guess = get_letter("What is your next guess?");
			while (game.is_guessed(guess)) {
				cout << endl << "You already guessed that!" << endl;
				guess = get_letter("What is your next guess?");
			}
			cout << endl;

			if (game.is_spoiled()) {
				cout << "There are " << game.get_remaining_word_count();
				cout << " words remaining" << endl;
			}

			bool good_guess = game.process_guess(guess);
			if (good_guess) {
				cout << "Good guess!" << endl;
				game.add_guess(guess);
			} else {
				cout << "Sorry, that letter isn't in the word." << endl;
				game.set_remaining_guesses(game.get_remaining_guesses() - 1);
				game.add_guess(guess);
			}

			if (game.is_won()) {
				cout << "Congratulations! You won the game! The word was " << game.display_word << endl;
			}

			if (game.is_lost()) {
				cout << "Oh no! You lost!!!" << endl;
				cout << "My secret word was: " << game.get_hidden_word() << endl;
			}
		}

		cout << endl;
		if (!get_yesno("Would you like to play again (y/n)?")) break;
	}

	cout << endl << "Thank you for playing Hangman." << endl;

	return 0;
}

// Prompt for a positive integer response, re-prompting if invalid
// input is given. This is not super-robust - it really should work
// harder to filter out responses like "123foo", but oh well.
int get_integer(string msg) {
	while (true) {
		string input;
		int result = 0;

		cout << msg << endl;
		getline(cin, input);

		result = atoi(input.c_str());
		if (result > 0) return result;

		cout << "I didn't understand that. Please enter a positive integer.";
		cout << endl;
	}
}

// Prompt for a letter of the alphabet, re-prompting if invalid
// input is given.
char get_letter(string msg) {
	while (true) {
		string input;

		cout << msg << endl;
		getline(cin, input);

		input = trim(input);

		if (input.size()==1) {
			char result = tolower(input[0]);
			if (result >= 'a' && result <= 'z') return result;
		}

		cout << "I didn't understand that. ";
		cout << "Please enter a letter of the alphabet.";
		cout << endl;
	}
}

// Prompt for a yes/no response, re-prompting if invalid
// input is given.
bool get_yesno(string msg) {
	while (true) {
		string input;

		cout << msg << endl;
		getline(cin, input);

		input = trim(input);
		for (int i = 0; i < input.size(); i++) {
			input[i] = tolower(input[i]);
		}

		if (input=="y" || input=="yes") return true;
		if (input=="n" || input=="no") return false;

		cout << "I didn't understand that. ";
		cout << "Please enter y(es) or n(o).";
		cout << endl;
	}
}

string trim(string s) {
	int a, b;

	for (a = 0; a < s.size() && isspace(s[a]); a++);
	for (b = s.size() - 1; b >= a && isspace(s[b]); b--);

	return s.substr(a, b - a + 1);
}


