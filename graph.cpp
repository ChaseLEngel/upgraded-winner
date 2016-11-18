#include<iostream>
#include<algorithm>
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
  Node* fromNode = nodes.find(from)->second;
  Node* toNode= nodes.find(from)->second;
  map<int, vector<Node*> > :: iterator it = adjList.find(from);
  map<int, vector<Node*> > :: iterator itt = adjList.find(to);

  /*if from element isn't in the list creates a vec and pushes neighbor edge 
   * onto it. Then pairs vec and element in map*/
  if(it == adjList.end())  
  {                       
    vector<Node*> fromVec;
    fromVec.push_back(toNode);
    adjList.insert(make_pair(from, fromVec));
  }
  /*if value is in list then new edge is added to list*/
  else{
    it->second.push_back(toNode);
  }

  /*same proccess as above but added to the "to" element's Adj List*/
  if(itt == adjList.end()){
    vector<Node*> toVec;
    toVec.push_back(fromNode);
    adjList.insert(make_pair(to, toVec));
  }
  else{
    itt->second.push_back(fromNode);
  }
}
void Graph::setColors(vector<string> colors){
  m_colors = colors; 
}

void Graph::eval(){
  Node* tmp = findNextNode();

}

Node* Graph::findNextNode(){
  return 0;
}

void Graph::backTrack(){
}

string Graph::findNextColor(vector<string> usedColors){
  string color = "";
  //iterate through colors and find colors taken 
  for(vector<string>::iterator it = m_colors.begin(); it != m_colors.end(); it++){
    color = *it;
    if(find(usedColors.begin(), usedColors.end(), color) != usedColors.end()){
      return color;
    }
    else{
      color = "";
    }
  }
  return color;
}
