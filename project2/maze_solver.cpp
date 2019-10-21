/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    one exists) to a simple maze.

    C. Painter-Wakefield
*/

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// TODO: read the complete assignment instructions before beginning.  Also look
// at maze_solver.h - you will need to modify it as well.  In this file you
// will need to complete several methods, and add any others as needed for your
// solution.


/*
 _read_maze()

 Read in maze information (rows, columns, maze) from the provided input stream.
 The values will be stored in a 2D vector of strings
*/
void maze_solver::_read_maze(istream& in) {
	int currentLineIndex = 0;
	string currentLine;
	// runs getline() twice to clear the dimensions line
	getline(in, currentLine);

	vector<string> temp;
	while (!in.eof()) {
		// stores the line in a string that will be chopped up and put in to the vector
		getline(in, currentLine);

		// loops through each character in the line and adds it to the vector
		temp.clear();
		for (char letterIndex : currentLine) {
			// coverts char to string
			string currentLetter(1, letterIndex);

			// adds string to vector
			temp.push_back(currentLetter);
		}
		_maze.push_back(temp);
		currentLineIndex++;
	}
}


/*
 _write_maze()

 Output the (partially or totally solved) maze on cout.
*/
void maze_solver::_print_maze() {
    for (auto vec : _maze) {
    	for (const string& s : vec) {
    		cout << s;
    	}
    	cout << endl;
    }
}


/*
 _initialize()

 Find the start point.  Push or enqueue the start point.
*/
void maze_solver::_initialize() {
	int startCol, startRow;
	startCol = startRow = -1;

	// loops through the 2D vector to find the start location
	for (int r = 0; r < _maze.size(); r++) {
		for (int c = 0; c < _maze[r].size(); c++) {
			if (_maze[r][c] == "o") {
				startCol = c;
				startRow = r;
			}
		}
	}

	pointer start(0,0);
	start.col = startCol;
	start.row = startRow;

	if (_use_stack) {
		_stack.push(start);
	} else {
		_queue.push(start);
	}
}


/*
 _step()

 Take *one* step towards solving the maze, setting _no_more_steps and
 _goal_reached as appropriate.  This implements the essential maze search
 algorithm; take the next location from your stack or queue, mark the
 location with '@', add all reachable next points to your stack or queue,
 etc.

 Notes:

 - Your initial point should have been pushed/enqueued in the _initialize()
   method.

 - Set the _no_more_steps variable to true when there are no more reachable
   points, or when the maze was successfully solved.

 - Set the _goal_reached variable to true if/when the maze was successfully
   solved.

 - You should write an '@' over every location you have previously visited,
   *except* for the start and goal positions - they should remain 'o' and '*',
   respectively.

 - Since the run() method will call _print_maze() in between calls to _step(),
   you probably want to try to make progress on each call to step.  On some
   mazes, depending on your approach, it may be possible to add the same
   point multiple times to your stack or queue - i.e., if a point is reachable
   from multiple other points.  When this happens, your code will work, but
   it may make very slow progress.  To fix the problem, simply run a loop to
   remove any already visited points from your stack or queue at the beginning
   or end of _step().

 - There are many approaches to dealing with invalid/unreachable points; you
   can choose to add them and then remove them next time you get into _step(),
   you can choose to not add them in the first place, etc.

 - It is strongly recommended that you make helper methods to avoid code
   duplication; e.g., a function to detect that a point is out of bounds is
   a real help on the mazes with no walls.  You can also think about pulling
   out methods that do the actual acting on stacks/queues - this will reduce
   code duplication, since everything is identical between the two except
   for whether you use your stack or queue.  E.g., you could have methods
   named "_push", "_pop", "_next" which use the appropriate data structure.
*/
void maze_solver::_step() {
	// TODO: write this method
	if (_use_stack) {
		// if the stack is empty, then the maze has either been solved or can't be solved, so the function ends
		if (_stack.empty()) {
			_no_more_steps = true;
			return;
		}

		pointer currentPoint = _stack.top();
		_stack.pop();

//		cout << endl << "Testing point " << currentPoint.row << ", " << currentPoint.col << endl;

		// if it is the goal, ends the function
		if (_maze[currentPoint.row][currentPoint.col] == "*") {
			_goal_reached = true;
			while (!_stack.empty()) {
				_stack.pop();
			}
			_no_more_steps = true;

			return;
		} else {
			// marks the point as visited ("@") and continues to next points
			_maze[currentPoint.row][currentPoint.col] = "@";
		}
		// checks if the points to the top, bottom, left and right are valid
		CheckPoints_stack(currentPoint);

		// pops off top until it hasn't been visited
		try {
			// if it is the goal, ends the function
			if (_maze[currentPoint.row][currentPoint.col] == "*") {
				_goal_reached = true;
				return;
			}
			while (!_stack.empty()) {
				if (_maze[_stack.top().row][_stack.top().col]=="@") {
					_stack.pop();
				} else {
					break;
				}
			}
		} catch (exception& ex) {
			cerr << ex.what() << endl;
		}

		if (_stack.empty()) {
			_no_more_steps = true;
		}
	} else {
		// if the queue is empty, then the maze has either been solved or can't be solved, so the function ends
		if (_queue.empty()) {
			_no_more_steps = true;
			return;
		}

		pointer currentPoint = _queue.front();
		_queue.pop();


//		cout << endl << "Testing point " << currentPoint.row << ", " << currentPoint.col << endl;

		// if it is the goal, ends the function
		if (_maze[currentPoint.row][currentPoint.col] == "*") {
			_goal_reached = true;
			while (!_queue.empty()) {
				_queue.pop();
			}
			_no_more_steps = true;
			return;
		} else {
			// marks the point as visited ("@") and continues to next points
			_maze[currentPoint.row][currentPoint.col] = "@";
		}
		// checks if the points to the top, bottom, left and right are valid
		CheckPoints_queue(currentPoint);

		// pops off top until it hasn't been visited
		while (_maze[_queue.front().row][_queue.front().col] == "@") {
			_queue.pop();
		}

		if (_queue.empty()) {
			_no_more_steps = true;
		}
	}
}



