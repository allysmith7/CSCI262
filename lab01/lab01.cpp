/*
    lab01.cpp

    Author: C. Painter-Wakefield

    Course and Assignment: CSCI 262 Lab 1

    Description: main() routine for lab01.  This program 
    prints a muddled "Computer Science!" message.
*/

#include <iostream>
#include <string>

#include "muddler.h"

using namespace std;

int main() {
    muddler m;
    
    string msg = m.muddle("Computer Science!");

    cout << msg << endl;

    return 0;
}
