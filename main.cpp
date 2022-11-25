#include <iostream>

#include "gjson.h"
#include "jparser.h"

int main()
{
    std::cout << "Hello, world!" << std::endl;

    Calc calc;
    calc.Run(std::cin);
    return 0;
}