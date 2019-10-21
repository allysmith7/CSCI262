#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "personality_test.h"

using namespace std;

/* Load method
 * 1) Provided an istream object, read in each line and process them accordingly
 * 2) Ensure to see if the input is "correct" (do at least one simple check, like first character is a number)
 * Input: istream object
 * Output: Boolean
 */
bool personality_test::load(istream &in) {
	string current_line;
	int numberOfQuestions;

	in >> numberOfQuestions;
	// removes the "Questions to analyze your personality!" from the buffer
	getline(in, current_line);

	// loops through each line
	for (int i = 0; i < numberOfQuestions; i++) {
		getline(in, current_line);

		// gets the category id
		stringstream ss(current_line);
		string category_id;
		ss >> category_id;

		// attempts to convert the word to an int. if it can't, then the line doesn't begin with an int so the function returns false
		try {
			stoi(category_id);
		} catch (invalid_argument &e) {
			return false;
		}

		// checks that the subsequent two letters are any of the following: E F I J N P S T
		string letter1, letter2;
		ss >> letter1 >> letter2;

		vector<string> valid_letters = {"E", "F", "I", "J", "N", "P", "S", "T"};
		bool letterOneIsValid = false;
		bool letterTwoIsValid = false;

		for (string letter : valid_letters) {
			if (letter1==letter) {
				letterOneIsValid = true;
			}
			if (letter2==letter) {
				letterTwoIsValid = true;
			}
		}

		if (!(letterOneIsValid && letterTwoIsValid)) {
			return false;
		}

		// gets the remaining part of the line as the question
		string sentence;
		string current_word;
		getline(ss, sentence);

		// creates new object of type <question> and adds it to the vector
		question q(sentence, letter1, letter2, category_id);
		questions.push_back(q);
	}

	return true;
}

/* personality_test::printout method
 * 1) Printout the questions to ensure that the load method was written correctly
 * This part will not be graded, just for your own check
 */
void personality_test::printout() {
	cout << "called printout" << endl;

	for (question q : questions) {
		cout << q.sentence << q.yes_option << q.no_option << q.category_id << endl;
	}
}

/* Run Test method
 * 1) Call proper methods in order to run the test
 * @param: None
 * @return: None, Text to Console
 */
void personality_test::run_test() {
	// runs the test and stores the result
	string output = analyze_personality();

	categorize_output(output);
}

/* Analyze Personality Method
 * 1) Ask user one question at a time
 * 2) Read in user's response and construct a vector containing the responses
 * 3) Analyze the responses to construct a personality type (eg. ENFJ)
 * @param None
 * @return string
 */
string personality_test::analyze_personality() {
	// the vector that holds the responses is in the format {E, I, S, N, T, F, J, P} so that we can compare the consecutive indices later on
	vector<int> results = {0, 0, 0, 0, 0, 0, 0, 0};

	// tells user how to respond
	cout
		<< "To answer a question, type 'Y', 'N', 'y', 'n', 'yes', 'no,'Yes', 'No', 'YES', or 'NO' to each of the questions"
		<< endl << endl;

	// loops through each question in the vector
	for (question q : questions) {
		// prints out the question to the terminal
		cout << q.sentence + " " << endl;

		// attempts to get user input until a valid answer is received
		string input;
		while (true) {
			cin >> input;

			// verifies that the input is yes or no
			if (input=="Y" || input=="y" || input=="yes" || input=="Yes" || input=="YES") {
				// checks which option the question's yes value was, and increments that index in the vector
				if (q.yes_option=="E") {
					results[0]++;
				} else if (q.yes_option=="I") {
					results[1]++;
				} else if (q.yes_option=="S") {
					results[2]++;
				} else if (q.yes_option=="N") {
					results[3]++;
				} else if (q.yes_option=="T") {
					results[4]++;
				} else if (q.yes_option=="F") {
					results[5]++;
				} else if (q.yes_option=="J") {
					results[6]++;
				} else if (q.yes_option=="P") {
					results[7]++;
				}
				break;
			} else if (input=="N" || input=="n" || input=="no" || input=="No" || input=="NO") {
				if (q.no_option=="E") {
					results[0]++;
				} else if (q.no_option=="I") {
					results[1]++;
				} else if (q.no_option=="S") {
					results[2]++;
				} else if (q.no_option=="N") {
					results[3]++;
				} else if (q.no_option=="T") {
					results[4]++;
				} else if (q.no_option=="F") {
					results[5]++;
				} else if (q.no_option=="J") {
					results[6]++;
				} else if (q.no_option=="P") {
					results[7]++;
				}
				break;
			} else {
				// if the user doesn't input a recognized answer to mean yes or no, the program will not accept it and
				// will prompt the user for a valid response
				cout << "Input not recognized, please try again." << endl;
			}
		}
	}

	// analyzes results
	string output;
	// adds the letter to the output based on which index holds the larger value
	output += results[0] > results[1] ? "E" : "I";
	output += results[2] > results[3] ? "S" : "N";
	output += results[4] > results[5] ? "T" : "F";
	output += results[6] > results[7] ? "J" : "P";

	return output;
}

/* Categorize Output Method
 * 1) Read in the analysis.txt file
 * 2) Provided a user's personality type, print out to console the user's personality description
 * @param Personality type string (eg. "ENFJ")
 * @return None, Text to console
 */
void personality_test::categorize_output(string my_personality) {
	string letters;
	string category;
	string type;
	string desc;

	while (true) {
		// gets the file and opens it
		string fileName;
		cout << "Please enter the input file name, e.g., \"analysis.txt\": ";
		cin >> fileName;

		ifstream questions_file(fileName);

		if (!questions_file.is_open()) {
			cout << "Error opening file " << fileName << ". Please try again." << endl;
			continue;
		}

		// finds the number of lines in the file
		string numberOfLines;
		getline(questions_file, numberOfLines);
		int numLines = stoi(numberOfLines);

		// loops through each line of the file
		if (questions_file.is_open()) {
			for (int i = 0; i < numLines; i++) {
				string current_line;
				getline(questions_file, current_line);

				// stores the values from the line in the corresponding variables
				stringstream ss(current_line);
				ss >> letters >> category >> type;
				string word;
				getline(ss, desc);

				// if the matching letter combination is found, the loop will break
				if (my_personality==letters) {
					break;
				}
			}
			break;
		}
		// if the file fails to open, the user will be prompted again to enter a file name
		cout << "Error opening file " << fileName << ". Please try again." << endl;
	}

	// puts the output into a string variable
	string output =
		"Personality type: " + my_personality + "\n\nCategory: " + category + "\n\nType: " + type + "\n\nDescription: "
			+ desc;

	// prints out the values
	cout << output << endl;

	// saves the output, if the user desires
	save_output(output);
}

/* Save Output
 * 1) Ask user to save or not
 * 2) If yes, ask for a file name and save the results
 * @param string (the thing to write)
 * @return None, creates a file
 */
void personality_test::save_output(string output) {
	// prompts the user if they would like to save the output to a file
	cout << "Would you like to save the output to a file?" << endl
		 << "To answer a question, type 'Y', 'N', 'y', 'n', 'yes', 'no,'Yes', 'No', 'YES', or 'NO'" << endl;
	string input;
	cin >> input;

	// if the user says yes, they are asked to provice a file name and the file is written to
	if (input=="Y" || input=="y" || input=="yes" || input=="Yes" || input=="YES") {
		string filename;
		cout << "What would you like the file to be named? (ex. 'results.txt') ";
		cin >> filename;

		ofstream ofs(filename);

		ofs << output;
	}
}

