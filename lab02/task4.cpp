#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
	int lineNumberWithLongestWord = 0;
	int lengthOfLongestWord = 0;
	string longestWord;

	ifstream fin("lines.txt");
	string numOfLines;
	fin >> 	numOfLines;

	const int NUMBER_OF_LINES = stoi(numOfLines);
	cout << NUMBER_OF_LINES << endl;
	string currentLine;
	string currentWord;

	for (int i = 1; i <= NUMBER_OF_LINES; i++) {
		getline(fin, currentLine);
		istringstream sin(currentLine);

		while (!sin.eof()) {
			sin >> currentWord;
			if (currentWord.length() > lengthOfLongestWord) {
				lengthOfLongestWord = currentWord.length();
				lineNumberWithLongestWord = i;
				longestWord = currentWord;
				cout << "The longest word in the file is " << longestWord << ". It is " << lengthOfLongestWord << " letters long and is on line " << lineNumberWithLongestWord << endl;
			}
		}
	}
}