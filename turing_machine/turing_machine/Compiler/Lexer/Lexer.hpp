#ifndef Lexer_hpp
#define Lexer_hpp

#include <sstream>
#include <regex>
#include "./TokenCollector.hpp"
#include "../FilePosition.hpp"

struct Lexer {
    Lexer(TokenCollector &collector) : collector{collector} {}
    void lex(const std::string &input) {
        std::istringstream stream{input};
        lex(stream);
    }
    
    void lex(std::istream &input) {
        lineNumber = 1;
        for (std::string line; std::getline(input, line);) {
            lexLine(line);
            ++lineNumber;
        }
    }
    
private:
    TokenCollector &collector;
    
    std::size_t lineNumber{};
    std::string::const_iterator lineStart{};
    std::string::const_iterator lineEnd{};
    
    const std::regex whitespacePattern{R"/(^\s+)/"};
    const std::regex symbolPattern{R"/(^.{1}(?:[\s{}<>\-:]+|$))/"};
    const std::regex namePattern{R"/(^(\w{2,})(?:\W+|$))/"};
    
    void lexLine(const std::string &line) {
        auto cursor = std::begin(line);
        for (lineStart = cursor, lineEnd = std::end(line); cursor != lineEnd;)
            lexToken(cursor);
    }
    
    void lexToken(std::string::const_iterator &cursor) {
        if (!findToken(cursor)) {
            ++cursor;
            collector.error(position(cursor));
        }
    }
    
    bool findToken(std::string::const_iterator &cursor) {
        return (
            findWhitespace(cursor) ||
            findSingleCharToken(cursor) ||
            findSymbol(cursor) ||
            findName(cursor)
        );
    }
    
    bool findWhitespace(std::string::const_iterator &cursor) {
        std::smatch match;
        std::regex_search(cursor, lineEnd, match, whitespacePattern);
        
        if (!match.empty()) {
            cursor += match.length(0);
            return true;
        }
        
        return false;
    }
    
    bool findSingleCharToken(std::string::const_iterator &cursor) {
        switch (*cursor) {
            case '{':
                collector.openBrace(position(cursor));
                break;
            case '}':
                collector.closedBrace(position(cursor));
                break;
            case '<':
                collector.openAngle(position(cursor));
                break;
            case '>':
                collector.closedAngle(position(cursor));
                break;
            case '-':
                collector.dash(position(cursor));
                break;
            case ':':
                collector.colon(position(cursor));
                break;
                
            default:
                return false;
        }
        
        ++cursor;
        return true;
    }
    
    bool findSymbol(std::string::const_iterator &cursor) {
        std::smatch match;
        std::regex_search(cursor, lineEnd, match, symbolPattern);
        
        if (!match.empty()) {
            collector.symbol(*cursor, position(cursor));
            ++cursor;
            return true;
        }
        
        return false;
    }
    
    bool findName(std::string::const_iterator &cursor) {
        std::smatch match;
        std::regex_search(cursor, lineEnd, match, namePattern);
        
        if (!match.empty()) {
            collector.name(match.str(1), position(cursor));
            cursor += match.length(1);
            return true;
        }
        
        return false;
    }
    
    FilePosition position(const std::string::const_iterator &cursor) {
        return FilePosition{lineNumber, static_cast<std::size_t>(cursor - lineStart)};
    }
};

#endif
