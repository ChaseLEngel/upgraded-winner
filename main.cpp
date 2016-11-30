#include "graph.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(int argv, char* argc[])
{
  if(argv < 2)
  {
    cerr << "usage: " << argc[0] << " [input_file]" << endl;
    exit(1);
  }

  char* input_file = argc[1];

  ifstream inf;
  inf.open(input_file);
  if(!inf.good())
  {
    cerr << "Error opening input file" << endl;
    exit(1);
  }
  
  /* Read first line, and parse colors. push into vector */
  Graph myGraph;
  vector<string> colors;
  string line;

  getline(inf,line);
  istringstream ist(line);
  string color_value;
  while(ist >> color_value)
  {
    colors.push_back(color_value);
  } 

  myGraph.setColors(colors);

  ist.clear();

  /* Read second line, parse # of Nodes in graph */
  cout << "#nodes" << endl;
  string value;

  getline(inf,line);
  ist.str(line);
  while(ist >> value)
  {
    myGraph.addNode(atoi(value.c_str())); 
  } 
  
  ist.clear();

  /* Read the rest of input file, for the edges */ 
  
  cout << "#edges" << endl;
  while(getline(inf, line))
  {
    int from, to;
    string first, second;
    ist.str(line);

    ist >> from;
    ist >> to;
    myGraph.addEdge(from,to);
    ist.clear();
  }

  myGraph.eval();

  return 0;
}
