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

Data* RealEstateDataFactory::getData(Data* temp)
{
    RealEstate* realEstate = (RealEstate*)temp;
    return new RealEstate(realEstate->ID,realEstate->name,realEstate->description,realEstate->coordinates,realEstate->count);
}

long RealEstateDataFactory::getDataSize()
{
    RealEstate temp;
    return temp.getSize();
}
