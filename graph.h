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
    void setColors(std::vector<string>);
    void backTrack();
    void eval();
    void print();
    void printAssignedColors();
    std::vector<string> getColors();
    Node* findNextNode();
    std::string findNextColor(std::vector<std::string> crossedOutColors);
    bool acceptable();
  private:
    std::vector<string> m_colors;
    std::map<int, Node*> m_nodes;
    std::map<int, std::vector<Node*> > m_adjList;
    std::stack<Node*> m_backtrack;
    bool m_accept;
    bool m_reject;
};
