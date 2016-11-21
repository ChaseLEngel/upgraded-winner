#include <gtest/gtest.h>
#include <vector>
#include "../graph.h"

class GraphTest : public ::testing::Test {
  protected:
    GraphTest() {}
    virtual ~GraphTest() {}
    void SetUp() {}
    virtual void TearDown() {}
};

TEST(GraphTest, setListOfColors) {
  Graph graph = Graph();
  std::vector<string> expected_colors {"red", "blue", "green", "brown"};
  graph.setColors(expected_colors);
  vector<string> actual_colors = graph.getColors();
  ASSERT_EQ(expected_colors.size(), actual_colors.size());
  for(int i = 0; i < actual_colors.size(); i++) {
    ASSERT_EQ(actual_colors[i], expected_colors[i]);
  }
}

TEST(GraphTest, findFirstColorWithoutAnyCrossedOutColors) {
  Graph graph = Graph();
  std::vector<string> colors {"red", "blue", "green", "brown"};
  graph.setColors(colors);
  Node* node = new Node(0);
  string next_color = graph.findNextColor(node->getCrossedOut());
  ASSERT_EQ(next_color, "red");
  delete node;
}

TEST(GraphTest, findSecondColorWithCrossedOutColors) {
  Graph graph = Graph();
  std::vector<string> colors {"red", "blue", "green", "brown"};
  graph.setColors(colors);
  Node* node = new Node(0);
  node->addCrossedOut("red");
  string next_color = graph.findNextColor(node->getCrossedOut());
  ASSERT_EQ(next_color, "blue");
  delete node;
}

TEST(GraphTest, findFirstColorWithCrossedOutColors) {
  Graph graph = Graph();
  std::vector<string> colors {"red", "blue", "green", "brown"};
  graph.setColors(colors);
  Node* node = new Node(0);
  node->addCrossedOut("blue");
  string next_color = graph.findNextColor(node->getCrossedOut());
  ASSERT_EQ(next_color, "red");
  delete node;
}

TEST(GraphTest, findNextColorShouldReturnEmpty) {
  Graph graph = Graph();
  std::vector<string> colors {"red", "blue", "green", "brown"};
  graph.setColors(colors);
  Node* node = new Node(0);
  for(int i = 0; i < colors.size(); i++) {
    node->addCrossedOut(colors[i]);
  }
  string next_color = graph.findNextColor(node->getCrossedOut());
  ASSERT_EQ(next_color, "");
  delete node;
}


TEST(GraphTest, findFirstNodeInGraph) {
  Graph graph = Graph();
  for(int i = 0; i < 4; i++) {
    graph.addNode(i);
  }
  Node* found_node = graph.findNextNode();
  // Make sure we have a good return
  ASSERT_TRUE(NULL != found_node);
  // and that it is the expected node.
  ASSERT_EQ(0, found_node->getId());
}
