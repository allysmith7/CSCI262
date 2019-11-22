/*
    analog_clock.cpp

    Extends unix_clock.h

    Author: C. Smith
*/
#pragma once
#include <string>
#include <utility>

using namespace std;
class analog_clock : public unix_clock {
 public:
  explicit analog_clock(unix_clock c) : unix_clock(std::move(c)) {};

  string get_time() override {
	  string result;
	  int hour = get_hour();

	  // special case for _seconds = 0
	  if (_seconds == 0) {
	  	return "12:00:00 am";
	  }

	  if (hour > 12) {
		result += to_string(hour % 12) + ":";
	  } else {
	  	result += to_string(hour) + ":";
	  }

	  if (get_minute() < 10) {
		  result += "0";
	  }

	  result += to_string(get_minute()) + ":";

	  if (get_second() < 10) {
		  result += "0";
	  }

	  result += to_string(get_second());

	  if (hour > 12) {
	  	result += " pm";
	  } else {
	  	result += " am";
	  }

	  return result;
  }

};