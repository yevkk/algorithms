#pragma once
#include "catch.hpp"
#include "cyclic_offset.hpp"

TEST_CASE( "Cyclic offset is true", "[cyclic offset]" ) {
    REQUIRE(isCyclicOffset("", ""));
    REQUIRE(isCyclicOffset("a", "a"));
    REQUIRE(isCyclicOffset("Lorem ipsum dolor sit amet", "or sit ametLorem ipsum dol"));
    REQUIRE(isCyclicOffset("abcdefg", "bcdefga"));
    REQUIRE(isCyclicOffset("samplesample", "esamplesampl"));
}

TEST_CASE( "Cyclic offset is false", "[cyclic offset]" ) {
    REQUIRE(!isCyclicOffset("a", ""));
    REQUIRE(!isCyclicOffset("a", "ab"));
    REQUIRE(!isCyclicOffset("Lorem ipsum dolor sit amet", "Lorem ipsum dolor sit"));
    REQUIRE(!isCyclicOffset("abcdefg", "fghabcde"));
    REQUIRE(!isCyclicOffset("samplesample", "esamplesamp"));
}