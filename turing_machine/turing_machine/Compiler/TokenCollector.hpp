#ifndef TokenCollector_hpp
#define TokenCollector_hpp

#include <string>

struct TokenCollector {
    virtual void open(int line, int col) = 0;
    virtual void close(int line, int col) = 0;
    virtual void name(const std::string &name, int line, int col) = 0;
    virtual void symbol(char symbol, int line, int col) = 0;
    virtual void direction(/* direction */ int line, int col) = 0;
    virtual void wildcard(int line, int col) = 0;
    virtual void separator(int line, int col) = 0;
    
    virtual void error(int line, int col) = 0;
};

#endif
