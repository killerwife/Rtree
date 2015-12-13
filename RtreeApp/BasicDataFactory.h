#pragma once
#include "DataFactory.h"
#include "Data.h"
class BasicDataFactory :
    public DataFactory
{
public:
    BasicDataFactory();
    virtual ~BasicDataFactory() override;
    virtual Data* getData(char* byteArray, long* position)override;
    virtual long getDataSize()override;
};

