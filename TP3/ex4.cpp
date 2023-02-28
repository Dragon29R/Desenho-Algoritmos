// By: Gonçalo Leão

#include "exercises.h"

#include <algorithm>
struct ratio_bozo{
    int indice;
    double valor;
    double peso;
    double ratio;
    double used;
};
double fractionalKnapsackGR(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    for(int i=0;i<n;i++)usedItems[i]=0.0;
    double final=0.0;
    unsigned int  weightleft = maxWeight;
    std::vector<ratio_bozo> listoftheall;
    for(auto i=0;i<n;i++){
        ratio_bozo atual;
        atual.indice = i;
        atual.peso=weights[i];
        atual.valor=values[i];
        atual.ratio= atual.valor/atual.peso;
        atual.used=0;
        listoftheall.push_back(atual);
    }
    std::sort(listoftheall.begin(), listoftheall.end(), [](const ratio_bozo& a, const ratio_bozo& b) {
        return a.ratio > b.ratio;
    });
    for(int i=0;i<listoftheall.size();i++){
        if(weightleft>0){
            if(listoftheall[i].peso<weightleft){
                weightleft-=listoftheall[i].peso;
                final+=listoftheall[i].valor;
                listoftheall[i].used++;
            }
            else{

                final+=listoftheall[i].ratio*weightleft;
                listoftheall[i].used += static_cast<double>(weightleft) / static_cast<double>(listoftheall[i].peso);
                weightleft=0;
            }
        }
    }
    std::sort(listoftheall.begin(), listoftheall.end(), [](const ratio_bozo& a, const ratio_bozo& b) {
        return a.indice < b.indice;
    });
    for(int i=0;i<n;i++){
        usedItems[i]=listoftheall[i].used;
    }
    return final;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP3_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}

