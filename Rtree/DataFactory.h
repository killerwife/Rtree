#include "Data.h"
#pragma once
class DataFactory
{
public:
    DataFactory();
    ~DataFactory();
    virtual Data* getData(char* byteArray, int* position)=0;
    virtual long getMBRSize()=0;
};

