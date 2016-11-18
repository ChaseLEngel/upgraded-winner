#include<iostream>
#include<map>
#include<vector>
#include"node.h"

class Graph{
  public:
    Graph();
    void addNode(int id);
    void addEdge(int from, int to);
  private:
    std::map<int, Node*> nodes;
    std::map<int, std::vector<Node*> > adjList;
};

