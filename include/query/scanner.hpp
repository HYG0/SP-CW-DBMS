#pragma once
#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

// #include "parser.hpp" 

class Scanner : public yyFlexLexer {
public:
    explicit Scanner(std::istream &in) : yyFlexLexer(&in) {
    }

    yy::Parser::symbol_type next_token();
};

