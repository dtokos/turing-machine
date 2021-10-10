#include "catch.hpp"
#include "Lexer.hpp"
#include "Mocks/TokenCollectorMock.hpp"

TEST_CASE("Test Lexer", "[compiler]") {
    TokenCollectorMock collector{};
    Lexer lexer{collector};
    
    SECTION("Single Token Tests") {
        SECTION("Open Brace") {
            lexer.lex("{");
            REQUIRE( collector.tokens == "OB" );
        };
        
        SECTION("Close Brace") {
            lexer.lex("}");
            REQUIRE( collector.tokens == "CB" );
        };
        
        SECTION("Open Angle") {
            lexer.lex("<");
            REQUIRE( collector.tokens == "OA" );
        };
        
        SECTION("Close Angle") {
            lexer.lex(">");
            REQUIRE( collector.tokens == "CA" );
        };
        
        SECTION("Dash") {
            lexer.lex("-");
            REQUIRE( collector.tokens == "D" );
        };
        
        SECTION("Colon") {
            lexer.lex(":");
            REQUIRE( collector.tokens == "C" );
        };
        
        SECTION("All Single Tokens") {
            lexer.lex("{}<>-:");
            REQUIRE( collector.tokens == "OB,CB,OA,CA,D,C" );
        };
    };
    
    SECTION("Whitespace Tests") {
        SECTION("Space") {
            lexer.lex(" ");
            REQUIRE( collector.tokens == "" );
        };
        
        SECTION("Tab") {
            lexer.lex("\t");
            REQUIRE( collector.tokens == "" );
        };
        
        SECTION("New Line") {
            lexer.lex("\n");
            REQUIRE( collector.tokens == "" );
        };
        
        SECTION("Leading Whitespace") {
            lexer.lex(" \t{");
            REQUIRE( collector.tokens == "OB" );
        };
        
        SECTION("Middle Whitespace") {
            lexer.lex("{ \t}");
            REQUIRE( collector.tokens == "OB,CB" );
        };
        
        SECTION("Trailing Whitespace") {
            lexer.lex("{ \t");
            REQUIRE( collector.tokens == "OB" );
        };
        
        SECTION("Mixed Whitespace") {
            lexer.lex(" {\t}\n< -\t   >\t\t: \t  ");
            REQUIRE( collector.tokens == "OB,CB,OA,D,CA,C" );
        };
    };
    
    SECTION("Symbol Tests") {
        SECTION("Single") {
            lexer.lex("A");
            REQUIRE( collector.tokens == "#A#" );
        };
        
        SECTION("Multiple") {
            lexer.lex("A B");
            REQUIRE( collector.tokens == "#A#,#B#" );
        };
        
        SECTION("Mixed") {
            lexer.lex(" \tA   \t\t B C\tD\t\tE ");
            REQUIRE( collector.tokens == "#A#,#B#,#C#,#D#,#E#" );
        };
        
        SECTION("Alphanumeric") {
            lexer.lex("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 0 1 2 3 4 5 6 7 8 9");
            REQUIRE( collector.tokens == "#A#,#B#,#C#,#D#,#E#,#F#,#G#,#H#,#I#,#J#,#K#,#L#,#M#,#N#,#O#,#P#,#Q#,#R#,#S#,#T#,#U#,#V#,#W#,#X#,#Y#,#Z#,#0#,#1#,#2#,#3#,#4#,#5#,#6#,#7#,#8#,#9#" );
        };
        
        SECTION("Lowercase Alphanumeric") {
            lexer.lex("a b c d e f g h i j k l m n o p q r s t u v w x y z 0 1 2 3 4 5 6 7 8 9");
            REQUIRE( collector.tokens == "#a#,#b#,#c#,#d#,#e#,#f#,#g#,#h#,#i#,#j#,#k#,#l#,#m#,#n#,#o#,#p#,#q#,#r#,#s#,#t#,#u#,#v#,#w#,#x#,#y#,#z#,#0#,#1#,#2#,#3#,#4#,#5#,#6#,#7#,#8#,#9#" );
        };
        
        SECTION("Some Special Symbols") {
            lexer.lex("+ @ # $ ~ ^ & * ] [ ' ; | \\ % ( / ) ! \" _ ? = . ,");
            REQUIRE( collector.tokens == "#+#,#@#,###,#$#,#~#,#^#,#&#,#*#,#]#,#[#,#'#,#;#,#|#,#\\#,#%#,#(#,#/#,#)#,#!#,#\"#,#_#,#?#,#=#,#.#,#,#" );
        };
    };
    
    SECTION("Name Tests") {
        SECTION("Single") {
            lexer.lex("foo");
            REQUIRE( collector.tokens == "$foo$" );
        };
        
        SECTION("Multiple") {
            lexer.lex("foo bar");
            REQUIRE( collector.tokens == "$foo$,$bar$" );
        };
        
        SECTION("Complex") {
            lexer.lex("Foo_bar_123");
            REQUIRE( collector.tokens == "$Foo_bar_123$" );
        };
        
        SECTION("Lorem Ipsum") {
            lexer.lex("Lorem ipsum dolor sit amet consectetur adipiscing elit");
            REQUIRE( collector.tokens == "$Lorem$,$ipsum$,$dolor$,$sit$,$amet$,$consectetur$,$adipiscing$,$elit$" );
        };
    };
};
