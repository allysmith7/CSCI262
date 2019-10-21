#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "personality_test.h"

using namespace std;

void load_file(personality_test &);

/* main
 * Calls necessary functions in this file as well as functions in personality_test
 * @param None
 * @return None, Text to Console
 */
int main() {
	cout << "====================================" << endl;
	cout << "Welcome to CSCI262 Personality Test!" << endl;
	cout << "====================================" << endl << endl;

	personality_test test;
	string input;

	do {
		// Uncomment the below methods as you complete them
		load_file(test);
		//    test.printout();
		test.run_test();

		cout << "Would you like to take the test again?" << endl;

		cin >> input;
	} while (input=="Y" || input=="y" || input=="yes" || input=="Yes" || input=="YES");
}

/* Load File Method
 * 1) Prompt the user for a file name.
 * 2) Confirm that the file can be loaded
 * 3) Run personality_test::load to load in the data
 * 4) If personality_test::load fails, report this and retry
 * @param personality_test object (by reference)
 * @return None, Text to Console
 */
void load_file(personality_test &test) {
	while (true) {
		string fileName;
		cout << "Please enter the input file name, e.g., \"questions.txt\": ";
		cin >> fileName;

		ifstream questions_file(fileName);

//		ifstream questions_file("questions.txt");

		if (!questions_file.is_open()) {
			cout << "Error opening file " << fileName << ". Please try again." << endl;
			continue;
		}

		if (!test.load(questions_file)) {
			cout << "The file " << fileName << " appears to not be a proper file! Please try again." << endl;
			continue;
		}
		return;
	}
}
