#pragma once

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
    Null = 7,
} ;

struct Value
{
    virtual ~Value() = default;
    virtual Type GetType() const {return Type::Unknown;}
};

struct Null : Value
{
    using value_t = std::nullptr_t;
    enum Type GetType() const override {return Type::Null;}
};

struct Bool : Value
{
    using value_t = bool;
    
    Bool(value_t value) : value(value){};
    virtual ~Bool() = default;


    enum Type GetType() const override {return Type::Bool;}

    value_t value;
};

struct String : Value
{
    using value_t = std::wstring;

    String(const value_t& value) : value(value){};
    virtual ~String() = default;

    enum Type GetType() const override {return Type::String;}

    value_t value;
};

struct Integer : Value
{
    using value_t = long long;
    Integer(const value_t& value) : value(value){};
    virtual ~Integer() = default;
    enum Type GetType() const override {return Type::Integer;}

    value_t value;
};

struct Float : Value
{
    using value_t = double;
    Float(const value_t& value) : value(value){};
    virtual ~Float() = default;
    enum Type GetType() const override {return Type::Float;}

    value_t value;
};

struct Object : Value
{
    virtual ~Object()
    {
        for(auto &o : value)
        {
            delete o.second;
            o.second = nullptr;
        }
        value.clear();
    }
    using value_t = std::unordered_map<std::wstring, Value *>;
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
    virtual ~Array()
    {
        for(auto &o : value)
        {
            delete o;
            o = nullptr;
        }
        value.clear();
    }

    using value_t = std::vector<Value*>;
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