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
    // Set node color
    void setColor(string value);
    // Returns what color node has been set to.
    string getCurColor();
    // Returns all colors node cannot be.
    vector<string> getCrossedOut();
    // Using node color, crosses out all node's neighbors.
    void crossOutNeighbors(Node* neighbor);
    // Uncrosses out color on node's neighbors. Used for backtrack.
    void undoCrossedOut();
    // Removes color from crossed out vector.
    void freeColor(string color);
    // Adds color to list of colors node can't be.
    void addCrossedOut(string color);
    // Checks if node can be assigned specific color.
    bool ifCrossedOut(string color);
    // Checks if node have been assigned color.
    bool hasColor();
    // Returns size of m_crossedOut vector.
    int crossedOutSize(); 
  
  private:
    int m_id;
    string m_curColor;
    vector<string> m_crossedOut;
    vector<Node*> m_crossedNeighbors;
};

#endif
