#ifndef TokenCollector_hpp
#define TokenCollector_hpp

#include <string>

struct TokenCollector {
    virtual void openBrace(long line, long col) = 0;
    virtual void closedBrace(long line, long col) = 0;
    virtual void openAngle(long line, long col) = 0;
    virtual void closedAngle(long line, long col) = 0;
    virtual void dash(long line, long col) = 0;
    virtual void colon(long line, long col) = 0;
    
    virtual void symbol(char symbol, long line, long col) = 0;
    virtual void name(const std::string &name, long line, long col) = 0;
    
    virtual void error(long line, long col) = 0;
};

#endif
