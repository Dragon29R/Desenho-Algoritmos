#include "exercises.h"

#include <cmath>

Result nearestPointsBF(std::vector<Point> &vp) {
    Result res;
    double d = LONG_MAX;
    Point p1(0,0);
    Point p2(0,0);
    for(auto x: vp){
        for (auto y : vp){
            if((x.x!=y.x or x.y!=y.y) and x.distance(y)<d){
                d = x.distance(y);
                res.p1 = x;
                res.p2 = y;
                res.dmin=d;
            }
        }
    }
    return res;
}

/// TESTS ///
#include "gtest/gtest.h"

TEST(TP2_Ex5, testNPBF) {
    testNearestPoints(nearestPointsBF, "Brute force");
}