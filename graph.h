#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include"node.h"

class Graph{
  public:
    Graph();
    void addNode(int id);
    void addEdge(int from, int to);
    void setColors(std::vector<string>);
    void backTrack();
    void eval();
    Node* findNextNode();
    std::string findNextColor(std::vector<std::string> crossedOutColors);
  
  private:
    std::vector<string> m_colors;
    std::map<int, Node*> nodes;
    std::map<int, std::vector<Node*> > adjList;
    std::queue<Node*> m_backtrack;
};

