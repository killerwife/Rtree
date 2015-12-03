#pragma once
#include "DataFactory.h"
#include "Data.h"
class BasicDataFactory :
    public DataFactory
{
public:
    BasicDataFactory();
    ~BasicDataFactory();
    virtual Data* getData(char* byteArray, int* position)override;
    virtual long getMBRSize()override;
};

