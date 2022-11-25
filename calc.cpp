#include "calc.h"

#include "parser.h"
#include "lexer.h"

void* ParseAlloc(void* (*allocProc)(size_t));
void* Parse(void*, int, Token *, std::map<std::wstring, double>*);
void* ParseFree(void*, void(*freeProc)(void*));

Calc::Calc()
{

}

Calc::~Calc()
{

}

void Calc::Run(std::istream& is)
{
    void* shellParser = ParseAlloc(malloc);
    Lexer lexer(is, std::cout);
    std::string line;

    while(std::getline(is, line))
    {
        std::stringstream ss(line);
        for(;;)
        {
            auto code = lexer.lex(ss);

            while(code > 0)
            {
                std::cout << code << ", " << lexer.token.value << std::endl;
                Parse(shellParser, code, &lexer.token, &memory);
                code = lexer.lex();
            }
            Parse(shellParser, 0, &lexer.token, &memory);
            break;
        }
    }

    ParseFree(shellParser, free);
}