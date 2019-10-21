#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main1() {
	ifstream fin;
	cout << "Enter the name of the file to be copied: ";
	string input_filename;
	cin >> input_filename;
	fin.open(input_filename);

	ofstream fout;
	cout << endl << "Enter the name of the file to be copied to: ";
	string output_filename;
	cin >> output_filename;
	fout.open(output_filename);

	while (!fin.eof()) {
		string currentline;
		getline(fin, currentline);
		fout << currentline << endl;
	}

	fin.close();
	fout.close();
	return 0;
}