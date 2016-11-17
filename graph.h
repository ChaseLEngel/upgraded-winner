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
    map<int, Node*> nodes;
    map<int, vector<Node*> > adjList;
}
