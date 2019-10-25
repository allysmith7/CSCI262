#include "Queue.h"
#include <iostream>
/*
    Queue.cpp

    Method implementations for Queue class

    assignment: CSCI 262 Lab - Queues, part 1

    author:

    last modified: 9/7/2017
*/

bool Queue::enqueue(char c) {
	// if the front has the same index and it isn't a null char, then the queue is full, so it returns false
	if (_back == _front && _data[_front] != '\u0000') return false;

	// else, it enqueues and updates _back
	_data[_back] = c;
	_back++;
	_back %= ARRAY_SZ;
	return true;
}

bool Queue::dequeue() {
	if (is_empty()) return false;

	// if it isn't empty, it changes the char to a null char and updates _front
	_data[_front] = '\u0000';
	_front++;
	_front %= ARRAY_SZ;
	return true;
}

char Queue::front() {
	return _data[_front];
}

bool Queue::is_empty() {
	// if _front equals _back and the value at _back is null, it is emptyÅ
	return _front == _back && _data[_back] == '\u0000';
}

void Queue::print_queue() {
	std::cout << std::endl << "[";
	for (auto character : _data) {
		std::cout << character << ", ";
	}
	std::cout << std::endl;
	std::cout << "Front: " << _front << "    " << "Back: " << _back << std::endl;
}