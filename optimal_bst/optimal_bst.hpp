#ifndef OPTIMAL_BST_OPTIMAL_BST_HPP
#define OPTIMAL_BST_OPTIMAL_BST_HPP

#include <vector>
#include <climits>

int** optimalBSTRootMatrix(std::vector<double> p, std::vector<double> q) {
    int n = p.size();

    double **subtree_cost = new double *[n + 2];
    double **subtree_exp = new double *[n + 2]; //expected_value
    int **root = new int *[n + 1];

    for (int i = 1; i <= n + 1; i++) {
        subtree_cost[i] = new double[n + 1];
        subtree_exp[i] = new double[n + 1];
        root[i] = new int[n + 1];
    }

    for (int i = 1; i <= n; i++) {
        subtree_cost[i][i - 1] = q[i - 1];
        subtree_exp[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n; i++) {
            j = i + length - 1;
            subtree_exp[i][j] = INT_MAX;
            subtree_cost[i][j] = subtree_cost[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                int tmp = subtree_exp[i][r - 1] + subtree_exp[r + 1][j] + subtree_cost[i][j];
                if (tmp < subtree_exp[i][j]) {
                    subtree_exp[i][j] = tmp;
                    root[i][j] = r;
                }
            }
        }
    }

    return root;
}

#endif //OPTIMAL_BST_OPTIMAL_BST_HPP
