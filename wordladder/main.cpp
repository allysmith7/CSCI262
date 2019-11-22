#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int shortest(vector<string> words, string from, string to);
int count_matching_letters(string one, string two);
void find_paths(vector<string> words,
				const string &from,
				const string &to,
				vector<string> &path,
				vector<vector<string> > &paths,
				bool hasUsedRung);

int main() {
    vector<string> words;
	words.emplace_back("dart");
	words.emplace_back("dire");
	words.emplace_back("hire");
	words.emplace_back("wire");
	words.emplace_back("mire");
	words.emplace_back("here");
	words.emplace_back("were");
	words.emplace_back("mere");
	words.emplace_back("care");
	words.emplace_back("tart");
	words.emplace_back("dare");
	words.emplace_back("dirt");

	string from = "cart";
    string to = "pere";
    cout << shortest(words, from, to) << endl;
    return 0;
}

/**
 * Sets up recursive calls to find_path()
 */
int shortest(vector<string> words, string from, string to) {
    vector<string> path;
    path.push_back(from);

    vector<vector<string> > paths;

	find_paths(std::move(words), from, to, path, paths, false);

    if (paths.empty()) return 0;

    int shortest = INT16_MAX;
    for (const auto& p: paths) {
        if (p.size() < shortest) shortest = p.size();
    }

    return shortest;
}

/**
 * Helper function that counts the matching letters
 * within two words
 */
int count_matching_letters(string one, string two) {
    int matching = 0;
    for (int i = 0; i < min(one.length(), two.length()); i++) {
        if (one[i] == two[i])
            matching++;
    }

    return matching;
}

void find_paths(vector<string> words,
				const string &from,
				const string &to,
				vector<string> &path,
				vector<vector<string> > &paths,
				bool hasUsedRung) {
//	cout << "REMAINING WORDS: ";
//	for (const string& w : words) cout << w << " ";
//	cout << endl << "FROM: " << from;
//	cout << endl << "TO: " << to;
//	cout << endl << "PATH: ";
//	for (const string& p : path) cout << p <<  " -> ";
//	cout << endl << endl;

	if (hasUsedRung && count_matching_letters(from, to) == to.size() - 1 ) {
		path.push_back(to);
		paths.push_back(path);
		return;
	}

    for (int i = 0; i < words.size(); i++) {
        // if the all of the letters match except one,
        if (count_matching_letters(from, words.at(i)) == from.size() - 1) {
            path.push_back(words.at(i));

            // create a copy of words, excluding the word
            if (i == 0) {
                vector<string> new_words(words.begin() + 1, words.end());
				find_paths(new_words, words.at(i), to, path, paths, true);
            } else if (i == words.size() - 1) {
                vector<string> new_words(words.begin(), words.end() - 1);
				find_paths(new_words, words.at(i), to, path, paths, true);
            } else {
                // finds iterator to the element we are using as the new from
                auto it = words.begin();
                while (*it != words.at(i))
                    it++;

                vector<string> new_words(words.begin(), it - 1);
                vector<string> part2(it + 1, words.end());

                new_words.insert(new_words.end(), part2.begin(), part2.end());
				find_paths(new_words, words.at(i), to, path, paths, true);
            }
        }
    }
}