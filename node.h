/*
 * Author: Colby Bates
 * File: node.h
 */

#ifndef NODE_H
#define NODE_H

#include<vector>
#include<string>
#include<algorithm>

using std::string;
using std::vector;

class Node
{
  public:
    Node(int num);
    ~Node();
    int getId();
    void setColor(string value);
    string getCurColor();
    vector<string> getCrossedOut();
    void crossOutNeighbors(Node* neighbor);
    void undoCrossedOut();
    void freeColor(string color);
    void addCrossedOut(string color);
    bool ifCrossedOut(string color);
    bool hasColor();
    int crossedOutSize(); 
  
  private:
    int m_id;
    string m_curColor;
    vector<string> m_crossedOut;
    vector<Node*> m_crossedNeighbors;
};

#endif
