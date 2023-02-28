// By: Gonçalo Leão

#include "exercises.h"

std::vector<int> IntroGraph::topsort() const {
    std::vector<int> res;

    for (auto v : vertexSet) {
        v->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    std::queue<Vertex *> q;
    for (auto v : vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while( !q.empty() ) {
        Vertex* v = q.front();
        q.pop();
        res.push_back(v->getId());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
        //std::cout << "Impossible topological ordering!" << std::endl;
        res.clear();
        return res;
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

void expectTopSort(const IntroGraph graph, std::vector<int> topOrder){
    for(auto u: graph.getVertexSet()) {
        auto itrU = std::find(topOrder.begin(), topOrder.end(), u->getId());
        unsigned int indexU = std::distance(topOrder.begin(), itrU);
        for(auto edge: u->getAdj()) {
            auto v = edge->getDest();
            auto itrV = std::find(topOrder.begin(), topOrder.end(), v->getId());
            unsigned int indexV = std::distance(topOrder.begin(), itrV);
            EXPECT_LT(indexU,indexV);
        }
    }
}

TEST(TP1_Ex4, test_topsort) {
    IntroGraph myGraph;
    myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
    myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(1, 4, 0);
    myGraph.addEdge(1, 3, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(2, 4, 0);
    myGraph.addEdge(3, 6, 0);
    myGraph.addEdge(4, 3, 0);
    myGraph.addEdge(4, 6, 0);
    myGraph.addEdge(4, 7, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(5, 7, 0);
    myGraph.addEdge(7, 6, 0);

    std::vector<int> topOrder = myGraph.topsort();
    EXPECT_EQ(topOrder.size(), 7);
    expectTopSort(myGraph, topOrder); // example of two valid topsorts: "1 2 5 4 3 7 6" and "1 2 5 4 7 3 6"

    // to test including a cycle in the graph
    myGraph.addEdge(3, 1, 0);

    topOrder = myGraph.topsort();
    EXPECT_EQ(topOrder.size(), 0);
}