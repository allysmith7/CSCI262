/*
 * lab4.cpp
 *
 * Implementations of selection sort, Fisher-Yates shuffling, and insertion
 * sort for analysis practice.  There are also some convenience methods to 
 * provide vectors of integers to use in testing, and timing code.
 *
 * Author: C. Painter-Wakefield
 * 
 * Last modified: 1/30/2019
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

/* Function prototypes */

/* Algorithms */
void insertion_sort(vector<unsigned int> &vec);
void selection_sort(vector<unsigned int> &vec);
void shuffle(vector<unsigned int> &vec);

/* Utility */
vector<unsigned int> range_vector(unsigned int size);
vector<unsigned int> random_vector(unsigned int size);
unsigned int get_random();

/* timing */
/* 
 * time_it returns the number of seconds executing a function call takes.
 * This uses some techniques we haven't studied yet, such as templates.
 * For now, just note that you can call time_it and pass in a function
 * name and a vector<unsigned int> and it will execute the function on 
 * the vector, timing how long the execution takes.
 */
template<class Function>
double time_it(Function f, vector<unsigned int> &vec) {
    auto start = system_clock::now();

    f(vec);

    auto stop = system_clock::now();
    auto diff = duration_cast<nanoseconds>(stop - start);
    return diff.count() / 1.0e9;
}


int main() {
    // loop until user asks to exit
    while (true) {

        // Algorithm choice
        int algorithm = 0;
        while (algorithm < 1 || algorithm > 3 || !cin) {
            if (!cin) {
                cin.clear();
                string discard;
                getline(cin, discard);
            }
            cout << "Which algorithm would you like to run? " << endl;
            cout << "1 - Selection sort" << endl;
            cout << "2 - Insertion sort" << endl;
            cout << "3 - Fisher-Yates shuffle" << endl;
            cin >> algorithm;
        }
        cout << endl;

        // Type of vector - random or already sorted
        char vector_type = 0;
        while (vector_type != 'r' && vector_type != 's') {
            cout << "Would you like to work with (r)andom or (s)orted data?" << endl;
            cin >> vector_type;
        }
        cout << endl;

        // Vary the size input to get measures of how the time taken by
        // the function grows with the size of input.  Recommended:
        // start with size 1000 and double each time.
        unsigned int size = 0;
        while (size == 0 || !cin) {
            if (!cin) {
                cin.clear();
                string discard;
                getline(cin, discard);
            }
            cout << "How big a vector would you like to test? ";
            cin >> size;
        }
        cout << endl;

        // Better timing data can be obtained by averaging many trial runs
        // of the same algorithm.  This can even out differences due to 
        // various types of interference, or differences in the data input.
        // Recommended: prefer smaller size and larger trials.
        unsigned int trials = 0; 
        while (trials == 0) {
            cout << "How many trials would you like to run? ";
            cin >> trials;
        }
        cout << endl << endl;

        // Summarize what we are about to do
        cout << "Executing ";
        if (algorithm == 1) cout << "selection sort";
        if (algorithm == 2) cout << "insertion sort";
        if (algorithm == 3) cout << "Fisher-Yates shuffle";
        cout << " on ";
        if (vector_type == 'r') cout << "random";
        if (vector_type == 's') cout << "sorted";
        cout << " vectors of size " << size << "," << endl;
        cout << "running " << trials << " trial(s).  Please wait." << endl;

        // Approach:
        // 1. Initialize a double time total to zero
        // 2. Loop TRIALS time:
        //    a. Create an appropriate vector for the algorithm to work on
        //    b. Use time_it() to time running the algorithm on the vector
        //    c. Add the return from time_it() to the time total
        // 3. Divide the time total by TRIALS to get the average run time

        vector<unsigned int> vec;

        auto fn = selection_sort;
        if (algorithm == 2) fn = insertion_sort;
        if (algorithm == 3) fn = shuffle;

        double t2 = 0.0;
        for (int i = 0; i < trials; i++) {
            // need to recreate vectors each time
            if (vector_type == 'r') vec = random_vector(size);
            else vec = range_vector(size);

            t2 += time_it(fn, vec);
        }

        cout << "Average time: " << (t2 / trials) << "s." << endl << endl;

        char yesno = 0;
        while (yesno != 'y' && yesno != 'n') {
            cout << "Would you like to run another test (y/n)? ";
            cin >> yesno;
        }
        if (yesno == 'n') break;
    }
    return 0;
}


/*
 * void insertion_sort(vector<unsigned int> &vec)
 * Sorts a vector of integers in place.
 */
void insertion_sort(vector<unsigned int> &vec) {
    for (int i = 1; i < vec.size(); i++) {
        int j;
        int el = vec[i];
        for (j = i - 1; j >= 0 && vec[j] > el; j--) {
            vec[j + 1] = vec[j];
        }
        vec[j + 1] = el;
    }
}

/*
 * void selection_sort(vector<unsigned int> &vec)
 * Sorts a vector of integers in place.
 */
void selection_sort(vector<unsigned int> &vec) {
    for (int left = 0; left < vec.size() - 1; left++) {
        int right = left;
	for (int j = left + 1; j < vec.size(); j++) {
            if (vec[j] < vec[right]) right = j;
	}
        swap(vec[left], vec[right]);
    }
}

/*
 * void shuffle(vector<unsigned int> &vec)
 * Shuffles a vector of integers in place.  The algorithm used is 
 * the Fisher-Yates algorithm.
 */
void shuffle(vector<unsigned int> &vec) {
    for (unsigned int i = vec.size() - 1; i >= 1; i--) {
        unsigned int idx = get_random() % (i + 1);
        swap(vec[idx], vec[i]);
    }
}

/*
 * vector<int> range_vector(int size)
 * Return a vector<int> containing all the integers from 0 to size - 1, in 
 * order.
 */
vector<unsigned int> range_vector(unsigned int size) {
    vector<unsigned int> answer(size);
    for (unsigned int i = 0; i < size; i++) answer[i] = i;
    return answer;
}

/*
 * vector<int> random_vector(int size)
 * Return a vector<int> containing random integers, in no particular order.
 */
vector<unsigned int> random_vector(unsigned int size) {
    vector<unsigned int> answer(size);
    for (unsigned int i = 0; i < size; i++) answer[i] = get_random();
    return answer;
}

/*
 * unsigned int get_random()
 * Return a uniformly randomly generated unsigned int.
 * While rand() from <cstdlib> is good enough for most purposes, we may
 * wish to test vectors of size > INT_MAX, so we need C++'s library.
 */
unsigned int get_random() {
    static default_random_engine gen;
    static bool initialized = false;
    if (!initialized) {
        random_device rd;
        gen.seed(rd());
    }
    
    uniform_int_distribution<unsigned int> dist;
    return dist(gen);
}

