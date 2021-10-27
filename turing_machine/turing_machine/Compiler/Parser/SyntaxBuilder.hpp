#ifndef SyntaxBuilder_hpp
#define SyntaxBuilder_hpp

#include <string>
#include "./TMSyntax.hpp"
#include "./Builder.hpp"

struct SyntaxBuilder : Builder {
private:
    TMSyntax tm{};
    TMSyntax::Header header{};
    TMSyntax::Rule rule{};
    TMSyntax::SubRule subrule{};
    
    char symbol{};
    std::string name{};
    
public:
    void setSymbol(char s) {
        symbol = s;
    }
    
    void setName(const std::string &n) {
        name = n;
    }
    
    void newHeaderWithName() {
        header = TMSyntax::Header{};
        header.name = name;
    }
    
    void addHeaderWithValue() {
        header.value = name;
        tm.headers.push_back(header);
    }
    
    void newRuleWithState() {
        rule = TMSyntax::Rule{};
        rule.inputState = name;
    }
    
    void addRule() {
        tm.rules.push_back(rule);
    }
    
    void addRuleBody() {
        rule.body.push_back(subrule);
    }
    
    /*void setInputSymbol() {
        
    }

    void newInputSymbolGroupWithSymbol() {
        
    }

    void newInputSymbolGroup() {
        
    }*/
    
    void addInputSymbol() {
        subrule.inputSymbols.push_back(symbol);
    }
    
    void setDirectionLeft() {
        subrule.direction = TMSyntax::Left;
    }
    
    void setDirectionNone() {
        subrule.direction = TMSyntax::None;
    }
    
    void setDirectionRight() {
        subrule.direction = TMSyntax::Right;
    }
    
    void setNullOutputState() {
        subrule.outputState = "";
    }
    
    void setOutputState() {
        subrule.outputState = name;
    }
    
    void setNullOutputSymbol() {
        newOutputSymbolGroup();
        rule.body.push_back(subrule);
    }
    
    /*void setOutputSymbol() {
        ruleBody.outputSymbols.push_back(symbol);
    }*/
    
    void newOutputSymbolGroup() {
        subrule.outputSymbols = TMSyntax::OutputSymbols{};
    }
    
    void addOutputSymbol() {
        subrule.outputSymbols.push_back(symbol);
    }
    
    void addNullOutputSymbol() {
        subrule.outputSymbols.push_back(std::nullopt);
    }
    
    void done() {
        tm.isDone = true;
    }
    
    void syntaxError(const FilePosition pos) {
        // TODO: Implement errors
    }
    
    TMSyntax getTM() {
        return tm;
    }
};

#endif
