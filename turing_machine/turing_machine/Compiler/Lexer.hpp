#ifndef Lexer_hpp
#define Lexer_hpp

#include <sstream>
#include "./TokenCollector.hpp"

struct Lexer {
    Lexer(TokenCollector &collector) : collector{collector} {}
    void lex(const std::string &input) {
        std::istringstream stream{input};
        lex(stream);
    }
    
    void lex(std::istream &input) {
        lineNumber = 1;
        for (std::string line; std::getline(input, line);) {
            lexLine(line);
            ++lineNumber;
        }
    }
    
private:
    TokenCollector &collector;
    int lineNumber{};
    int colNumber{};
    
    void lexLine(const std::string &line) {
        for (auto it = std::begin(line); it != std::end(line);)
            lexToken(it);
    }
    
    void lexToken(std::string::const_iterator &it) {
        if (!findToken(it)) {
            ++it;
            collector.error(lineNumber, ++colNumber);
        }
    }
    
    bool findToken(std::string::const_iterator &it) {
        return false;
    }
};

#endif
