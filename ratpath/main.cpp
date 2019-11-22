#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int num_routes(vector<string> enc);
pair<int, int> find_rat_start(vector<string> enc);
pair<int, int> find_end_goal (vector<string> enc);
int find_routes(vector<string> enc, pair<int, int> rat_start, pair<int, int> end_goal, double last_distance);

int main() {
    vector<string> enc;
    enc.push_back(".R...");
    enc.push_back("..X..");
    enc.push_back("....X");
    enc.push_back("X.X.X");
    enc.push_back("...C.");

    cout << num_routes(enc) << endl;
    return 0;
}

/**
 * Sets up recursive calls for the rest of the program
 */
int num_routes(vector<string> enc) {
    pair<int, int> rat_start = find_rat_start(enc);
    pair<int, int> end_goal  = find_end_goal(enc);

    double distance = sqrt(pow(rat_start.first - end_goal.first, 2) + pow(rat_start.second - end_goal.second, 2));

    return find_routes(enc, rat_start, end_goal, distance);
}

/**
 * Helper function that finds the initial position of the
 * rat and returns it in a pair
 */
pair<int, int> find_rat_start(vector<string> enc) {
    for (int r = 0; r < enc.size(); r++) {
        for (int c = 0; c < enc.at(r).length(); c++) {
            if (enc[r][c] == 'R') {
                pair<int, int> results(r, c);
                return results;
            }
        }
    }
    return pair<int, int>(-1, -1);
}

/**
 * Helper function that finds the end goal that the rat is 
 * trying to get to, used for distance calculation
 */
pair<int, int> find_end_goal(vector<string> enc) {
    for (int r = 0; r < enc.size(); r++) {
        for (int c = 0; c < enc.at(r).length(); c++) {
            if (enc[r][c] == 'C') {
                pair<int, int> results(r, c);
                return results;
            }
        }
    }
    return pair<int, int>(-1, -1);
}

/**
 * Function that is responsible for recursively finding the routes 
 */
int find_routes(vector<string> enc, pair<int, int> rat_start, pair<int, int> end_goal, double last_distance) {
    int routes = 0;
    cout << "START: " << rat_start.first << ", " << rat_start.second << endl;
    cout << "DISTANCE: " << last_distance << endl;

    double up_distance = sqrt(pow(rat_start.first - 1 - end_goal.first, 2) + pow(rat_start.second - end_goal.second, 2));
    cout << "UPDISTANCE: " << up_distance << endl;

    double down_distance = sqrt(pow(rat_start.first + 1 - end_goal.first, 2) + pow(rat_start.second - end_goal.second, 2));
    cout << "DOWNDISTANCE: " << down_distance << endl;

    double left_distance = sqrt(pow(rat_start.first - end_goal.first, 2) + pow(rat_start.second - 1 - end_goal.second, 2));
    cout << "LEFTDISTANCE: " << left_distance << endl;

    double right_distance = sqrt(pow(rat_start.first - end_goal.first, 2) + pow(rat_start.second + 1 - end_goal.second, 2));
    cout << "RIGHTDISTANCE: " << right_distance << endl;
    cout << endl << endl;

    if (rat_start.first == end_goal.first && rat_start.second == end_goal.second) return 1;

    // checks each direction to see if it is in bounds & if the distance is lesser
    // up
    if (rat_start.first - 1 >= 0 && up_distance <= last_distance && enc[rat_start.first - 1][rat_start.second] != 'X') {
        routes += find_routes(enc, pair<int, int>(rat_start.first - 1, rat_start.second), end_goal, up_distance);
    }
    
    // down
    if (rat_start.first + 1 >= 0 && down_distance <= last_distance && enc[rat_start.first + 1][rat_start.second] != 'X') {
        routes += find_routes(enc, pair<int, int>(rat_start.first + 1, rat_start.second), end_goal, down_distance);
    }
    
    // left
    if (rat_start.second - 1 >= 0 && left_distance <= last_distance && enc[rat_start.first][rat_start.second - 1] != 'X') {
        routes += find_routes(enc, pair<int, int>(rat_start.first, rat_start.second - 1), end_goal, left_distance);
    }
    
    // right
    if (rat_start.second + 1 >= 0 && right_distance <= last_distance && enc[rat_start.first][rat_start.second + 1] != 'X') {
        routes += find_routes(enc, pair<int, int>(rat_start.first, rat_start.second + 1), end_goal, right_distance);
    }
    
    

    return routes;
}
