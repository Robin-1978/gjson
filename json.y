%include {   
#include <iostream>
#include "../token.h"
#include "json_lexer.h"
}  

%token_type {gjson::Token *}  
%type value { gjson::Value*}
%type object { gjson::Object*}
%type object_list { gjson::Object*}
%type array { gjson::Array*}
%type array_list { gjson::Array*}


%extra_argument {gjson::Value*& value}

%syntax_error {  
  std::cout << "Syntax error!" << std::endl;  
}   
%parse_failure {
  std::cout << "Parse failure!" << std::endl; 
}

start ::= object(A). { value = A; }
start ::= array(A). { value = A; }

object(A) ::= LBRACE object_list(B) RBRACE. { A = B; }
object_list(A) ::= object_list(B) COMMA STRING(C) COLON value(D). { B->value[C->sv] = D; A = B; }
object_list(A) ::= STRING(B) COLON value(C). { A = new gjson::Object; A->value[B->sv] = C; }
object_list(A) ::= . { A = new gjson::Object; }

array(A) ::= LBRACKET array_list(B) RBRACKET. { A = B; }
array_list(A) ::= array_list(B) COMMA value(C). { B->value.push_back(C); A = B;}
array_list(A) ::= value(B). { A = new gjson::Array; A->value.push_back(B); }
array_list(A) ::= . { A = new gjson::Array; }

value(A) ::= object(B). { A = B; }
value(A) ::= array(B). { A = B; }
value(A) ::= TRUE. { A = new gjson::Bool(true); }
value(A) ::= FALSE. { A = new gjson::Bool(false); }
value(A) ::= NIL. { A = new gjson::Null; }
value(A) ::= FLOAT(B). { A = new gjson::Float{B->fv};  }
value(A) ::= INTEGER(B). { A =  new gjson::Integer{B->iv}; }
value(A) ::= STRING(B). { A =  new gjson::String{B->sv}; }

