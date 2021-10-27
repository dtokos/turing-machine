#ifndef Parser_hpp
#define Parser_hpp

#include "../Lexer/TokenCollector.hpp"
#include "./ParserState.hpp"
#include "./ParserEvent.hpp"
#include "./Builder.hpp"
#include <array>

struct Parser : TokenCollector {
    Parser(Builder &builder) : builder{builder} {}
    
    void openBrace(const FilePosition pos) {
        handleEvent(OpenBrace, pos);
    }
    
    void closedBrace(const FilePosition pos) {
        handleEvent(ClosedBrace, pos);
    }
    
    void openAngle(const FilePosition pos) {
        handleEvent(OpenAngle, pos);
    }
    
    void closedAngle(const FilePosition pos) {
        handleEvent(ClosedAngle, pos);
    }
    
    void dash(const FilePosition pos) {
        handleEvent(Dash, pos);
    }
    
    void colon(const FilePosition pos) {
        handleEvent(Colon, pos);
    }
    
    void symbol(char symbol, const FilePosition pos) {
        builder.setSymbol(symbol);
        handleEvent(Symbol, pos);
    }
    
    void name(const std::string &name, const FilePosition pos) {
        builder.setName(name);
        handleEvent(Name, pos);
    }
    
    void error(const FilePosition pos) {
        builder.syntaxError(pos);
    }
    
    void handleEvent(ParserEvent event, const FilePosition pos) {
        for (const auto &t : transitions) {
            if (t.state == state && t.event == event) {
                t.action(builder);
                state = t.newState;
                return;
            }
        }
        
        handleEventError(event, pos);
    }
    
private:
    struct Transition {
        using Action = void (*)(Builder &);
        static constexpr Action NoAction = [](Builder &b){};
        
        Transition(ParserState state, ParserEvent event, ParserState newState, Action action)
            : state{state}, event{event}, newState{newState}, action{action} {}
        Transition(ParserState state, ParserEvent event, ParserState newState)
            : Transition{state, event, newState, NoAction} {}
        
        
        ParserState state;
        ParserEvent event;
        ParserState newState;
        Action action;
    };
    
    Builder &builder;
    ParserState state{Header};
    const std::array<Transition, 30> transitions {
        Transition{Header,  Name,       HName,  [](Builder &b){ b.newHeaderWithName(); }},
        Transition{Header,  OpenBrace,  Body},
        Transition{HName,   Colon,      HValue},
        Transition{HValue,  Name,       Header, [](Builder &b){ b.addHeaderWithValue(); }},
        
        Transition{Body,    Name,           RInputState,    [](Builder &b){ b.newRuleWithState(); }},
        Transition{Body,    ClosedBrace,    End,            [](Builder &b){ b.done(); }},
        
        Transition{RInputState, Symbol,     SRInputSymbol,  [](Builder &b){ b.addInputSymbol(); }},
        Transition{RInputState, OpenBrace,  MRInputState},
        
        Transition{SRInputSymbol, OpenAngle,    SRDirection, [](Builder &b){ b.setDirectionLeft(); }},
        Transition{SRInputSymbol, Dash,         SRDirection, [](Builder &b){ b.setDirectionNone(); }},
        Transition{SRInputSymbol, ClosedAngle,  SRDirection, [](Builder &b){ b.setDirectionRight(); }},
        
        Transition{SRDirection, Name, SROutputState, [](Builder &b){ b.setOutputState(); }},
        Transition{SRDirection, Dash, SROutputState, [](Builder &b){ b.setNullOutputState(); }},
        
        Transition{SROutputState, Symbol,   Body, [](Builder &b){ b.addOutputSymbol(); b.addRuleBody(); b.addRule(); }},
        Transition{SROutputState, Dash,     Body, [](Builder &b){ b.setNullOutputSymbol(); b.addRuleBody(); b.addRule(); }},
        
        Transition{MRInputState, Symbol,        MRInputSymbol,      [](Builder &b){ b.addInputSymbol(); }},
        Transition{MRInputState, OpenBrace,     MRInputSymbolGroup, [](Builder &b){ b.addInputSymbol(); }},
        Transition{MRInputState, ClosedBrace,   Body,               [](Builder &b){ b.addRule(); }},
        
        Transition{MRInputSymbolGroup, Symbol,      MRInputSymbolGroup, [](Builder &b){ b.addInputSymbol(); }},
        Transition{MRInputSymbolGroup, ClosedBrace, MRInputSymbol},
        
        Transition{MRInputSymbol, OpenAngle,    MRDirection, [](Builder &b){ b.setDirectionLeft(); }},
        Transition{MRInputSymbol, Dash,         MRDirection, [](Builder &b){ b.setDirectionNone(); }},
        Transition{MRInputSymbol, ClosedAngle,  MRDirection, [](Builder &b){ b.setDirectionRight(); }},
        
        Transition{MRDirection, Name, MROutputState, [](Builder &b){ b.setOutputState(); }},
        Transition{MRDirection, Dash, MROutputState, [](Builder &b){ b.setNullOutputState(); }},
        
        Transition{MROutputState, Symbol,       MRInputState,           [](Builder &b){ b.addOutputSymbol(); b.addRuleBody(); }},
        Transition{MROutputState, OpenBrace,    MROutputSymbolGroup,    [](Builder &b){ b.newOutputSymbolGroup(); }},
        
        Transition{MROutputSymbolGroup, Symbol,         MROutputSymbolGroup, [](Builder &b){ b.addOutputSymbol(); }},
        Transition{MROutputSymbolGroup, Dash,           MROutputSymbolGroup, [](Builder &b){ b.addNullOutputSymbol(); }},
        Transition{MROutputSymbolGroup, ClosedBrace,    MRInputState,        [](Builder &b){ b.addRuleBody(); }},
    };
    
    void handleEventError(ParserEvent event, const FilePosition pos) {
        // TODO: Implement error handling
    }
};

#endif
