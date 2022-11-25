#pragma once

#include <iostream>
#include <string>
#include <map>

struct Token
{
std::wstring str;
double value;
int line, column;
};

class Calc
{
public:
    Calc();
    virtual ~Calc();
    virtual void Run(std::istream& is);	

 private:
    std::map<std::wstring, double> memory;
};