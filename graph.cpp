#include "graph.h"

using namespace std;

Graph::Graph(){
  m_accept = false;
  m_reject = false;
}

void Graph::addNode(int id){
  cout << "Added Node: " << id << endl;
  Node* tmp = new Node(id);
  assert(tmp != NULL);
  m_nodes.insert(make_pair(id,tmp));
}

void Graph::addEdge(int from, int to){
  cout << "Added Edge from " << from << " to " << to << endl;
  Node* fromNode = m_nodes[from];
  assert(fromNode != NULL);
  Node* toNode= m_nodes[to];
  assert(toNode != NULL);
  m_adjList[from].push_back(toNode);
  m_adjList[to].push_back(fromNode);
}

int Graph::acceptable(){
  cout << "Checking if acceptable: ";
  for(map<int, Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++) {
    if(it->second->getCurColor() == "") {
      cout << "Nope" << endl;
      return false;
    }
  }
  cout << "YATZEE!" << endl;
  return true;
}

void Graph::eval(){
  cout << "Starting eval" << endl;
  // Initialize first node with first color.
  string color = m_colors[0];
  m_nodes[0]->setColor(color);
  while(!m_accept || !m_reject) {
    Node* node = findNextNode();
    assert(node != NULL);
    cout << "Next node to evaluate: " << node->getId() << endl;
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
      assert(tmp != NULL);
      if(!tmp->ifCrossedOut(color)){
        tmp->addCrossedOut(color);
        node->crossOutNeighbors(*it);
        m_backtrack.push(node);
      }
    }
  }
  m_accept = acceptable();
}

void Graph::setColors(vector<string> colors){
  cout << "Setting colors" << endl;
  m_colors = colors; 
}

Node* Graph::findNextNode(){
  int max = INT_MIN;
  int idMin = INT_MIN;
  for(map<int, Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++){
    Node* tmp = it->second;
    assert(tmp != NULL);
    //find node with most crossed out neightbors
    if(max >= tmp->crossedOutSize() && !tmp->hasColor()){
      //if current node has equal crossed out size and its id is lower
      //return lower id node
      if(max == tmp->crossedOutSize() && idMin <= tmp->getId()){
        idMin = tmp->getId();
      }
      max = tmp->crossedOutSize();
    }
  }
  cout << "Found minimum node to be node: " << idMin << endl;
  Node* min_node = m_nodes.find(idMin)->second;
  assert(min_node != NULL);
  return min_node;
}

void Graph::backTrack() {
  cout << "Running backTrack" << endl;
  Node* node = m_backtrack.front();
  cout << "Backtracking to node: " << node->getId() << endl;
  assert(node != NULL);
  m_backtrack.pop();
  string cur_color = node->getCurColor();
  node->undoCrossedOut();
  node->setColor("");
  string next_color = findNextColor(node->getCrossedOut());
  // Node doesn't have any other available colors. Need to backtrack again.
  if(next_color == "") {
    backTrack();
  }
  else {
    node->setColor(next_color);
  }
  // Reject state
  if(node->getId() == 0 && next_color == "") {
    cout << "Reject is true" << endl;
    m_reject = true;
  }
}

string Graph::findNextColor(vector<string> usedColors){
  cout << "Finding next color" << endl;
  string color = "";
  //iterate through colors and find colors taken 
  for(vector<string>::iterator it = m_colors.begin(); it != m_colors.end(); it++){
    color = *it;
  }
  cout << "Found next color to be: " << color << endl;
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
