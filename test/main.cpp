#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int least_borders(vector<int> &x, vector<int> &y, vector<int> &r, int x1, int y1, int x2, int y2) {
	vector<bool> startCircles;
	vector<bool> endCircles;

	for (int i = 0; i < x.size(); i++) {
		startCircles.push_back(false);
		endCircles.push_back(false);
	}

	for (int i = 0; i < x.size(); i++) {
		int xs = (int)pow((x.at(i) - x1), 2);
		int ys = (int)pow((y.at(i) - y1), 2);
		int rs = (int)pow(r.at(i), 2);
//		cout << "XS: " << xs << " YS: " << ys << " RS: "<< rs << endl;
		if ((xs + ys) < rs) {
			startCircles.at(i) = true;
		}
	}

	for (int i = 0; i < x.size(); i++) {
		int xs = (int)pow((x.at(i) - x2), 2);
		int ys = (int)pow((y.at(i) - y2), 2);
		int rs = (int)pow(r.at(i), 2);
//		cout << "XS: " << xs << " YS: " << ys << " RS: "<< rs << endl;
		if ((xs + ys) < rs) {
			endCircles.at(i) = true;
		}
	}

	vector<bool> crosses;
	// xors the values
	for (int i = 0; i < x.size(); i++) {
		crosses.push_back(startCircles.at(i) != endCircles.at(i));
	}

	int results = 0;
	for (bool b : crosses) {
		if (b) results++;
	}

//	for (bool b : startCircles) cout << b;
//	cout << endl;
//
//	for (bool b : endCircles) cout << b;
//	cout << endl;

	return results;
}

int main() {
	vector<int> x = {0};		//{0,-6,6}; ,{-1,2,3,1,5,1,1,1},{1,3,1,7,1,1,2,3},2,3,13,2
	vector<int> y = {0};		//{0,1,2};
	vector<int> r = {2};		//{2,2,2};
	int x1 = 0;
	int y1 = 0;
	int x2 = 1;
	int y2 = 1;

	cout << least_borders(x, y, r, x1, y1, x2, y2) << endl;
}