/*
	main.cpp

	Code for CSCI 262 Hashtables Lab.  This code provides several candidate
	hashcode functions to evaluate on a collection of string values on a
	simple hashtable simulation, the size of which can be modified to
	evaluate the impact of different table sizes.

	This code assumes the availability of the file dictionary.txt, which
	contains exactly DICTIONARY_SIZE words, one per line.  If a different
	collection of strings is used, modify DICTIONARY_SIZE accordingly.

	Author: Luke Henke

	Last modified: 10/13/2019
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <set>
#include <unordered_set>
#include <algorithm>

#include "hash_functions.h"

using namespace std;

// Define our hash_function type
typedef unsigned int (*hash_function)(string);

void insert(string*, int, string, hash_function);
bool search(string*, int, string, hash_function);
void remove(string*, int, string, hash_function);

void make_histogram(string*, int);
void do_timing(string*, int, vector<string>, hash_function);

// This is how many words are in dictionary.txt
static const unsigned int DICTIONARY_SIZE = 127141;
static const unsigned int TEST_SIZE = 100000;
static const unsigned int VECTOR_TEST_SIZE = TEST_SIZE / 20;

int main() {
	// Modify these two lines of code to test different aspects of
	// hashtables for the lab.  The second line below uses a function
	// pointer, which we haven't studied; just replace "hash1" with
	// whichever of the hash functions above you want to test.
	unsigned int table_size = unsigned(DICTIONARY_SIZE * 1.3333333);
	hash_function hasher = &hash5;

	string* table = new string[table_size];

	// open the dictionary file
	ifstream words("dictionary.txt");
	if (!words) {
		cerr << "Error opening dictionary.txt, exiting." << endl;
		return -1;
	}

	cout << "Reading in words" << endl;

	// for each word, get the corresponding hashcode, and then mod
	// by the table size and store the word at the resulting index.
	string word;
	unsigned int hashcode;
	vector<string> words_vec; // This words_vec will be used later for timing

	int i = 0;
	while (!words.eof()) {
		getline(words, word);

		insert(table, table_size, word, hasher);

		words_vec.push_back(word);

		i++;

		// Log our progress, as some of the hashes make insert take a _really_ long time
		if (i % 1000 == 0)
			cout << i << "th word inserted" << endl;
	}

	words.close();

	make_histogram(table, table_size);

	// Uncomment this for the last quiz question
	 do_timing(table, table_size, words_vec, hasher);

	return 0;
}

void insert(string* table, int table_size, string record, hash_function hasher) {
	int i = 0;

	while(true) {
		int j = (hasher(record) + i) % table_size;

		if (table[j] == "") {
			table[j] = record;
			break;
		}

		i++;
	}
}

bool search(string* table, int table_size, string record, hash_function hasher) {
	int i = 0;
	int j = 0;

	do {
		j = (hasher(record) + i) % table_size;

		if (table[j] == record) {
			return true;
		}

		i++;
	} while (table[j] != "");

	return false;
}

void remove(string* table, int table_size, string record, hash_function hasher) {
	int i = 0;
	int home_position = hasher(record) % table_size;
	int k = 0;

	while (true) {
		int j = (hasher(record) + i) % table_size;

		if (table[j] == "")
			break;

		int j_home_position = hasher(table[j]) % table_size;

		if (j_home_position < home_position) {
			k = j;
		}

		i++;
	}

	if (k == 0) {
		table[home_position] = "";
	} else {
		table[home_position] = table[k];
		table[home_position] = "";
	}
}

void make_histogram(string* table, int table_size) {
	// now count the number of words in each bucket, and generate
	// a histogram of the different bucket sizes.
	map<int, int> histogram;
	for (int i = 0; i < table_size; i++) {
		int bucket_size = (table[i] != "") ? 1 : 0;
		histogram[bucket_size]++;
	}

	// output the histogram counts
	cout << "size   |  count" << endl;
	cout << "-------+-------" << endl;
	for (auto entry : histogram) {
		cout << right << setw(6) << entry.first;
		cout << " |";
		cout << right << setw(7) << entry.second << endl;
	}
}

void do_timing(string* table, int table_size, vector<string> words_vec, hash_function hasher) {
	// create a vector of strings to search for - we'll pick words spaced
    // evenly throughout the collection.
	cout << "Creating test words collection..." << endl;
    vector<string> test_words;
	set<string> test_words_set;
	unordered_set<string> test_words_unordered_set;

	// We cheat with the vector: since it takes far too long,
	// we'll only do 1/20th the size, and then multiply the size by 20,
	// to get a feel for how long it takes
	vector<string> special_vector_test;
	for (size_t i = 0; i < VECTOR_TEST_SIZE; i++) {
        int index = int(words_vec.size() / double(DICTIONARY_SIZE) * i);
        special_vector_test.push_back(words_vec[index]);
    }

	// ...we won't cheat with everyone else though.
    for (size_t i = 0; i < TEST_SIZE; i++) {
        int index = int(words_vec.size() / double(DICTIONARY_SIZE) * i);
        test_words.push_back(words_vec[index]);
		test_words_set.insert(words_vec[index]);
		test_words_unordered_set.insert(words_vec[index]);
    }

	clock_t start, stop;
	int count;

	// First, time the vector (eek)
	cout << "Timing vector..." << endl;

	count = 0;
	start = clock();
	for (string s: special_vector_test) {
		if (find(words_vec.begin(), words_vec.end(), s) != words_vec.end()) {
			count++;
		}
	}
	stop = clock();
	cout << "done." << endl << endl;

	double vector_time = (stop - start) / double(CLOCKS_PER_SEC);
	vector_time *= 200.0;

	/***********************************************/

	// First, time an ordered set
	cout << "Timing ordered set..." << endl;
	start = clock();
	count = 0;
	for (string s : test_words) {
		if (test_words_set.count(s) > 0) {
			count ++;
		}
	}

	stop = clock();
	cout << "done." << endl << endl;

	double ordered_set_time = (stop - start) / double(CLOCKS_PER_SEC);

	// Then, unordered set
	cout << "Timing unordered set..." << endl;
	start = clock();
	count = 0;
	for (string s : test_words) {
		if (test_words_unordered_set.count(s) > 0) {
			count ++;
		}
	}

	stop = clock();
	cout << "done." << endl << endl;

	double unordered_set_time = (stop - start) / double(CLOCKS_PER_SEC);

	// Hash table
	cout << "Timing hashtable..." << endl;
	start = clock();
	count = 0;
	for (string s : test_words) {
		if (search(table, table_size, s, hasher)) {
			count ++;
		}
	}

	stop = clock();
	cout << "done." << endl << endl;

    // This next line takes the elapsed "clock time" and converts to seconds
    double hash_table_time = (stop - start) / double(CLOCKS_PER_SEC);

	cout << "data structure   |   time (seconds)" << endl;
	cout << "-----------------+-----------------" << endl;
	cout << "vector           |";
	cout << "       " << vector_time << endl;
	cout << "ordered set      |";
	cout << "       " << ordered_set_time << endl;
	cout << "unordered set    |";
	cout << "       " << unordered_set_time << endl;
	cout << "hashtable        |";
	cout << "       " << hash_table_time << endl;
}
