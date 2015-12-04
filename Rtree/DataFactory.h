#include "Data.h"
#pragma once
class DataFactory
{
public:
    DataFactory();
    ~DataFactory();
    virtual Data* getData(char* byteArray, long* position) = 0;
    virtual long getDataSize()=0;
};

