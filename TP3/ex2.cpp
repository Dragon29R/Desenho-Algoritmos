// By: Gonçalo Leão

#include "exercises.h"

#include <algorithm>
using namespace std;
bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> activitySelectionGR(std::vector<Activity> A) {
    std::vector<Activity> V ;
    sort(A.begin(),A.end());
    unsigned int lower_interval=0;
    for(auto it=A.begin();it!=A.end();it++){
        if(lower_interval<it->start){
            V.push_back(*(it));
            lower_interval=it->finish;
        }
    }
    return V;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP3_Ex2, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionGR(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_THAT(V,  ::testing::UnorderedElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}

