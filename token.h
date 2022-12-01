#pragma once

#include <string>
#include <iostream>
#include "gjson.h"

namespace gjson
{
struct Token
{
    Float::value_t fv;    
    Integer::value_t iv;
    String::value_t* sv;
};

struct Statement
{
    gjson::Value::value_ptr value;
};

}