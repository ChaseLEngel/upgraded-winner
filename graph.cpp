#include "graph.h"

using namespace std;

Graph::Graph(){
  m_accept = false;
  m_reject = false;
}

void Graph::addNode(int id){
  cout << id << endl;
  Node* tmp = new Node(id);
  assert(tmp != NULL);
  m_nodes.insert(make_pair(id,tmp));
}

void Graph::addEdge(int from, int to){
  cout << from << " " << to << endl;
  Node* fromNode = m_nodes[from];
  assert(fromNode != NULL);
  Node* toNode= m_nodes[to];
  assert(toNode != NULL);
  m_adjList[from].push_back(toNode);
  m_adjList[to].push_back(fromNode);
}

bool Graph::acceptable(){
  for(map<int, Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++) {
    if(it->second->getCurColor() == "") {
      return false;
    }
  }
  return true;
}

void Graph::eval(){
  while(!m_accept && !m_reject) {
    Node* node = findNextNode();
    assert(node != NULL);
    string color = findNextColor(node->getCrossedOut());
    if(color == ""){
      backTrack();
    }
    else{
      node->setColor(color);
      m_backtrack.push(node);

      vector<Node*> neighbors = m_adjList.find(node->getId())->second;
      for(vector<Node*>::iterator it = neighbors.begin(); it != neighbors.end();it++){
        Node* tmp = *it;
        assert(tmp != NULL);
        if(!tmp->ifCrossedOut(color)){
          tmp->addCrossedOut(color);
          node->crossOutNeighbors(*it);
        }
      }
    }
    m_accept = acceptable();
  }
  if(m_accept) {
    printAssignedColors();
  }
  else {
    cout << "Rejected" << endl;
    exit(1);
  }
}

void Graph::setColors(vector<string> colors){
  m_colors = colors; 
}

Node* Graph::findNextNode(){
  // Node that has the most crossed out colors and has minimum id.
  Node* minNode = NULL;
  // Keep track of minimum node's id.
  int minId = INT_MAX;
  // Keep track of node with max crossed out colors.
  int maxCrossedOut = INT_MIN;
  // For all nodes in m_nodes
  for(auto pair : m_nodes) {
    Node* node = pair.second;
    assert(node != NULL);
    // Does node have less than or equal number of crossed out colors as previous node
    // and node has already color?
    if(node->crossedOutSize() >= maxCrossedOut && !node->hasColor()) {
      if(node->crossedOutSize() == maxCrossedOut && node->getId() > minId) {
        continue;
      }
      minNode = node;
      maxCrossedOut = node->crossedOutSize();
      minId = node->getId();
    }
  }
  assert(minNode != NULL);
  return minNode;
}

void Graph::backTrack() {
  Node* node = m_backtrack.top();
  assert(node != NULL);
  m_backtrack.pop();
  string cur_color = node->getCurColor();
  node->undoCrossedOut();
  node->setColor("");
  string next_color = findNextColor(node->getCrossedOut());
  // Reject state
  if(node->getId() == 0 && next_color == cur_color) {
    m_reject = true;
    return;
  }
  // Node doesn't have any other available colors. Need to backtrack again.
  if(next_color == "" || next_color == cur_color) {
    backTrack();
  }
  else {
    node->setColor(next_color);
    m_backtrack.push(node);
  }
}

string Graph::findNextColor(vector<string> usedColors){
  if(m_colors.size() == usedColors.size())
  {
    return ""; 
  }
  string chosen_color = "";
  bool chosenFlag = true;
  //iterate through colors and find colors taken 
  for(auto color : m_colors){
    for(auto usedColor : usedColors)
    {
      if(color == usedColor)
      {
        chosenFlag = false;
        break;
      } 
    }
    if(chosenFlag){
      chosen_color = color;
      break;
    }
    chosenFlag = true;

  }
  return chosen_color;
}

void Graph::printAssignedColors() {
  cout << "#results" << endl;
  for(auto node : m_nodes) {
    cout << node.second->getId() << " " << node.second->getCurColor() << endl;
  }
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
