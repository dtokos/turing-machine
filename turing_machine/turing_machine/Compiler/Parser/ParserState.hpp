#ifndef ParserState_hpp
#define ParserState_hpp

enum ParserState {
    Header,
    
    HName,
    HValue,
    
    Body,
    
    RInputState,
    
    SRInputSymbol,
    SRDirection,
    SROutputState,
    
    MRInputState,
    MRInputSymbol,
    MRInputSymbolGroup,
    MRDirection,
    MROutputState,
    MROutputSymbolGroup,
    
    End,
};

#endif
