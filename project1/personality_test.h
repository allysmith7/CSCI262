#ifndef _PERSONALITY_TEST_H
#define _PERSONALITY_TEST_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class question {
 public:
  question(string sentence_val, string yesOption, string noOption, string categoryId) {
	  sentence = sentence_val;
	  yes_option = yesOption;
	  no_option = noOption;
	  category_id = categoryId;
  }

  string sentence;
  string yes_option;
  string no_option;
  string category_id;
};

// personality test class
class personality_test {
 public:
  bool load(istream &);
  void printout();
  void run_test();
  string analyze_personality();
  void categorize_output(string);
  void save_output(string);
  vector<question> questions;

 private:
  // Add anything you may need
};

#endif
