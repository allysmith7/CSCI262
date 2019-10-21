#include <iostream>
#include <fstream>
#include <string>

#include "rwg.h"

using namespace std;

int main() {
	string filename;

	cout << "Welcome to the random text generator!" << endl;
	cout << "=====================================" << endl << endl;

	cout << "Please input the name of a dictionary file: ";
	// cin >> filename;
	filename = "dictionary.txt";

	ifstream fin(filename);
	while (!fin) {
		fin.clear();
		cerr << "Error opening file \"" << filename << "\"!" << endl;
		cout << "Please input the name of a dictionary file: ";
		cin >> filename;
		fin.open(filename);
	}

	rwg generator(fin);

	fin.close();

	if (generator.is_empty()) {
		cout << "No words found! Exiting." << endl;
		return 1;
	}

    generator.self_test();

	cout << "Please input number of words to generate: ";
	int n;
	cin >> n;

	cout << "Generating " << n << " words..." << endl;
	cout << "-------------------------------" << endl;
	generator.generate(n);

	cout << "-------------------------------" << endl;
	cout << "Done." << endl << endl;

	return 0;
}

