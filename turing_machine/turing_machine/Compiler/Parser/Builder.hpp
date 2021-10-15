#ifndef Builder_hpp
#define Builder_hpp

#include <string>

struct Builder {
    virtual void setSymbol(char symbol) = 0;
    virtual void setName(const std::string &name) = 0;
    
    virtual void newHeaderWithName() = 0;
    virtual void addHeaderWithValue() = 0;
    
    virtual void newRuleWithState() = 0;
    
    virtual void setInputSymbol() = 0; // TODO: Sort out and simplify
    virtual void newInputSymbolGroupWithSymbol() = 0;
    virtual void newInputSymbolGroup() = 0;
    virtual void addInputSymbol() = 0;
    
    virtual void setDirectionLeft() = 0;
    virtual void setDirectionNone() = 0;
    virtual void setDirectionRight() = 0;
    
    virtual void setNullOutputState() = 0;
    virtual void setOutputState() = 0;
    
    virtual void setNullOutputSymbol() = 0; // TODO: Sort out and simplify
    virtual void setOutputSymbol() = 0;
    virtual void newOutputSymbolGroup() = 0;
    virtual void addOutputSymbol() = 0;
    virtual void addNullOutputSymbol() = 0;

    virtual void done() = 0;
    virtual void syntaxError(long line, long col);
};

#endif
