#include "BasicDataFactory.h"


BasicDataFactory::BasicDataFactory()
{
}


BasicDataFactory::~BasicDataFactory()
{
}

Data* BasicDataFactory::getData(char* byteArray, long* position)
{
    return new Data(byteArray,position);
}

long BasicDataFactory::getDataSize()
{
    Data temp;
    return temp.getSize();
}
