#include "ggh/graph.h"

#include <gtest/gtest.h>

using namespace testing;
using PrimitiveGraph = ggh::graph::Graph<int, double>;

namespace ggh::graph {
TEST(GraphTest, ConstructorDestructorPrimitives)
{
    EXPECT_NO_THROW(PrimitiveGraph());
}

TEST(GraphTest, WHENAddNodeTHENTrue) {
    Graph<int, double> graph;
    auto result{graph.addNode(0)};
    EXPECT_TRUE(result);
}

TEST(GraphTest, WHENReaddNodeTHENfalse) {
    Graph<int, double> graph;
    graph.addNode(0);
    auto result{graph.addNode(0)};
    EXPECT_FALSE(result);
}

TEST(GraphTest, WHENRemoveAddedNodeTHENTrue) {
    Graph<int, double> graph;
    graph.addNode(0);
    auto result{graph.removeNode(0)};
    EXPECT_TRUE(result);
}

TEST(GraphTest, WHENRemoveMissingNodeTHENFalse) {
    Graph<int, double> graph;
    auto result{graph.removeNode(0)};
    EXPECT_FALSE(result);
}

TEST(GraphTest, WHENAddEdgeToNodesTHENTrue) {
    Graph<int, double> graph;
    graph.addNode(0);
    graph.addNode(1);
    auto result{graph.addEdge(0,1,1.0)};
    EXPECT_TRUE(result);
}

TEST(GraphTest, WHENAddEdgeToNodesTHENNodeContainsEdge) {
    Graph<int, double> graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addEdge(0,1,1.0);

    ASSERT_TRUE(graph.contains(0));
    auto node_0{graph.getNodeFromData(0)};
    auto edges{node_0->getEdges()};
    ASSERT_GT(edges.size(), 0);
    auto first_edge{edges.at(0)};
    EXPECT_DOUBLE_EQ(first_edge->getAnnotation(), 1.0 );
    auto adj_node{first_edge->getNodeTo()};
    EXPECT_EQ(adj_node->getData(), 1);
}

}

