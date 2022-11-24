#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace gjson
{

enum class  Type{
    Unknown = 0,
    Bool = 1,
    String = 2,
    Integer = 3,
    Float = 4,
    Object = 5,
    Array = 6,
} ;

struct Value
{
    virtual ~Value() = default;
    using ptr = std::unique_ptr<Value>;
    virtual Type GetType() const {return Type::Unknown;}
};

struct Bool : Value
{
    virtual ~Bool() = default;
    using ptr = std::unique_ptr<Bool>;
    using value_t = bool;

    enum Type GetType() const override {return Type::Bool;}

    value_t value;
};

struct String : Value
{
    virtual ~String() = default;
    using ptr = std::unique_ptr<String>;
    using value_t = std::string;
    enum Type GetType() const override {return Type::String;}

    value_t value;
};

struct Integer : Value
{
    virtual ~Integer() = default;
    using ptr = std::unique_ptr<Integer>;
    using value_t = long long;
    enum Type GetType() const override {return Type::Integer;}

    value_t value;
};

struct Float : Value
{
    virtual ~Float() = default;
    using ptr = std::unique_ptr<Float>;
    using value_t = double;
    enum Type GetType() const override {return Type::Float;}

    value_t value;
};

struct Object : Value
{
    virtual ~Object() = default;
    using ptr = std::unique_ptr<Object>;
    using value_t = std::unordered_map<std::string, Value::ptr>;
    enum Type GetType() const override {return Type::Object;}
    value_t value;

    value_t::iterator begin(){return value.begin();}
    value_t::iterator end(){return value.end();}
    value_t::const_iterator begin() const{return value.cbegin();}
    value_t::const_iterator end() const{return value.cend();}
    value_t::const_iterator cbegin() const{return value.cbegin();}
    value_t::const_iterator cend() const{return value.cend();}
};


struct Array : Value
{
    virtual ~Array() = default;

    using ptr = std::unique_ptr<Array>;
    using value_t = std::vector<Value::ptr>;
    enum Type GetType() const override {return Type::Array;}

    value_t value;

    value_t::iterator begin(){return value.begin();}
    value_t::iterator end(){return value.end();}
    value_t::const_iterator begin() const{return value.cbegin();}
    value_t::const_iterator end() const{return value.cend();}
    value_t::const_iterator cbegin() const{return value.cbegin();}
    value_t::const_iterator cend() const{return value.cend();}
};

}