// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"
using namespace std;
std::vector<int> IntroGraph::dfs(const int & source) const {
    vector<int> result;
    Vertex * start = findVertex(source);
    if (start == nullptr)
        return result;

    stack<Vertex*> s;
    s.push(start);
    stack<Vertex*> reverse;
    while (!s.empty()) {
        Vertex *current = s.top();
        s.pop();
        if (!current->isVisited()) {
            current->setVisited(true);
            result.push_back(current->getId());
            for ( auto e : current->getAdj()) {
                if (!e->getDest()->isVisited()) {
                    reverse.push(e->getDest());
                }
            }
            while(!reverse.empty()){
                s.push(reverse.top());
                reverse.pop();
            }
        }
    }

    for (auto v : vertexSet)
        v->setVisited(false);

    return result;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, test_dfs) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<int> vs = graph.dfs(1);

    unsigned int ids[] = {1, 2, 5, 6, 3, 7, 4};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}