#include<iostream>
#include<map>
#include<vector>
#include<stack>
#include<algorithm>
#include<cassert>
#include<climits>

#include"node.h"

class Graph{
  public:
    Graph();
    void addNode(int id);
    void addEdge(int from, int to);
    // Initialize all possible colors for nodes.
    void setColors(std::vector<string>);
    void backTrack();
    // Start algorithm
    void eval();
    void print();
    void printAssignedColors();
    std::vector<string> getColors();
    // Finds node with most crossed out colors.
    Node* findNextNode();
    // Finds next possible color node.
    std::string findNextColor(std::vector<std::string> crossedOutColors);
    // Check if all nodes have color.
    bool acceptable();
  private:
    std::vector<string> m_colors;
    std::map<int, Node*> m_nodes;
    std::map<int, std::vector<Node*> > m_adjList;
    std::stack<Node*> m_backtrack;
    bool m_accept;
    bool m_reject;
};
