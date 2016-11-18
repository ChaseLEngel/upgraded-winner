/*
 * Author: Colby Bates
 * File: node.cpp
 */

#include "node.h"
//Constructor
Node::Node(int value) : m_id(value), m_curColor("Empty")
{
}
//Destructor
Node::~Node()
{

}

void Node::setColor(string value)
{
  m_curColor = value;
}

string Node::getCurColor()
{
  return m_curColor;
}

vector<string> Node::getCrossedOut()
{
  return m_crossedOut;
}
void Node::crossOutNeighbors(Node* neighbor)
{
  m_crossedNeighbors.push_back(neighbor);
}
