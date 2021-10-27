#ifndef TMSyntax_hpp
#define TMSyntax_hpp

#include <string>
#include <vector>
#include <optional>
#include <algorithm>

struct TMSyntax {
    using Symbol = char;
    using State = std::string;
    using OutputSymbol = std::optional<Symbol>;
    using InputSymbols = std::vector<Symbol>;
    using OutputSymbols = std::vector<OutputSymbol>;
    
    enum Direction {
        Left,
        Right,
        None,
    };
    
    struct Header {
        std::string name;
        std::string value;
    };
    
    struct SubRule {
        InputSymbols inputSymbols;
        Direction direction;
        State outputState;
        OutputSymbols outputSymbols;
    };
        
    using RuleBody = std::vector<SubRule>;
    struct Rule {
        State inputState;
        RuleBody body;
    };
    
    // TODO: Implement errors
    bool isDone{false};
    std::vector<Header> headers{};
    std::vector<Rule> rules{};
    
    std::string toString() {
        return formatHeaders() + formatRules() + formatDone();
    }
    
private:
    std::string formatHeaders() {
        return std::accumulate(
            std::begin(headers),
            std::end(headers),
            std::string{},
            [this](const std::string &acc, const Header &h) {return acc + formatHeader(h);}
       );
    }
    
    std::string formatHeader(const Header &h) {
        return h.name + ":" + h.value + "\n";
    }
    
    std::string formatRules() {
        if (rules.empty()) return "";
        return std::accumulate(
            std::begin(rules),
            std::end(rules),
            std::string{},
            [this](const std::string &acc, const Rule &r) {return acc + formatRule(r);}
        );
    }
    
    std::string formatRule(const Rule &r) {
        return "";
    };
    
    std::string formatDone() {
        return isDone ? ".\n" : "";
    }
};

#endif
