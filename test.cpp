#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "memory.hpp"

TEST_CASE("CPU Initial State", "[CPU][Basic]") {
}

TEST_CASE("CPU Operation ADC", "[CPU][Operation][ADC]") {
    NES::Memory mem;

    mem.write(0xFFFC, 0x0);
    mem.write(0xFFFD, 0x0);
}
