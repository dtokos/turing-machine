#include "catch.hpp"
#include "bar.hpp"

TEST_CASE("Bar", "[qwe]") {
    REQUIRE( bar_subtract(1, 1) == 0 );
    REQUIRE( bar_subtract(1, 2) == -1 );
    REQUIRE( bar_subtract(2, 2) == 0 );
}
