#include "MBR.h"
#pragma once
class Data
{
public:
    MBR rectangle;
    std::string name;
    Data();
    Data(char* byteArray,long* position);
    ~Data();
    virtual long getSize();
    virtual void toByteArray(char* byteArray, long* position);
    virtual bool operator==(Data* other);
    virtual std::string to_string();
};

