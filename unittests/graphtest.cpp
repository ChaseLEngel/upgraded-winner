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
