#include <iostream>
#include <fstream>
#include <chrono>

#include "gjson.h"
#include "nl_json.hpp"


void RunNl(char * filename)
{
    auto old = std::chrono::system_clock::now();
    std::ifstream is(filename);
    auto data = nlohmann::json::parse(is);
  
    std::cout << "(nlohmann)Duration:" << (std::chrono::system_clock::now() - old).count() / 1000000.0 <<" ms" << std::endl;
}

void RunMy(char* filename)
{
   auto old = std::chrono::system_clock::now();
 
    std::ifstream is(filename);
    //std::ifstream is("../sample/large-file.json");
    if(is)
    {
        auto pJson = gjson::ParseJson(is);
        if(pJson)
        {
            //pJson->print(std::wcout);
        }
        else
        {
            std::cout << "Parse json failed" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to open file " << filename << std::endl;
    }
    std::cout << "(My)Duration:" << (std::chrono::system_clock::now() - old).count() / 1000000.0 <<" ms" << std::endl;
}

int main(int argc, char*argv[])
{
    std::cout << "json_example <filename>" << std::endl;
     if(argc < 2)
    {
        std::cout << "usage: json_example <filename>" << std::endl;
        return 1;
    }

    //RunNl(argv[1]);
    RunMy(argv[1]);

    return 0;
}