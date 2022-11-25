
%include {   
#include <iostream>
#include "lexer.h"

}  

%token_type {Token *}  
%type expr { int }

%left PLUS MINUS.   
%left DIVIDE TIMES.  
%left LPAR RPAR.
%right NOT.


%extra_argument { std::map<std::wstring, double>* memory }

%syntax_error {  
  std::cout << "Syntax error!" << std::endl;  
}   
%parse_failure {
  std::cout << "Parse failure!" << std::endl; 
}

stm ::= expr(A). {std::cout << "Result=" << A << std::endl;}
stm ::= IDENTIFIER(A) ASSIGN expr(B). {
  (*memory)[A->str] = B;
}


expr(A) ::= LPAR expr(B) RPAR. { A = B; }
expr(A) ::= expr(B) MINUS  expr(C).   { A = B - C; }  
expr(A) ::= expr(B) PLUS  expr(C).   { A = B + C; }  
expr(A) ::= expr(B) TIMES  expr(C).   { A = B * C; }  
expr(A) ::= expr(B) DIVIDE expr(C).  { 
         if(C != 0){
           A = B / C;
          }else{
           std::cout << "divide by zero" << std::endl;
           }
}  /* end of DIVIDE */
expr(A) ::= IDENTIFIER(B). { 
  auto it = memory->find(B->str);
  if(it != memory->end())
  {
    A = it->second;
  }
  else{
    std::wcout << "Variable not found(" << B->str << ")" << std::endl;
  }
}

expr(A) ::= INTEGER(B). { A = B->value; } 
expr(A) ::= MINUS INTEGER(B). [NOT] { A = - B->value; } 