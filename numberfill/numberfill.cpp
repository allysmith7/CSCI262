#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

pair<int, int> findBottomRightCorner(vector<string>& picture, int row, int col);
pair<int, int> findMaxValueAndColumn(vector<string>& picture, pair<pair<int, int>, pair<int, int> > regionBounds);
int gradient(vector<string> picture);
int getValue(map<int, char>& associations, char c);
bool isHorizontalBoundary(vector<string>& picture, int row, int col);
bool isVerticalBoundary(vector<string>& picture, int row, int col);
bool isNumber(char c);

int main() {
    vector<string> picture = {"..X.....",
                              "..X..0..",
                              "1.X.....",
                              "..X.....",
                              "........"};

    cout << gradient(picture) << endl;

    return 0;
}

int gradient(vector<string> picture) {
    // finds the individual regions and stores their upper left and bottom right corners in a vector<pair<pair<int, int>, pair<int, int> > >
    vector<pair<pair<int, int>, pair<int, int> > > regions;
    vector<string> duplicate;

    for (int r = 0; r < picture.size(); r++) {
        string row;
        for (int c = 0; c < picture.at(r).size(); c++) {
            row += picture[r][c];
        }
        duplicate.push_back(row);
    }

    int r, c;
    r = c = 0;

    // gets the coordinates of each region
    while (r < picture.size()) {
        while (c < picture.at(r).size()) {
            // loops through the picture looking for non-X characters
            if (picture[r][c] != 'X') {
                // stores top left of the region
                pair<int, int> topLeft(r, c);
                pair<int, int> bottomRight = findBottomRightCorner(picture, r, c);

                pair<pair<int, int>, pair<int, int> > p(topLeft, bottomRight);
                regions.push_back(p);

                // marks the region as X so it isn't visited again
                for (int r0 = topLeft.first; r0 <= bottomRight.first; r0++) {
                    for (int c0 = topLeft.second; c0 <= bottomRight.second; c0++) {
                        picture[r0][c0] = 'X';
                    }
                }
            }
            c++;
        }
        r++;
    }

    for (auto p : regions) {
        cout << "TL: " << (p.first).first << ", " << (p.first).second << endl;
        cout << "BR: " << (p.second).first << ", " << (p.second).second << endl;
    }

    picture = duplicate;

    map<int, char> associations;
    associations.emplace(-10, 'Q');
    associations.emplace(-9, 'W');
    associations.emplace(-8, 'E');
    associations.emplace(-7, 'R');
    associations.emplace(-6, 'T');
    associations.emplace(-5, 'Y');
    associations.emplace(-4, 'U');
    associations.emplace(-3, 'I');
    associations.emplace(-2, 'O');
    associations.emplace(-1, 'P');
    associations.emplace(10, 'A');
    associations.emplace(11, 'S');
    associations.emplace(12, 'D');
    associations.emplace(13, 'F');
    associations.emplace(14, 'G');
    associations.emplace(15, 'H');
    associations.emplace(16, 'J');
    associations.emplace(17, 'K');
    associations.emplace(18, 'L');
    associations.emplace(19, ';');
    associations.emplace(20, ':');

    // goes region by region, altering the characters to be the correct number
    for (auto regionBounds : regions) {
        // first, it finds the greatest number and its most left occurance
        pair<int, int> maxValueAndColumn = findMaxValueAndColumn(picture, regionBounds);
        // cout << "VAL: " << maxValueAndColumn.first << " COL: " << maxValueAndColumn.second << endl;

        // if no values are in the region, the region is skipped and left blank
        if (maxValueAndColumn.second == -1)
            continue;

        // fills in region
        for (int r = (regionBounds.first).first; r <= (regionBounds.second).first; r++) {
            for (int c = (regionBounds.first).second; c <= (regionBounds.second).second; c++) {
                if (picture[r][c] == 'X')
                    continue;
                if ((maxValueAndColumn.first + c - maxValueAndColumn.second) >= 0 && (maxValueAndColumn.first + c - maxValueAndColumn.second) < 10) {
                    picture[r][c] = to_string(maxValueAndColumn.first + c - maxValueAndColumn.second)[0];
                } else {
                    // if the value is negative or greater than 10, it uses a map of associations to put in a char
                    picture[r][c] = associations.at(maxValueAndColumn.first + c - maxValueAndColumn.second);
                }
            }
        }
    }

    for (string s : picture) {
        cout << s << endl;
    }

    int sum = 0;

    // sums all of the numbers in the picture, using the associations if neccessary
    for (int r = 0; r < picture.size(); r++) {
        for (int c = 0; c < picture.at(r).size(); c++) {
            char character = picture[r][c];
            if (character != 'X' && character != '.') {
                if (isNumber(character)) {
                    sum += atoi(&character);
                } else {
                    sum += getValue(associations, character);
                }
            }
        }
    }
    return sum;
}

bool isHorizontalBoundary(vector<string>& picture, int row, int col) {
    for (int c = col; c < picture.at(row).size(); c++) {
        if (picture[row][c] != 'X')
            return false;
    }
    return true;
}

bool isVerticalBoundary(vector<string>& picture, int row, int col) {
    for (int r = row; r < picture.size(); r++) {
        if (picture[r][col] != 'X')
            return false;
    }
    return true;
}

pair<int, int> findBottomRightCorner(vector<string>& picture, int row, int col) {
    int r = row;
    int c = col;

    bool foundCol, foundRow;
    foundCol = foundRow = false;

    int boundaryCol, boundaryRow;
    boundaryRow = picture.size() - 1;
    boundaryCol = picture.at(0).size() - 1;

    while (!foundCol && c < picture.at(r).size()) {
        // looks for vertical boundary
        if (picture[r][c] == 'X') {
            boundaryCol = c - 1;
            foundCol = true;
        }

        while (foundCol && r < picture.size()) {
            if (picture[r][boundaryCol] == 'X') {
                boundaryRow = r - 1;
                foundRow = true;
                break;
            }
            r++;
        }

        c++;
    }

    pair<int, int> bottomRight(picture.size() - 1, picture.at(0).size() - 1);
    if (foundRow && foundCol) {
        pair<int, int> bottomRight(boundaryRow, boundaryCol);
    }
    return bottomRight;
}

pair<int, int> findMaxValueAndColumn(vector<string>& picture, pair<pair<int, int>, pair<int, int> > regionBounds) {
    auto upperLeft = regionBounds.first;
    auto bottomRight = regionBounds.second;

    int maxValue = INT32_MIN;
    int column = -1;

    for (int r = upperLeft.first; r <= bottomRight.first; r++) {
        for (int c = upperLeft.second; c <= bottomRight.second; c++) {
            // if it a  number (which it should be...) it checks it
            if (picture[r][c] != 'X' && picture[r][c] != '.') {
                int val = atoi(&picture[r][c]);
                if (val > maxValue) {
                    maxValue = val;
                    column = c;
                } else if (val == maxValue) {
                    if (c < column)
                        column = c;
                }
            }
        }
    }

    pair<int, int> valAndColumn(maxValue, column);
    return valAndColumn;
}

bool isNumber(char c) {
    switch (c) {
        case '0':
            return true;
        case '1':
            return true;
        case '2':
            return true;
        case '3':
            return true;
        case '4':
            return true;
        case '5':
            return true;
        case '6':
            return true;
        case '7':
            return true;
        case '8':
            return true;
        case '9':
            return true;
        default:
            return false;
    }
    return false;
}

int getValue(map<int, char>& associations, char c) {
    for (auto p : associations) {
        if (p.second == c)
            return p.first;
    }

    return 0;
}