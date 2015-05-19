//
// Created by Michal Miszczyszyn on 19/05/15.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../PI2.hpp"


TEST_CASE( "should raise to given power", "[modularPow]" ) {
    REQUIRE( modularPow(2, 0, 100) == 1 );
    REQUIRE( modularPow(2, 1, 100) == 2 );
    REQUIRE( modularPow(2, 2, 100) == 4 );
    REQUIRE( modularPow(2, 3, 100) == 8 );

    REQUIRE( modularPow(10, 0, 100) == 1 );
    REQUIRE( modularPow(10, 1, 100) == 10 );
    REQUIRE( modularPow(10, 2, 1000000) == 100 );
    REQUIRE( modularPow(10, 3, 1000000) == 1000 );
}

TEST_CASE( "should use modular arithmetic", "[modularPow]" ) {
    REQUIRE( modularPow(2, 3, 2) == 0 );
    REQUIRE( modularPow(2, 16, 2) == 0 );
    REQUIRE( modularPow(2, 100000, 2) == 0 );
}

TEST_CASE( "should convert float to hext", "[hexFromFloat]" ) {
    char hex[] = "0123456789ABCDEF";

    for (unsigned i = 0; i < 15; ++i) {
        float val = static_cast<float>(i) / 16.0f;
        REQUIRE( hexFromFloat(val) == hex[i] );
    }
}

TEST_CASE( "should trim non-fractional values", "[hexFromFloat]" ) {
    char hex[] = "0123456789ABCDEF";

    for (unsigned i = 0; i < 15; ++i) {
        float val = 1.0f + static_cast<float>(i) / 16.0f;
        REQUIRE( hexFromFloat(val) == hex[i] );
    }
}
