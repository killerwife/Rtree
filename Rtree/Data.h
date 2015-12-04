#include "MBR.h"
#pragma once
class Data
{
public:
    MBR rectangle;
    std::string name;
    Data();
    Data(char* byteArray,int* position);
    ~Data();
    long getSize();
    virtual void toByteArray(char* byteArray, long* position);
    virtual bool operator==(Data* other);
};

