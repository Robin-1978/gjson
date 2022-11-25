#pragma once

#include <string>
#include "gjson.h"

namespace gjson
{
struct Token
{
    Float::value_t fv;    
    Integer::value_t iv;
    String::value_t sv;
};

}