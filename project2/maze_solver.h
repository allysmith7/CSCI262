/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.h

    Class declaration for the maze_solver class.

    C. Painter-Wakefield
*/

#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/*
 TODO: make sure you read all of the assignment instructions before you
 begin.  You need to fill in the following methods of this class:
    _read_maze()
    _print_maze()
    _initialize()
    _step()
 You will also need to add instance variables for your stack and queue
 objects.  You may also add other instance variables or methods as needed
 to effectively complete the task.  It is highly recommended that you also
 create helper methods to decompose and simplify your _step() method.

 The code below assumes you will use a vector<string> to store
 the maze. You can change this if you wish.
*/

class maze_solver {
public:
    // constructor
	maze_solver(string infile, bool use_stack, bool pause = false);

	// public methods
	void run();
	class pointer {
	 public:
	  pointer(int rowVal, int colVal);;
	  int row;
	  int col;
	};

private:
	// private instance variables
	string _maze_name;
	bool _use_stack;
	bool _do_pause;

	int _rows{}, _columns{};
	vector<vector<string>> _maze;

	stack<pointer> _stack;
	queue<pointer> _queue;

	bool _no_more_steps;
	bool _goal_reached;

	// private methods you need to write
    void _read_maze(istream& in);
    void _print_maze();
    void _initialize();
    void _step();

    // other private methods
    void _pause();

  bool shouldPush(pointer pointer);
  void CheckPoints_stack(pointer pointer);
  void CheckPoints_queue(pointer pointer);
};

#endif
