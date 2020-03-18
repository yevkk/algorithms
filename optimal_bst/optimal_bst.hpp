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

    for (int i = 1; i <= n + 1; i++) {
        subtree_cost[i][i - 1] = q[i - 1];
        subtree_exp[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            subtree_exp[i][j] = INT_MAX;
            subtree_cost[i][j] = subtree_cost[i][j - 1] + p[j - 1] + q[j];
            for (int r = i; r <= j; r++) {
                double tmp = subtree_exp[i][r - 1] + subtree_exp[r + 1][j] + subtree_cost[i][j];
                if (tmp < subtree_exp[i][j]) {
                    subtree_exp[i][j] = tmp;
                    root[i][j] = r;
                }
            }
        }
    }

    return root;
}

template<typename DataType>
BSTNode<DataType> *
restoreOptimalBST(std::vector<DataType> &data, int **rootMatrix, int indexI, int indexJ, BSTNode<DataType> *parent) {
    if (indexI < 1 || indexJ > data.size() || indexJ < indexI) return nullptr;
    if (indexI == indexJ) {
        auto node = new BSTNode<DataType>(data[indexI - 1]);

        node->parent = parent;
        node->left = node->right = nullptr;

        return node;
    } else {
        int index = rootMatrix[indexI][indexJ];

        auto node = new BSTNode<DataType>(data[index - 1]);
        node->parent = parent;
        node->left = restoreOptimalBST(data, rootMatrix, indexI, index - 1, node);
        node->right = restoreOptimalBST(data, rootMatrix, index + 1, indexJ, node);

        return node;
    }
}

template<typename DataType>
BST<DataType> optimalBST(std::vector<DataType> &data, std::vector<double> &frequency,
                         std::vector<double> &frequency_f) { //TODO: rename frequency_f;

    auto rootMatrix = optimalBSTRootMatrix(frequency, frequency_f);

    BST<DataType> tree;
    tree.root = restoreOptimalBST<DataType>(data, rootMatrix, 1, data.size(), nullptr);

    return tree;
}

#endif //OPTIMAL_BST_OPTIMAL_BST_HPP
