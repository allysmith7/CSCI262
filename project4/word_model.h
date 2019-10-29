/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Cole Smith

   Modified: 10/28/2019
*/

#ifndef _WORD_MODEL_H
#define _WORD_MODEL_H

#include "model.h"

using namespace std;

class word_model : public markov_model {
 public:
  virtual void initialize(string text, int order);

  virtual string generate(int size);

  void shiftKey(vector<string> &vec, string &str);

 protected:
  // Add any variables you may need here
  map<vector<string>, vector<string>> _map;
  string _text;

  unsigned int _order;
};

#endif
