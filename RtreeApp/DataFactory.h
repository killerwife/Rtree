#include "Data.h"
#pragma once
class DataFactory
{
public:
    DataFactory();
    virtual ~DataFactory();
    virtual Data* getData(char* byteArray, long* position) = 0;
    virtual long getDataSize()=0;
    virtual Data* getData(Data* temp)=0;
};

