#ifndef TokenCollectorMock_hpp
#define TokenCollectorMock_hpp

#include "TokenCollector.hpp"

struct TokenCollectorMock : TokenCollector {
    std::string tokens{};
    
    void openBrace(const FilePosition pos) {
        addToken("OB");
    }
    
    void closedBrace(const FilePosition pos) {
        addToken("CB");
    }
    
    void openAngle(const FilePosition pos) {
        addToken("OA");
    }
    
    void closedAngle(const FilePosition pos) {
        addToken("CA");
    }
    
    void dash(const FilePosition pos) {
        addToken("D");
    }
    
    void colon(const FilePosition pos) {
        addToken("C");
    }
    
    void symbol(char symbol, const FilePosition pos) {
        using namespace std::string_literals;
        addToken("#"s + symbol + "#"s);
    }
    
    void name(const std::string &name, const FilePosition pos) {
        addToken("$" + name + "$");
    }
    
    void error(const FilePosition pos) {
        addToken("E" + std::to_string(pos.line) + "/" + std::to_string(pos.column));
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
