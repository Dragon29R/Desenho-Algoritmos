// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = A[0];
    i = j = 0;
    for (int start = 0; start < n; start++) {
        for (int end = start; end < n; end++) {
            int sum = 0;
            for (int k = start; k <= end; k++) {
                sum += A[k];
            }
            if (sum > maxSum) {
                maxSum = sum;
                i = start;
                j = end;
            }
        }
    }
    return maxSum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}