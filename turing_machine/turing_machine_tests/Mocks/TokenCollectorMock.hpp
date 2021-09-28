#ifndef TokenCollectorMock_hpp
#define TokenCollectorMock_hpp

#include "TokenCollector.hpp"

struct TokenCollectorMock : TokenCollector {
    std::string tokens{};
    
    void open(int line, int col) {
        addToken("O");
    }
    
    void close(int line, int col) {
        addToken("C");
    }
    
    void name(const std::string &name, int line, int col) {
        addToken("$" + name + "$");
    }
    
    void symbol(char symbol, int line, int col) {
        addToken("#" + std::to_string(symbol) + "#");
    }
    
    void direction(int line, int col) {
        addToken("D");
    }
    
    void wildcard(int line, int col) {
        addToken("W");
    }
    
    void separator(int line, int col) {
        addToken("S");
    }
    
    void error(int line, int col) {
        addToken("E" + std::to_string(line) + "/" + std::to_string(col));
    }
    
private:
    bool firstToken{true};
    
    void addToken(const std::string &token) {
        if (!firstToken) tokens += ',';
        tokens += token;
        firstToken = false;
    }
};

#endif
