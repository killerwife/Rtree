#pragma once
#include "DataFactory.h"
#include "RealEstate.h"
class RealEstateDataFactory :
    public DataFactory
{
public:
    RealEstateDataFactory();
    ~RealEstateDataFactory();
    virtual Data* getData(char* byteArray, long* position)override;
    virtual long getDataSize()override;
};

