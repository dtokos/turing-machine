#ifndef Parser_hpp
#define Parser_hpp

#include "../Lexer/TokenCollector.hpp"
#include "./ParserState.hpp"
#include "./ParserEvent.hpp"
#include "./Builder.hpp"
#include <array>

struct Parser : TokenCollector {
    Parser(Builder &builder) : builder{builder} {}
    
    void openBrace(long line, long col) {
        handleEvent(OpenBrace, line, col);
    }
    
    void closedBrace(long line, long col) {
        handleEvent(ClosedBrace, line, col);
    }
    
    void openAngle(long line, long col) {
        handleEvent(OpenAngle, line, col);
    }
    
    void closedAngle(long line, long col) {
        handleEvent(ClosedAngle, line, col);
    }
    
    void dash(long line, long col) {
        handleEvent(Dash, line, col);
    }
    
    void colon(long line, long col) {
        handleEvent(Colon, line, col);
    }
    
    void symbol(char symbol, long line, long col) {
        builder.setSymbol(symbol);
        handleEvent(Symbol, line, col);
    }
    
    void name(const std::string &name, long line, long col) {
        builder.setName(name);
        handleEvent(Name, line, col);
    }
    
    void error(long line, long col) {
        builder.syntaxError(line, col);
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
        
        Transition{RInputState, Symbol,     SRInputSymbol,  [](Builder &b){ b.setInputSymbol(); }},
        Transition{RInputState, OpenBrace,  MRInputState},
        
        Transition{SRInputSymbol, OpenAngle,    SRDirection, [](Builder &b){ b.setDirectionLeft(); }},
        Transition{SRInputSymbol, Dash,         SRDirection, [](Builder &b){ b.setDirectionNone(); }},
        Transition{SRInputSymbol, ClosedAngle,  SRDirection, [](Builder &b){ b.setDirectionRight(); }},
        
        Transition{SRDirection, Name, SROutputState, [](Builder &b){ b.setOutputState(); }},
        Transition{SRDirection, Dash, SROutputState, [](Builder &b){ b.setNullOutputState(); }},
        
        Transition{SROutputState, Symbol,   Body, [](Builder &b){ b.setOutputSymbol(); }},
        Transition{SROutputState, Dash,     Body, [](Builder &b){ b.setNullOutputSymbol(); }},
        
        Transition{MRInputState, Symbol,        MRInputSymbol,      [](Builder &b){ b.newInputSymbolGroupWithSymbol(); }},
        Transition{MRInputState, OpenBrace,     MRInputSymbolGroup, [](Builder &b){ b.newInputSymbolGroup(); }},
        Transition{MRInputState, ClosedBrace,   Body}, // TODO: Add action
        
        Transition{MRInputSymbolGroup, Symbol,      MRInputSymbolGroup, [](Builder &b){ b.addInputSymbol(); }},
        Transition{MRInputSymbolGroup, ClosedBrace, MRInputSymbol},
        
        Transition{MRInputSymbol, OpenAngle,    MRDirection, [](Builder &b){ b.setDirectionLeft(); }},
        Transition{MRInputSymbol, Dash,         MRDirection, [](Builder &b){ b.setDirectionNone(); }},
        Transition{MRInputSymbol, ClosedAngle,  MRDirection, [](Builder &b){ b.setDirectionRight(); }},
        
        Transition{MRDirection, Name, MROutputState, [](Builder &b){ b.setOutputState(); }},
        Transition{MRDirection, Dash, MROutputState, [](Builder &b){ b.setNullOutputState(); }},
        
        Transition{MROutputState, Symbol,       MRInputState,           [](Builder &b){ b.setOutputSymbol(); }},
        Transition{MROutputState, OpenBrace,    MROutputSymbolGroup,    [](Builder &b){ b.newOutputSymbolGroup(); }},
        
        Transition{MROutputSymbolGroup, Symbol,         MROutputSymbolGroup, [](Builder &b){ b.addOutputSymbol(); }},
        Transition{MROutputSymbolGroup, Dash,           MROutputSymbolGroup, [](Builder &b){ b.addNullOutputSymbol(); }},
        Transition{MROutputSymbolGroup, ClosedBrace,    MRInputState}, // TODO: Add action
    };
    
    
    void handleEvent(ParserEvent event, long line, long col) {
        for (const auto &t : transitions) {
            if (t.state == state && t.event == event) {
                t.action(builder);
                state = t.newState;
                return;
            }
        }
        
        handleEventError(event, line, col);
    }
    
    void handleEventError(ParserEvent event, long line, long col) {
        // TODO: Implement error handling
    }
};

#endif
