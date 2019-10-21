/*
    muddler.cpp

    Author: C. Painter-Wakefield

    Course and Assignment: CSCI 262 Lab 1

    Description: Method definitions for the muddler class.
*/

#include <string>
#include <set>

#include "muddler.h"

using namespace std;

/*
   muddle()

   Does the actual muddling of strings.
*/
string muddler::muddle(string str) {
    set<char> letters;
    for (char c : str) { 
        letters.insert(c);
    }

    string muddled;

    for (char c : letters) {
        muddled.push_back(c);
    }

    return muddled;
}

