#ifndef TMSyntax_hpp
#define TMSyntax_hpp

#include <string>

struct TMSytax {
    using Symbol = char;
    
    struct Header {
        std::string name;
        std::string value;
    };
    
    struct Rule {
        std::string inputState;
    };
    
    struct RuleBody {
        Symbol inputSymbol; // TODO: Add support for multiple symbols
        Direction direction;
        std::string outputState;
        Symbol outputSymbol; // TODO: Add Support for multiple symbols
    };
    
    enum Direction {
        Left,
        Right,
        None,
    };
    
    // TODO: Implement errors
};

#endif
