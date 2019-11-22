/*
    unix_clock.h

    Header for unix_clock

    Code for Data Structures Inheritance lab.

    Author: L. Henke
*/

#pragma once
#include <string>

using namespace std;
class unix_clock {
public:
    virtual int get_hour();
    virtual int get_minute();
    virtual int get_second();

    virtual void set_time(int h, int m, int s);
    virtual string get_time();

    unix_clock();
    unix_clock(int h, int m, int s);

protected:
    int _seconds;
};
