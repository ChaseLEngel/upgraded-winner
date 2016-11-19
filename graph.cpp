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
  m_nodes.insert(make_pair(id,tmp));
}

void Graph::addEdge(int from, int to){
  Node* fromNode = m_nodes[from];
  Node* toNode= m_nodes[to];
  m_adjList[from].push_back(toNode);
  m_adjList[to].push_back(fromNode);
}

void Graph::eval(){
  Node* node = findNextNode();
  string color = findNextColor(node->getCrossedOut());
  if(color == ""){
    backTrack();
  }
  else{
    node->setColor(color);
  }

  vector<Node*> neighbors = m_adjList.find(node->getId())->second;
  for(vector<Node*>::iterator it = neighbors.begin(); it != neighbors.end();it++){
    Node* tmp = *it;
    if(!tmp->ifCrossedOut(color)){
      tmp->addCrossedOut(color);
      node->crossOutNeighbors(*it);
      m_backtrack.push(node);
    }
  }
}

void Graph::setColors(vector<string> colors){
  m_colors = colors; 
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
  }
  return color;
}

void Graph::print()
{
  cout << "PRINTING GRAPH" << endl;
  cout << "==============" << endl << endl;
  cout << "Printing Colors:" << endl;
  for(unsigned int i = 0; i < m_colors.size(); i++)
  {
    cout << m_colors[i] << " ";
  }
  cout << endl << endl;

  cout << "Printing Node List:" << endl;
  typedef map<int,Node*>::iterator it_type;
  for(it_type iterator = m_nodes.begin(); iterator != m_nodes.end(); iterator++)
  {
    cout << iterator->first << " ";
  }
  cout << endl << endl;

  cout << "Printing Edge List:" << endl; 
  typedef map<int,vector<Node*> >::iterator it;
  for(it iterator = m_adjList.begin(); iterator != m_adjList.end(); iterator++)
  {
    cout << "Node [" << iterator->first << "]" << endl; 
    cout << "   Adjacency list: " << endl;
    cout << "   ";
    int size = iterator->second.size();
    for(int i = 0; i < size; i++)
    {
      cout << iterator->second[i]->getId() << " "; 
    }
    cout << endl;
  }
}

std::vector<string> Graph::getColors() {
  return m_colors;
}