/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

/*
 maze_solver constructor

 You should not need to modify this.  It opens the maze file and passes
 the input stream to read_maze(), along with setting up some internal state
 (most importantly, the variable telling you whether to use a stack or
 a queue).
*/
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	_use_stack = use_stak;
	_do_pause = pause;

	_no_more_steps = false;
	_goal_reached = false;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		_maze_name = infile;
	} else {
		_maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);

	_read_maze(fin);

	fin.close();
}

/*
 run()

 Initializes the maze_solver, then runs a loop to keep moving forward towards
 a solution.

 While more steps are possible (while no_more_steps == false), run() calls
 step(), then calls print_maze(), then pause().  Once there are no more steps,
 it prints a success/failure message to the user (based on the goal_reached
 flag) and writes the final maze to a solution file.
*/

void maze_solver::run() {
    _initialize();

	cout << "Solving maze '" << _maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	_print_maze();
	cout << endl;

	// main loop
	while (!_no_more_steps) {
		_pause();
		_step();
		if (!_goal_reached) {
			cout << endl;
			_print_maze();
			cout << endl;
		}
	}

	// final output to user
	cout << "Finished: ";
	if (_goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}
}


/*
 pause()

 Pauses execution until user hits enter (unless do_pause == false).
*/
void maze_solver::_pause() {
	if (!_do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
}

/*
 * Checks if the part of the maze at the pointer is not a wall, is in bounds, and hasn't been visited previously
 *
 * @param pointer: the pointer that is being checked
 */
bool maze_solver::shouldPush(maze_solver::pointer pointer) {
	// if the pointer is out of the maze, attempting to get the character will throw an out_of_range exception
	if (pointer.row >= 0 && pointer.row < _maze.size()) {
		if (pointer.col >= 0 && pointer.col < _maze[pointer.row].size()) {
			string character = _maze[pointer.row][pointer.col];

			if (character == "." || character == "*") {
				return true;
			}
		}
	}

	return false;
}
void maze_solver::CheckPoints_stack(maze_solver::pointer pointer) {
	class pointer top(pointer.row - 1, pointer.col);
	class pointer bottom(pointer.row + 1, pointer.col);
	class pointer left(pointer.row, pointer.col - 1);
	class pointer right(pointer.row, pointer.col + 1);

	if (shouldPush(top)) {
		_stack.push(top);
	}
	if (shouldPush(left)) {
		_stack.push(left);
	}
	if (shouldPush(right)) {
		_stack.push(right);
	}
	if (shouldPush(bottom)) {
		_stack.push(bottom);
	}
}

void maze_solver::CheckPoints_queue(maze_solver::pointer pointer) {
	class pointer top(pointer.row - 1, pointer.col);
	class pointer bottom(pointer.row + 1, pointer.col);
	class pointer left(pointer.row, pointer.col - 1);
	class pointer right(pointer.row, pointer.col + 1);

	if (shouldPush(top)) {
		_queue.push(top);
	}
	if (shouldPush(left)) {
		_queue.push(left);
	}
	if (shouldPush(right)) {
		_queue.push(right);
	}
	if (shouldPush(bottom)) {
		_queue.push(bottom);
	}
}

maze_solver::pointer::pointer(int rowVal, int colVal) {
	row = rowVal;
	col = colVal;
}
