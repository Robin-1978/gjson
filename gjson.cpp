#include "gjson.h"

#include "token.h"

#include "json.h"
#include "json_lexer.h"

#include <chrono>


void* JsonAlloc(void* (*allocProc)(size_t));
void* Json(void*, int, gjson::Token, gjson::Statement* statement);
void* JsonFree(void*, void(*freeProc)(void*));

namespace gjson {

Value::value_ptr ParseJson(std::istream& is)
{
    void* shellParser = JsonAlloc(malloc);
    JsonLexer lexer(is);
    
    //lexer.token.sv = nullptr;
    auto code = lexer.lex(is);

    gjson::Statement state;
    while(code > 0)
    {
        /*
        std::cout << code <<std::endl;
        switch(code)
        {
            case STRING:
                std::wcout  << "\t" << *lexer.token.sv << std::endl;
                break;
            case FLOAT:
                std::cout  << "\t" << lexer.token.fv << std::endl;
                break;
            case INTEGER:
                std::cout  << "\t" << lexer.token.iv << std::endl;
                break;
            default:
            break;
        }
        */
        Json(shellParser, code, lexer.token, &state);
        
        //lexer.token.sv = nullptr;
        code = lexer.lex();
    }
    Json(shellParser, 0, lexer.token, &state);

    JsonFree(shellParser, free);
    return std::move(state.value);
}

}