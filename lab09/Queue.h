#ifndef _Queue_h
#define _Queue_h
#include <iostream>

/*
    Queue.h

    class definition for the Queue class.

    assignment: CSCI 262 Lab - Queues, part 1

    author:

    last modified: 9/7/2017
*/

#include <cstdlib>

class Queue {
 public:
  // max elements in queue
  static const size_t ARRAY_SZ = 5;

  Queue() {
	  _front = 0;
	  _back = 0;
  }

  bool enqueue(char c);
  bool dequeue();
  char front();
  bool is_empty();

  void print_queue();
 private:

  char _data[ARRAY_SZ];
  int _front;
  int _back;
};

#endif
