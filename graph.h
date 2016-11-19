#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>

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
    std::vector<string> getColors();
    Node* findNextNode();
    std::string findNextColor(std::vector<std::string> crossedOutColors);
  
  private:
    std::vector<string> m_colors;
    std::map<int, Node*> m_nodes;
    std::map<int, std::vector<Node*> > m_adjList;
    std::queue<Node*> m_backtrack;
};
