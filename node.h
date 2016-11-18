/*
 * Author: Colby Bates
 * File: node.h
 */

#ifndef NODE_H
#define NODE_H

#include<vector>
#include<string>

using std::string;
using std::vector;

class Node
{
  public:
    Node(int num);
    ~Node();
    void set_color(string value);
    string get_cur_color();
    vector<string> get_crossed_out();
  
  private:
    int id;
    string cur_color;
    vector<string> crossed_out;
};

#endif
