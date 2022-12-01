#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

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
    using value_ptr = std::unique_ptr<Value>;
    
    virtual ~Value() = default;
    virtual Type GetType() const {return Type::Unknown;}

    virtual std::wostream& print(std::wostream& os, unsigned tab = 0) const = 0;
    std::wostream& print_tab(std::wostream& os, unsigned count) const
    {
        for(auto n=0; n < count; ++n){os << "\t";}
        return os;
    }
};

Value::value_ptr ParseJson(std::istream& is);

struct Null : Value
{
    using value_t = std::nullptr_t;
    enum Type GetType() const override {return Type::Null;}
    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        os << "null";
        return os;
    }
};

struct Bool : Value
{
    using value_t = bool;
    
    Bool(value_t value) : value(value){};
    virtual ~Bool() = default;


    enum Type GetType() const override {return Type::Bool;}

    value_t value;

    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        os << (value ? "true" : "false");
        return os;
    }
};

struct String : Value
{
    using value_t = std::wstring;

    String(const value_t& value) : value(value){};
    virtual ~String() = default;

    enum Type GetType() const override {return Type::String;}

    value_t value;

    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        os << "\"" << value << "\"";
        return os;
    }

};

struct Integer : Value
{
    using value_t = long long;
    Integer(const value_t& value) : value(value){};
    virtual ~Integer() = default;
    enum Type GetType() const override {return Type::Integer;}

    value_t value;

    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        os << value;
        return os;
    }    
};

struct Float : Value
{
    using value_t = double;
    Float(const value_t& value) : value(value){};
    virtual ~Float() = default;
    enum Type GetType() const override {return Type::Float;}

    value_t value;

    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        os << value;
        return os;
    }    
};

struct Object : Value
{
    virtual ~Object() = default;
    using value_t = std::unordered_map<std::wstring, Value::value_ptr>;
    enum Type GetType() const override {return Type::Object;}
    value_t value;

    value_t::iterator begin(){return value.begin();}
    value_t::iterator end(){return value.end();}
    value_t::const_iterator begin() const{return value.cbegin();}
    value_t::const_iterator end() const{return value.cend();}
    value_t::const_iterator cbegin() const{return value.cbegin();}
    value_t::const_iterator cend() const{return value.cend();}

    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        //os << std::endl;
        //print_tab(os, tab);
        os << "{" << std::endl;
        if(!value.empty())
        {
            auto it = value.cbegin();
            for(auto n=0; n < value.size() -1 ; ++n, ++it)
            {
                print_tab(os, tab + 1);
                os << "\"" << it->first << "\""<< ": ";
                it->second->print(os, tab + 1) << "," << std::endl;
            }
 
            print_tab(os, tab + 1);
            os << "\"" << it->first << "\""<< ": ";
            it->second->print(os, tab + 1) << std::endl;

        }
        print_tab(os, tab) << "}";
        return os;
    }    
};


struct Array : Value
{
    virtual ~Array() = default;

    using value_t = std::vector<Value::value_ptr>;
    enum Type GetType() const override {return Type::Array;}
    value_t value;

    value_t::iterator begin(){return value.begin();}
    value_t::iterator end(){return value.end();}
    value_t::const_iterator begin() const{return value.cbegin();}
    value_t::const_iterator end() const{return value.cend();}
    value_t::const_iterator cbegin() const{return value.cbegin();}
    value_t::const_iterator cend() const{return value.cend();}

    std::wostream& print(std::wostream& os, unsigned tab = 0) const override
    {
        //os << std::endl;
        //print_tab(os, tab) << "[" << std::endl;
        os << "[" << std::endl;
        if(!value.empty())
        {
            auto it = value.cbegin();
            for(auto n=0; n < value.size() -1 ; ++n, ++it)
            {
                print_tab(os, tab + 1);
                (*it)->print(os, tab + 1) << "," << std::endl;
            }
            print_tab(os, tab + 1);
            (*it)->print(os, tab + 1) << std::endl;
        }
        print_tab(os, tab) << "]";
        return os;
    }
};

}