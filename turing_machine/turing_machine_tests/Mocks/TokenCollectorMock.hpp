#ifndef TokenCollectorMock_hpp
#define TokenCollectorMock_hpp

#include "TokenCollector.hpp"

struct TokenCollectorMock : TokenCollector {
    std::string tokens{};
    
    void openBrace(long line, long col) {
        addToken("OB");
    }
    
    void closeBrace(long line, long col) {
        addToken("CB");
    }
    
    void openAngle(long line, long col) {
        addToken("OA");
    }
    
    void closeAngle(long line, long col) {
        addToken("CA");
    }
    
    void dash(long line, long col) {
        addToken("D");
    }
    
    void colon(long line, long col) {
        addToken("C");
    }
    
    void symbol(char symbol, long line, long col) {
        using namespace std::string_literals;
        addToken("#"s + symbol + "#"s);
    }
    
    void name(const std::string &name, long line, long col) {
        addToken("$" + name + "$");
    }
    
    void error(long line, long col) {
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
