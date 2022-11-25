#include <iostream>

#include "calc.h"

int main()
{
    std::cout << "Hello, world!" << std::endl;

    Calc calc;
    calc.Run(std::cin);
    return 0;
}