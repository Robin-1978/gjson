// An interactive calculator with Unicode identifier variables
// Builds with bison-bridge to pass Lexer object 'lexer' to bison parser
// $ reflex calc.l
// $ bison -y -d calc.y
// $ c++ -o calc y.tab.c lex.yy.cpp -lreflex
// Example:
// $ ./calc
// π = 3.14
// => 3.14
// π/2
// => 1.57

%top{
  #include <cstdlib>
  #include <string>
  #include <map>

  // fixes problem with Bison 2.7 that needs the Lexer class type:
  //class REFLEX_OPTION_lexer;  // = %option lexer (which is 'Lexer' by default)

  #include "parser.h"
}

%{
  extern void yyerror(Lexer *lexer, const char *msg);
%}

%class{
 private:
  std::wstring                  var;
  double num;
}

%option fast unicode freespace

var    \p{UnicodeIdentifierStart} \p{UnicodeIdentifierPart}*
exp    [Ee] [-+]? \d+
num    \d* (\d | \.\d | \d\.) \d* {exp}?

%%

{var}        { var = wstr(); return 'V'; }
{num}        { num = strtod(text(), NULL); return 'N'; }
"-"          { return MINUS; }
"+" { return PLUS; }
"*" { return TIMES; }
"/" { return DIVIDE; }
\s           // ignore space
.            { yyerror(this, "mystery character"); }

%%