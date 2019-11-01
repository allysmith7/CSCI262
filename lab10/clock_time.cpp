//
// Created by Cole Smith on 11/1/19.
//

#include "clock_time.h"

using namespace std;

clock_time::clock_time() {
	_hours = 0;
	_minutes = 0;
	_seconds = 0;
}

clock_time::clock_time(int h, int m, int s) {
	set_time(h, m, s);
}

int clock_time::get_hour() {
	return _hours;
}

int clock_time::get_minute() {
	return _minutes;
}

int clock_time::get_second() {
	return _seconds;
}
void clock_time::set_time(int h, int m, int s) {
	_hours = h;
	_minutes = m;
	_seconds = s;

	while (_seconds > 59) {
		_seconds -= 60;
		_minutes += 1;
	}

	while (_seconds < 0) {
		_seconds += 60;
		_minutes -= 1;
	}

	while (_minutes > 59) {
		_minutes -= 60;
		_hours += 1;
	}

	while (_minutes < 0) {
		_minutes += 60;
		_hours -= 1;
	}

	while (_hours > 23) {
		_hours -= 24;
	}

	while (_hours < 0) {
		_hours += 24;
	}
}
bool operator==(clock_time a, clock_time b) {
	return a.get_hour()==b.get_hour() && a.get_minute()==b.get_minute() && a.get_second()==b.get_second();
}

bool operator!=(clock_time a, clock_time b) {
	return !(a==b);
}
clock_time operator+(clock_time a, clock_time b) {
	clock_time ct(a.get_hour() + b.get_hour(),
				  a.get_minute() + b.get_minute(),
				  a.get_second() + b.get_second());
	return ct;
}

ostream &operator<<(ostream &out, clock_time c) {
	int h = c.get_hour();
	int m = c.get_minute();
	int s = c.get_second();

	out << h << ":";

	if (m < 10) {
		out << "0" << to_string(m);
	} else {
		out << to_string(m);
	}

	out << ":";

	if (s < 10) {
		out << "0" << to_string(s);
	} else {
		out << to_string(s);
	}

	return out;
}

string to_string(clock_time c) {
	int h = c.get_hour();
	int m = c.get_minute();
	int s = c.get_second();

	string results;

	results += to_string(h) + ":";

	if (m < 10) {
		results = results + "0" + to_string(m);
	} else {
		results = results + to_string(m);
	}

	results += ":";

	if (s < 10) {
		results = results + "0" + to_string(s);
	} else {
		results = results + to_string(s);
	}

	return results;
}


