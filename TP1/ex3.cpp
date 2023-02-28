// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"

std::vector<int> IntroGraph::bfs(const int & source) const {
    std::vector<int> res;
    std::queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (!findVertex(current)->isVisited()) {
            res.push_back(current);
            findVertex(current)->setVisited(true);

            for (int i = 0; i < findVertex(current)->getAdj().size(); i++) {
                int neighbor = findVertex(current)->getAdj()[i]->getDest()->getId();
                if (!findVertex(neighbor)->isVisited()) {
                    q.push(neighbor);
                }
            }
        }
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, test_bfs) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<int> vs = graph.bfs(1);

    unsigned int ids[] = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}