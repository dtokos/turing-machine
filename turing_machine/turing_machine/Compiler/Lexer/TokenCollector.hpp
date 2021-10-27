#ifndef TokenCollector_hpp
#define TokenCollector_hpp

#include <string>
#include "../FilePosition.hpp"

struct TokenCollector {
    virtual void openBrace(const FilePosition pos) = 0;
    virtual void closedBrace(const FilePosition pos) = 0;
    virtual void openAngle(const FilePosition pos) = 0;
    virtual void closedAngle(const FilePosition pos) = 0;
    virtual void dash(const FilePosition pos) = 0;
    virtual void colon(const FilePosition pos) = 0;
    
    virtual void symbol(char symbol, const FilePosition pos) = 0;
    virtual void name(const std::string &name, const FilePosition pos) = 0;
    
    virtual void error(const FilePosition pos) = 0;
};

#endif
