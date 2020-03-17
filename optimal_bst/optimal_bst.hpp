#ifndef OPTIMAL_BST_OPTIMAL_BST_HPP
#define OPTIMAL_BST_OPTIMAL_BST_HPP

#include "bst.hpp"

#include <vector>
#include <climits>
#include <cassert>

int **optimalBSTRootMatrix(std::vector<double> &p, std::vector<double> &q) {
    int n = p.size();

    double **subtree_cost = new double *[n + 2];
    double **subtree_exp = new double *[n + 2]; //expected_value
    int **root = new int *[n + 1];

    for (int i = 1; i <= n + 1; i++) {
        subtree_cost[i] = new double[n + 1];
        subtree_exp[i] = new double[n + 1];
        root[i] = new int[n + 1];
    }

    //TODO: clear
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            subtree_cost[i][j] = 0;
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            subtree_exp[i][j] = 0;
        }
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            root[i][j] = -1;
        }
    }

    //=======

    for (int i = 1; i <= n + 1; i++) {
        subtree_cost[i][i - 1] = q[i - 1];
        subtree_exp[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            subtree_exp[i][j] = INT_MAX;
            subtree_cost[i][j] = subtree_cost[i][j - 1] + p[j - 1] + q[j]; // TODO: check p[0..n-1]
            for (int r = i; r <= j; r++) {
                double tmp = subtree_exp[i][r - 1] + subtree_exp[r + 1][j] + subtree_cost[i][j];
                if (tmp < subtree_exp[i][j]) {
                    subtree_exp[i][j] = tmp;
                    root[i][j] = r - 1;
                }
            }
        }
    }

    //TODO: clear
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            std::cout << subtree_cost[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            std::cout << subtree_exp[i][j] << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    //=======

    return root;
}

//template<typename DataType>
//BST<DataType> OptimalBST(std::vector<DataType *> &data, std::vector<double> &p, std::vector<double> &q) {
//    assert((p.size() == data.size() == q.size() - 1) && "Invalid vectors");
//
//    auto rootMatrix = optimalBSTRootMatrix(p, q);
//
//
//}

#endif //OPTIMAL_BST_OPTIMAL_BST_HPP
