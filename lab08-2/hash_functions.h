#pragma once

#include <string>

using namespace std;

// hash0 makes all hashes collide, reducing the hashtable to a singly-linked list.
unsigned int hash0(string s) {
	return 0;
}

// hash1 simply treats the first four chars of the string as if they were
// an unsigned int value.
unsigned int hash1(string s) {
	// pad s to at least size 4
	if (s.length() < 4) {
		s = s + "xxxx";
	}

	unsigned int h = s[0];
	for (int i = 1; i < 4; i++) {
		h = h * 256;
		h = h + s[i];
	}
	return h;
}

// hash2 simply adds up all of the char values in the string.
unsigned int hash2(string s) {
	unsigned int h = 0;
	for (int i = 0; i < s.length(); i++) {
		h = h + s[i];
	}
	return h;
}

// hash3 uses string folding, a complicated technique that goes through
// the string 4 bytes at a time
unsigned int hash3(string s) {
	unsigned int *lkey = (unsigned int *)s.c_str();
	int length = s.size() / 4;
	unsigned int sum = 0;

	for (int i = 0; i < length; i++) {
		sum += lkey[i];
	}

	int extra = s.size() - length * 4;
	char temp[4];
	lkey = (unsigned int *)temp;
	lkey[0] = 0;

	for (int i = 0; i < extra; i++) {
		temp[i] = s[length*4 + i];
	}

	sum += lkey[0];

	return sum;
}

// hash4 uses (roughly) Java's String hashCode algorithm; this is quite
// similar to the djb2 algorithm suggested by Dan Bernstein.
unsigned int hash4(string s) {
	unsigned int h = 0;
	for (int i = 0; i < s.length(); i++) {
		h = h * 31 + s[i];
	}
	return h;
}

// hash5 uses the C++ STL hash function for strings (implementation
// dependent - may differ by compiler).
unsigned int hash5(string s) {
	hash<string> hasher;
	return hasher(s);
}
