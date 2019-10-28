#pragma once

#include "rabin_karp_extended.hpp"
#include "catch.hpp"

TEST_CASE("matrix with char values", "[rabin-karp extended]") {
    std::vector<std::vector<char>> a;
    std::vector<std::vector<char>> b;

    SECTION("size 4 2") {
        Matrix<char> M(4), P(2);

        a = {{'a', 'f', 'g', 'd'},
             {'v', 'a', 'f', 'o'},
             {'g', 'v', 'a', 'a'},
             {'a', 'f', 'g', 'b'}};

        b = {{'a', 'f'},
             {'v', 'a'}};

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                M(i, j) = a[i][j];

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                P(i, j) = b[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 2);

        a = {{'r', 'd', 'g', 'd'},
             {'v', 'd', 'f', 'o'},
             {'g', 'v', 'a', 'a'},
             {'a', 'f', 'g', 'b'}};

        b = {{'b', 'b'},
             {'b', 'b'}};

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                M(i, j) = a[i][j];

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                P(i, j) = b[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 0);

        a = {{'a', 'a', 'a', 'a'},
             {'a', 'a', 'a', 'a'},
             {'a', 'a', 'a', 'a'},
             {'a', 'a', 'a', 'a'}};

        b = {{'a', 'a'},
             {'a', 'a'}};

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                M(i, j) = a[i][j];

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                P(i, j) = b[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 9);
    }

    SECTION("size 2 4") {
        Matrix<char> M(2), P(4);

        a = {{'a', 'f', 'g', 'd'},
             {'v', 'a', 'f', 'o'},
             {'g', 'v', 'a', 'a'},
             {'a', 'f', 'g', 'b'}};

        b = {{'a', 'f'},
             {'v', 'a'}};

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                M(i, j) = b[i][j];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                P(i, j) = a[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 0);
    }

    SECTION("size 3 3") {
        Matrix<char> M(3), P(3);

        a = {{'a', 'f', 'g'},
             {'v', 'a', 'f'},
             {'g', 'v', 'a'}};

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                M(i, j) = a[i][j];

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                P(i, j) = a[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 1);

        a = {{'a', 'f', 'g'},
             {'v', 'a', 'f'},
             {'g', 'v', 'a'}};

        b = {{'b', 'f', 'g'},
             {'v', 'a', 'f'},
             {'5', 'b', 'a'}};


        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                M(i, j) = a[i][j];

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                P(i, j) = b[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 0);
    }

}

TEST_CASE("matrix with int values", "[rabin-karp extended]") {
    std::vector<std::vector<int>> a;
    std::vector<std::vector<int>> b;

    SECTION("size 4 2") {
        Matrix<int> M(4), P(2);

        a = {{1, 2, 3, 1},
             {3, 12, 2, 3},
             {2, 3, 12, 2},
             {12, 2, 5, 4}};

        b = {{2, 3},
             {12, 2}};

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                M(i, j) = a[i][j];

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                P(i, j) = b[i][j];

        REQUIRE(rabin_karp_extended(M, P) == 3);
    }
}