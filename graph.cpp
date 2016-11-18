#include<iostream>
#include<map>
#include<vector>
#include "graph.h"
#include "node.h"

using namespace std;

Graph::Graph(){
}

void Graph::addNode(int id){

  Node* tmp = new Node(id);
  nodes.insert(make_pair(id,tmp));

}

void Graph::addEdge(int from, int to){
  Node* fromNode = adjList.find(from);
  Node* toNode= adjList.find(from);
  map<string, vector<Neighbor*> > :: iterator it = adjList.find(from);
  map<string, vector<Neighbor*> > :: iterator itt = adjList.find(to);

  /*if from element isn't in the list creates a vec and pushes neighbor edge 
   * onto it. Then pairs vec and element in map*/
  if(it == adjList.end())  
  {                       
    vector<Node*> fromNeighborVec;
    fromNeighborVec.push_back(toNode);
    adjList.insert(make_pair(from, fromNeighborVec));
  }
  /*if value is in list then new edge is added to list*/
  else{
    it->second.push_back(to);
  }

  /*same proccess as above but added to the "to" element's Adj List*/
  if(itt == adjList.end()){
    vector<Neighbor*> toNeighborVec;
    toNeighborVec.push_back(fromNode);
    adjList.insert(make_pair(to, toNeighborVec));
  }
  else{
    itt->second.push_back(fromNode);
  }
}

