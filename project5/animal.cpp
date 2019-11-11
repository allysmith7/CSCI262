/*
        animal.cpp

        author: L. Henke and C. Painter-Wakefield
        date: 04 November 2019

        Animal/20 questions program for CSCI 262, starter code.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

// holds questions and answers for learning from the mistake
vector<pair<string, string> > history;

class node {
   public:
    node();
    node(string str);
    string data;
    node* left;
    node* right;
};

node::node() {
    data = "";
    left = nullptr;
    right = nullptr;
}

node::node(string str) {
    data = str;
    left = nullptr;
    right = nullptr;
}

void play_game(node*);
node* read_game_tree();
void write_game_tree(node*);
void delete_game_tree(node*);

// TODO: Add helper method templates here, such as read_preorder().
void read_preorder(node* tree, ifstream& fin);
void write_preorder(node* tree, ofstream& fout);
void print_tree(node* root, string indent);

/**
 * Handles showing the main menu/basic UI
 */
int main() {
    node* root = read_game_tree();
    if (root == nullptr)
        return -1;

    while (true) {
        string tmp;
        int choice;

        // print_tree(root, "");

        std::cout << "Welcome to 20 questions!" << endl;
        std::cout << "  1) Play the game" << endl;
        std::cout << "  2) Save the game file" << endl;
        std::cout << "  3) Quit" << endl;
        std::cout << "Please make your selection: ";
        std::getline(cin, tmp);
        choice = atoi(tmp.c_str());

        switch (choice) {
            case 1:
                play_game(root);
                break;
            case 2:
                write_game_tree(root);
                break;
            case 3:
                delete_game_tree(root);
                cout << "Freed memory from tree." << endl;
                break;
            default:
                std::cout << "Sorry, I don't understand." << endl
                          << endl;
                break;
        }
        if (choice == 3)
            break;
    }

    delete_game_tree(root);
    return 0;
}

/**
 * Sets up the recursive call to the read_preorder
 * @return root of the tree
 */
node* read_game_tree() {
    ifstream fin("animal_game_tree.txt");
    if (!fin.is_open()) {
        cerr << "Problem opening the file. Ensure 'animal_game_tree.txt is in "
                "./cmake-build-debug/"
             << endl;
        return nullptr;
    }

    node* root = new node;

    read_preorder(root, fin);
    return root;
}

/**
 * Plays the game
 * @param root Root of the game tree
 */
void play_game(node* root) {
    string question = (root->data).substr(3);
    string response;
    std::cout << question << endl;
    std::getline(cin, response);

    // converts response to lowercase
    for (int i = 0; response[i]; i++) {
        response[i] = tolower(response[i]);
    }

    // if yes, uses left branch
    if (response == "y" || response == "yes") {
        if (root->left == nullptr) {
            std::cout << "Yay! I guessed your animal!\n"
                      << endl;
            return;
        } else {
            pair<string, string> p(question, "YES");
            history.push_back(p);
            play_game(root->left);
        }
    } else if (response == "n" || response == "no") {
        if (root->right == nullptr) {
            std::cout << "Darn I lost :(" << endl
                      << endl;

            string yn;  // holds yes or no
            std::cout << "Would you like to expand the tree (y/n)? ";
            std::getline(cin, yn);

            // converts response to lowercase
            for (int i = 0; yn[i]; i++) {
                yn[i] = tolower(yn[i]);
            }

            if (yn == "y" || yn == "yes") {
                // appends to tree
                std::cout << "\n"
                          << endl;

                std::cout << "I asked..." << endl;
                for (pair<string, string> p : history) {
                    string q = p.first + " " + p.second;
                    std::cout << q << endl;
                }
                std::cout << endl;

                std::cout << "Enter a new animal in the form of a question, \n"
                          << "e.g., 'Is it a whale?':" << endl;
                string new_animal;
                std::getline(cin, new_animal);

                std::cout << "Now enter a question for which the answer is 'yes' for your new \n"
                          << "animal, and which does not contradict your previous answers:" << endl;
                string new_question;
                std::getline(cin, new_question);

                string old_question = question;

                root->data = "#Q " + new_question;
                root->left = new node("#A " + new_animal);
                root->right = new node("#A " + old_question);

                write_game_tree(root);
            }
            return;
        } else {
            pair<string, string> p(question, "NO");
            history.push_back(p);
            play_game(root->right);
        }
    } else {
        std::cout << "Unable to interpret answer. Please input 'y', 'yes', 'n', or 'no'"
                  << endl;
    }
}

/**
 * Writes the game tree, sets up a recursive call to write_preorder();
 * @param root The root of the tree
 */
void write_game_tree(node* root) {
    ofstream fout("animal_game_tree.txt");
    if (!fout.is_open()) {
        std::cerr << "Error: Unable to write to file." << endl;
        return;
    }

    write_preorder(root, fout);
    fout.close();
}

/**
 * Deletes the game tree
 * @param root Root of the game tree
 */
void delete_game_tree(node* root) {
    // Optional. Do a post-order deletion of the game tree.
    // This isn't strictly needed as the program exits after this is called,
    // which frees up all the memory anyway.
    return;
}

void read_preorder(node* tree, ifstream& fin) {
    if (fin.eof())
        return;
    string val;
    std::getline(fin, val);
    tree->data = val;
    if (val[1] == 'A')
        return;
    tree->left = new node;
    tree->right = new node;
    read_preorder(tree->left, fin);
    read_preorder(tree->right, fin);
}

void write_preorder(node* tree, ofstream& fout) {
    if (tree == nullptr) return;
    fout << tree->data << endl;
    write_preorder(tree->left, fout);
    write_preorder(tree->right, fout);
}

void print_tree(node* root, string indent) {
    if (root == nullptr)
        return;
    std::cout << indent << root->data << endl;
    print_tree(root->left, indent + "	");
    print_tree(root->right, indent + "	");
}
