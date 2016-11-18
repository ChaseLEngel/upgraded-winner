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
    void setColor(string value);
    string getCurColor();
    vector<string> getCrossedOut();
    void crossOutNeighbors(Node* neighbor);
    int getID() { return m_id;}
  private:
    int m_id;
    string m_curColor;
    vector<string> m_crossedOut;
    vector<Node*> m_crossedNeighbors;
};

#endif
