#include "catch.hpp"
#include "foo.hpp"

TEST_CASE("Foo", "[asd]") {
    REQUIRE( foo_add(1, 1) == 2 );
    REQUIRE( foo_add(1, 2) == 3 );
    REQUIRE( foo_add(2, 2) == 4 );
}
