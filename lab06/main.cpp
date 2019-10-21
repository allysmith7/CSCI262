#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void egyptianMultiplication(unsigned a, unsigned b) {
	unsigned lesser, greater;
	vector<unsigned> left, right;

	// if the values of a and b are not equal, it stores them in clear variables
	// so the greater can be put in the top left corner
	lesser = (a < b ? a : b);
	if (a == b) {
		lesser = greater = a;
	} else {
		greater = (a > b ? a : b);
	}

	// starts building table using the vectors
	unsigned currentLeftVal = lesser;
	unsigned currentRightVal = greater;

	do {
		// adds the values to the vector, then divides the left by 2
		// and multiplies the right by 2
		left.push_back(currentLeftVal);
		right.push_back(currentRightVal);

		currentLeftVal /= 2;
		currentRightVal *= 2;
	} while (currentLeftVal >= 1);

	// prints out the vectors for the user to see
	// 		sets the width to be the length of the lesser val, making it line
	// 		up on the left side of the output
	for (int j = 0; j < left.size(); j++) {
		cout << setw(to_string(lesser).length()) << left[j] << " " <<  right[j] << endl;
	}
	cout << endl;

	int i = 0;
	while ( i < left.size()) {
		// if the value in the left column (vector) is odd, it deletes that row (index)
		if (left[i] % 2 == 0) {
			auto leftIter = left.begin();
			auto rightIter = right.begin();

			// loops through vector until the iterator equals the value at i
			while (*leftIter != left[i]) {
				leftIter++;
				rightIter++;
			}

			// erases the value at the index that was calculated
			left.erase(leftIter);
			right.erase(rightIter);
		} else {
			// if the value isn't odd, the index is incremented so the next can be checked
			i++;
		}
	}

	// calculates the answer by summing the remaining values in the right column
	int answer = 0;
	for (int val : right) {
		answer += val;
	}

	cout << "The answer is " << answer;
}

int main() {
	unsigned a, b;

	cout << "Please enter two positive integers: ";
	cin >> a >> b;
	cout << endl;

	egyptianMultiplication(a, b);

	return 0;
}
