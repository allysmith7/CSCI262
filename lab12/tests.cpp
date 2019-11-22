/*
     main() function for CSCI 262 Data Structures - Inheritance.

    Author: C. Painter-Wakefield and L. Henke
*/
#include <iostream>
#include <string>

#include "unix_clock.h"
#include "analog_clock.h" // Uncomment once you make this class

using namespace std;

int main() {
    int num_tests = 6;

    unix_clock* test_clocks[num_tests];
    test_clocks[0] = new unix_clock(0, 0, 0); // Midnight
    test_clocks[1] = new unix_clock(3, 15, 0); // 3:15 am
    test_clocks[2] = new unix_clock(6, 1, 1); // 6:01 am
    test_clocks[3] = new unix_clock(12, 0, 0); // Noon
    test_clocks[4] = new unix_clock(15, 15, 0); // 3:15 pm
    test_clocks[5] = new unix_clock(18, 1, 1); // 6:01 pm

    for (size_t i = 0; i < num_tests; i++) {
        // Declare each type of clock, at the test time
        unix_clock* unix_time = test_clocks[i];
        cout << unix_time->get_time() << "\t";

        // Uncomment the following lines of code once you have implemented analog_clock
        unix_clock* analog = new analog_clock(*test_clocks[i]);
        cout << analog->get_time() << "\t";
        delete analog;

        cout << endl;
    }

    for (size_t i = 0; i < num_tests; i++) {
        delete test_clocks[i];
    }
}
