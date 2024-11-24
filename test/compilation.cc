// provides main(); this line is required in only one .cpp file
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "engine/sandbox.hh"

TEST_CASE("Basic circuit compilation") {
    Sandbox sandbox;
    Board* board = static_cast<Board *>(sandbox.toplevels().at(0).get());
}