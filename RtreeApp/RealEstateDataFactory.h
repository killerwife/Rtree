#pragma once
#include "DataFactory.h"
#include "RealEstate.h"
class RealEstateDataFactory :
    public DataFactory
{
public:
    RealEstateDataFactory();
    virtual ~RealEstateDataFactory() override;
    virtual Data* getData(char* byteArray, long* position)override;
    virtual Data* getData(Data* temp)override;
    virtual long getDataSize()override;
};

