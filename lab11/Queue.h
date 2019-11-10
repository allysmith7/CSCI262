#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>

/*
    Queue.h

    A working implementation of a fixed-size circular queue
    meeting the requirements of the Queue, part 1 lab.  Use
    or replace as you wish.
*/

template<class T>
class Queue {
 public:
  // constructor
  Queue<T>() {
	  _capacity = 4;
	  _data = new T[_capacity];
	  _size = 0;
  }

  // big 3
  Queue<T>(const Queue<T> &q) {
	  _capacity = q._capacity;
	  _size = q._size;
	  _data = new T[_capacity];
	  for (int j = 0; j < _size; j++) {
		  _data[j] = q._data[j];
	  }
  }

  ~Queue<T>() {
	  delete[] _data;
  }

  Queue<T> &operator=(const Queue<T> &q) noexcept {
	  if (this==&q) return *this; // self-assign chk
	  delete[] _data;
	  _capacity = q._capacity;
	  _size = q._size;
	  _data = new T[_capacity];
	  for (int j = 0; j < _size; j++) {
		  _data[j] = q._data[j];
	  }
	  return *this;
  }
  // enqueue: add a char to the end of the queue if room and return true;
  // if not enough room, return false
  bool enqueue(T c);

  // dequeue: if queue is not empty, remove the front element from the queue;
  // if queue is empty, return false and do nothing.
  bool dequeue();

  // front: return the front element in the queue
  T front() { return _data[0]; }

  // is_empty: return whether or not the queue is empty
  bool is_empty() { return _size==0; }

  int size() { return _size; }

  void print() {
	  for (int i = 0; i < _size; i++) {
		  std::cout << _data[i] << ' ';
	  }
	  std::cout << std::endl;
  }

 private:
  int _capacity;
  T *_data;
  int _size;
};

template <class T>
bool Queue<T>::dequeue() {
	if (is_empty()) return false;

	T *temp = new T[_capacity];

	for (int i = 1; i < _size; i++) {
		temp[i - 1] = _data[i];
	}
	for (int i = _size; i < _capacity; i++) {
		temp[i - 1] = 0;
	}
	delete[] _data;
	_data = temp;
	_size--;

	return true;
}

template<class T>
bool Queue<T>::enqueue(T c) {
	// doubles capacity
	if (_size == _capacity) {
		_capacity *= 2;
		T* temp = new T[_capacity];
		for (int j = 0; j < _size; j++)
			temp[j] = _data[j];
		delete[] _data;
		_data = temp;
	}
	_data[_size] = c;
	_size++;
	return true;
}

#endif
