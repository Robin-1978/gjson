%top{
  #include <cstdlib>
  #include <string>
  #include <map>

  // fixes problem with Bison 2.7 that needs the Lexer class type:
  //class REFLEX_OPTION_lexer;  // = %option lexer (which is 'Lexer' by default)

  #include "parser.h"
  #include "../jparser.h"
}

%{
  extern void yyerror(Lexer *lexer, const char *msg);
%}

%class{
 public:
  Token token;
}

%option fast unicode freespace

var    \p{UnicodeIdentifierStart} \p{UnicodeIdentifierPart}*
exp    [Ee] [-+]? \d+
num    \d* (\d | \.\d | \d\.) \d* {exp}?

%%

{var}        { token.str = wstr(); return IDENTIFIER; }
{num}        { token.value = strtod(text(), NULL); return INTEGER; }
"-"          { return MINUS; }
"+"          { return PLUS; }
"*"          { return TIMES; }
"/"          { return DIVIDE; }
"("          { return LPAR; }
")"          { return RPAR; }
"="          { return ASSIGN;}
\s           // ignore space
.            { std::cout<<"mystery character"; }

%%