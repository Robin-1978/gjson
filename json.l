%top{
  #include <stdlib.h> // strtoul(), strtod()
  #include <iostream> // std::cout etc.
  #include "json.h"
  #include "../token.h"
}

// define yyFlexLexer class variables to collect values in the lexer rules

%class{
public:
    gjson::Token token;
}

%o fast freespace unicode lexer = JsonLexer

digit   [0-9]
digit1  [1-9]
digits  {digit}+
int     -? {digit} | -? {digit1} {digits}
frac    \. {digits}
exp     [eE] [-+]? {digits}
number  {int} {frac} {exp}?

%x STR

%%

[ \t\n\r]+      { /* ignore white space */ }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }  
"{"             { return LBRACE; }
"}"             { return RBRACE;}
","             { return COMMA; }
":"             { return COLON; }

null            { return NIL; }
true            { return TRUE; }
false           { return FALSE; }
{int}           { token.iv = strtoll(text(), NULL, 10); return INTEGER;}
{number}        { token.fv = strtod(text(), NULL); return FLOAT; }
\"              { token.sv = new gjson::String::value_t; token.sv->reserve(128); start(STR); }

<STR>{
\"                      { start(INITIAL); return STRING; }
\\ ["\\/]               { token.sv->push_back(text()[1]); }
\\ b                    { token.sv->push_back('\b'); }
\\ t                    { token.sv->push_back('\t'); }
\\ n                    { token.sv->push_back('\n'); }
\\ f                    { token.sv->push_back('\f'); }
\\ r                    { token.sv->push_back('\r'); }
\\ u [[:xdigit:]]{4}    { token.sv->push_back(strtoul(text() + 2, NULL, 16)); }
[\]-\x7f\x20-\[]        { token.sv->push_back(text()[0]); }
\p{Non_ASCII_Unicode}   { token.sv->append(wstr()); }
}

<*>.            { std::wcout << "Error charactor " << wstr() << std::endl; }

%%