//
// Created by Cole Smith on 11/1/19.
//

#ifndef LAB10__CLOCK_TIME_H_
#define LAB10__CLOCK_TIME_H_

#include <iostream>

using namespace std;

class clock_time {
 public:
  clock_time();
  clock_time(int h, int m, int s);

  int get_hour();
  int get_minute();
  int get_second();

  void set_time(int h, int m, int s);

  friend bool operator==(clock_time a, clock_time b);
  friend bool operator!=(clock_time a, clock_time b);
  friend clock_time operator+(clock_time a, clock_time b);

 private:
  int _hours;
  int _minutes;
  int _seconds;
};

ostream &operator<<(ostream &out, clock_time c);

string to_string(clock_time c);

#endif //LAB10__CLOCK_TIME_H_
