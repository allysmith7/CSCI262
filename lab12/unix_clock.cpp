/*
    unix_clock.cpp

    Implements unix_clock.h

    Code for Data Structures Inheritance Lab

    Author: L. Henke
*/

#include "unix_clock.h"

unix_clock::unix_clock() {
    _seconds = 0;
}

unix_clock::unix_clock(int h, int m, int s) {
    _seconds = 0;

    set_time(h, m, s);
}

int unix_clock::get_hour() {
    return _seconds / 3600;
}

int unix_clock::get_minute() {
    return (_seconds % 3600) / 60;
}

int unix_clock::get_second() {
    return _seconds % 60;
}

void unix_clock::set_time(int h, int m, int s) {
    _seconds = h * 3600 + m * 60 + s;

    // Fix overflow
    _seconds %= 24 * 60 * 60;
}

string unix_clock::get_time() {
    string result;

    // Add correct padding
    if (get_hour() < 10) {
        result += "0";
    }

    result += to_string(get_hour()) + ":";

    if (get_minute() < 10) {
        result += "0";
    }

    result += to_string(get_minute()) + ":";

    if (get_second() < 10) {
        result += "0";
    }

    result += to_string(get_second());

    return result;
}
