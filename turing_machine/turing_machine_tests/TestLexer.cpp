#include "catch.hpp"
#include "Lexer.hpp"
#include "Mocks/TokenCollectorMock.hpp"

TEST_CASE("Test Lexer", "[compiler]") {
    TokenCollectorMock collector{};
    Lexer lexer{collector};
    
    SECTION("Single Token Tests") {
        SECTION("Open") {
            lexer.lex("{");
            REQUIRE( collector.tokens == "O" );
        };
    };
};
