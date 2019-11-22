#include <iostream>
#include <string>
#include <vector>

using namespace std;

pair<int, int> findBottomRightCorner(vector<string>& picture, int row, int col);
int gradient(vector<string> picture);
bool IsHorizontalBoundary(vector<string>& picture, int row, int col);
bool isVerticalBoundary(vector<string>& picture, int row, int col);

int main() {
    vector<string> picture;
    picture.push_back("..X.....");
    picture.push_back("..X..0..");
    picture.push_back("1.X.....");
    picture.push_back("..X.....");
    picture.push_back("........");

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

    return 0;
}

bool IsHorizontalBoundary(vector<string>& picture, int row, int col) {
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

    bool foundCol;
    int boundaryCol, boundaryRow;

    while (r < picture.size()) {
        while (!foundCol && c < picture.at(r).size()) {
            // looks for vertical boundary
            if (picture[r][c] == 'X' && isVerticalBoundary(picture, r, c)) {
                boundaryCol = c;
                foundCol = true;
                break;
            }
            c++;
        }

        if (foundCol && picture[r][boundaryCol] == 'X' && IsHorizontalBoundary(picture, r, boundaryCol)) {
            boundaryRow = r;
            break;
        }
        r++;
    }
    if (!foundCol) {
        pair<int, int> bottomRight(picture.size() - 1, picture.at(0).size() - 1);
        return bottomRight;
    }

    pair<int, int> bottomRight(boundaryRow, boundaryCol);
    return bottomRight;
}