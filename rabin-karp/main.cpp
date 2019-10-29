#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tests.hpp"
#include <vector>
#include "rabin_karp_extended.hpp"

//int main() {
////    Matrix<int> M(4), P(2);
////
////    std::vector<std::vector<int>> a = {{1, 5, 3, 4},
////                                        {7, 1, 5, 6},
////                                        {3, 7, 1, 1},
////                                        {1, 5, 3, 2}};
////
////
////    std::vector<std::vector<int>> b = {{1, 5},
////                                        {7, 1}};
//    Matrix<char> M(4), P(2);
//
//    std::vector<std::vector<char>> a = {{'a', 'f', 'g', 'd'},
//         {'v', 'a', 'f', 'o'},
//         {'g', 'v', 'a', 'a'},
//         {'a', 'f', 'g', 'b'}};
//
//    std::vector<std::vector<char>> b = {{'a', 'f'},
//         {'v', 'a'}};
//
//    for (int i = 0; i < 4; i++)
//        for (int j = 0; j < 4; j++)
//            M(i, j) = a[i][j];
//
//    for (int i = 0; i < 4; i++)
//        for (int j = 0; j < 4; j++)
//            M(i, j) = a[i][j];
//
//    for (int i = 0; i < 2; i++)
//        for (int j = 0; j < 2; j++)
//            P(i, j) = b[i][j];
//
//    std::cout << rabin_karp_extended(M, P);
//
//    return 0;
//}