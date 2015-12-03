#include "BasicDataFactory.h"


BasicDataFactory::BasicDataFactory()
{
}


BasicDataFactory::~BasicDataFactory()
{
}

Data* BasicDataFactory::getData(char* byteArray, int* position)
{
    return new Data(byteArray,position);
}

long BasicDataFactory::getMBRSize()
{
    return Data().getMBRSize();
}
