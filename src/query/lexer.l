%{
#include "query/scanner.hpp"

#undef YY_DECL
#define YY_DECL yy::Parser::symbol_type Scanner::next_token()
%}

%option c++
%option yyclass="Scanner"

%option noyywrap nounput noinput

blank       [ \t\r\n]+
comment     "--"[^\n]*
string      \"([^\"\\]|\\.)*\"
timestamp   [0-9]{4}"."[0-9]{2}"."[0-9]{2}"-"[0-9]{2}":"[0-9]{2}":"[0-9]{2}"."[0-9]{3,6}
number      0|[1-9][0-9]*
identifier  [a-zA-Z_][a-zA-Z0-9_]*

%%
{blank}   { /* skip */ }
{comment} { /* skip */ }
%%