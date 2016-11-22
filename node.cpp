/*
 * Author: Colby Bates
 * File: node.cpp
 */

#include "node.h"

//Constructor
Node::Node(int value) : m_id(value), m_curColor("")
{
}
//Destructor
Node::~Node()
{

}

int Node::getId()
{
  return m_id;
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

void Node::undoCrossedOut()
{
  for(unsigned int i = 0; i < m_crossedNeighbors.size(); i++)
  {
    m_crossedNeighbors.at(i)->freeColor(m_curColor);
  }
}

void Node::freeColor(string color)
{
  vector<string>::iterator it = find(m_crossedOut.begin(), m_crossedOut.end(), color);
  if(it != m_crossedOut.end())
  {
    m_crossedOut.erase(it);
  }
}

void Node::addCrossedOut(string color)
{
  m_crossedOut.push_back(color);
}

bool Node::ifCrossedOut(string color)
{
  vector<string>::iterator it = find(m_crossedOut.begin(), m_crossedOut.end(), color);
  if(it != m_crossedOut.end())
  {
    return true;
  }
  return false;
}

bool Node::hasColor()
{
  if(m_curColor == "")
  {
    return false;
  }
  else
  {
    return true;
  }
}

int Node::crossedOutSize()
{
  return m_crossedOut.size();
}
