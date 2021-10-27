#include "catch.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "SyntaxBuilder.hpp"

TEST_CASE("Test Parser", "[compiler][parser]") {
    SyntaxBuilder builder{};
    Parser parser{builder};
    Lexer lexer{parser};
    
    SECTION("Header Tests") {
        SECTION("No Headers") {
            lexer.lex("{}");
            parser.handleEvent(EoF, {0, 0});
            REQUIRE( builder.getTM().toString() == ".\n" );
        };

        SECTION("Single Header") {
            lexer.lex("n1:v1{}");
            parser.handleEvent(EoF, {0, 0});
            REQUIRE( builder.getTM().toString() == "n1:v1\n.\n" );
        };
        
        SECTION("Multiple Headers") {
            lexer.lex("n1:v1 n2:v2{}");
            parser.handleEvent(EoF, {0, 0});
            REQUIRE( builder.getTM().toString() == "n1:v1\nn2:v2\n.\n" );
        };
    };
    
    SECTION("Rule Tests") {
        SECTION("Single Rule") {
            lexer.lex("{s1 a > s2 b}");
            parser.handleEvent(EoF, {0, 0});
            REQUIRE(
                builder.getTM().toString() ==
                "{\n"
                    "s1 a > s2 b\n"
                "}\n"
                ".\n"
            );
        };
    };
};
