%include {   
#include <iostream>
#include "../token.h"
#include "json_lexer.h"

}  

%token_type {gjson::Token}  
%type value { gjson::Value*}
%type object { gjson::Object*}
%type object_list { gjson::Object*}
%type array { gjson::Array*}
%type array_list { gjson::Array*}

%name Json
%extra_argument {gjson::Statement* statement}

%syntax_error {  
  std::cout << "Syntax error!" << std::endl;  
}   
%parse_failure {
  std::cout << "Parse failure!" << std::endl; 
}

start ::= object(A). { statement->value = gjson::Value::value_ptr(A); }
start ::= array(A). { statement->value = gjson::Value::value_ptr(A); }

object(A) ::= LBRACE object_list(B) RBRACE. { 
  A = B; 
  //std::wcout << "Object Object: " << std::endl;
}
object_list(A) ::= object_list(B) COMMA STRING(C) COLON value(D). { 
  B->value[*C.sv] = gjson::Value::value_ptr(D); A = B; 
  //std::wcout << "Multi object list: " << *C.sv << std::endl;
  delete C.sv;
}
object_list(A) ::= STRING(B) COLON value(C). { 
  A = new gjson::Object; A->value[*B.sv] = gjson::Value::value_ptr(C); 
  //std::wcout << "One object list: " << *B.sv << std::endl;
  delete B.sv;
}
object_list(A) ::= . { 
  A = new gjson::Object; 
  //std::wcout << "Empty object list: " << std::endl;
}

array(A) ::= LBRACKET array_list(B) RBRACKET. { 
  A = B; 
  //std::wcout << "Array Object: " << std::endl;
}
array_list(A) ::= array_list(B) COMMA value(C). { 
  B->value.emplace_back(gjson::Value::value_ptr(C)); A = B;
  //std::wcout << "Multi array list: " << std::endl;
}
array_list(A) ::= value(B). { 
  A = new gjson::Array; A->value.emplace_back(gjson::Value::value_ptr(B)); 
  //std::wcout << "One array list: " << std::endl;
}
array_list(A) ::= . { 
  A = new gjson::Array; 
  //std::wcout << "Empty array list: " << std::endl;
}

value(A) ::= object(B). { 
  A = B; 
  //std::wcout << "object: " << std::endl;
}
value(A) ::= array(B). {
  A = B; 
  //std::wcout << "array: " << std::endl;
}
value(A) ::= TRUE. {
  A = new gjson::Bool(true);
  //std::wcout << "TRUE: " << std::endl;
}
value(A) ::= FALSE. { 
  A = new gjson::Bool(false); 
  //std::wcout << "FALSE: " << std::endl;
}
value(A) ::= NIL. { 
  A = new gjson::Null;
  //std::wcout << "NIL: " << std::endl;
}
value(A) ::= FLOAT(B). {
  A = new gjson::Float{B.fv};  
  //std::wcout << "FLOAT: " << B.fv << std::endl;
}
value(A) ::= INTEGER(B). { 
  A =  new gjson::Integer{B.iv}; 
  //std::wcout << "INTEGER: " << B.iv << std::endl;
}
value(A) ::= STRING(B). {
  A =  new gjson::String{std::move(*B.sv)};
  //std::wcout << "STRING: " << *B.sv<< std::endl;
  delete B.sv;
}

