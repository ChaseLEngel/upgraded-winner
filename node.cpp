/*
 * Author: Colby Bates
 * File: node.cpp
 */

#include "node.h"
//Constructor
Node::Node(int value) : id(value), cur_color("Empty")
{
}
//Destructor
Node::~Node()
{

}

void Node::set_color(string value)
{
  cur_color = value;
}

string Node::get_cur_color()
{
  return cur_color;
}

vector<string> Node::get_crossed_out()
{
  return crossed_out;
}
void Node::cross_out_neighbors(Node* neighbor)
{
  crossed_neighbors.push_back(neighbor);
}
