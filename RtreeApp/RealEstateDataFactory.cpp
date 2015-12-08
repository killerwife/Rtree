#include "RealEstateDataFactory.h"


RealEstateDataFactory::RealEstateDataFactory()
{
}


RealEstateDataFactory::~RealEstateDataFactory()
{
}

Data* RealEstateDataFactory::getData(char* byteArray, long* position)
{
    return new RealEstate(byteArray, position);
}

long RealEstateDataFactory::getDataSize()
{
    RealEstate temp;
    return temp.getSize();
}
