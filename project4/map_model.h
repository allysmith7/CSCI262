/*
   CSCI 262 Data Structures, Fall 2019, Project 4 - Markov

   Author: Cole Smith

   Modified: 10/28/2019
*/

#ifndef _MAP_MODEL_H
#define _MAP_MODEL_H

#include "model.h"

using namespace std;

class map_model : public markov_model {
 public:
  virtual void initialize(string text, int order);

  virtual string generate(int size);

 protected:
  // Add any variables you may need here
  map<string, vector<string>> _map;
  string _text;
  unsigned int _order;
};

#endif
