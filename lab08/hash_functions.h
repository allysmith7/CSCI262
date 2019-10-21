#pragma once

#include <string>

using namespace std;

// hash0 makes all hashes collide, reducing the hashtable to a
// singly-linked list.
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

// hash3 uses string folding, which treats each 4 four-byte chunk of the string as a unsigned integer,
// which are then summed together. This works better on long strings
// Source: OpenDSA, 15.3.3 String Folding
unsigned int hash3(string s) {
	unsigned int sum = 0;
	unsigned int mul = 1;

	for (int i = 0; i < s.size(); i++) {
		if (i % 4 == 0) {
			mul = 1;
		} else {
			mul *= 256;
		}

		sum += s[i] * mul;
	}

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

// Only use this on question 4
// Note, that this *technically* isn't a hash function, as it's non-deterministic
unsigned int hash_rand(string s) {
	static default_random_engine gen;
	uniform_int_distribution<unsigned int> dist;

    return dist(gen);
}
