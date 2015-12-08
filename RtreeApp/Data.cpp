#include "Data.h"


Data::Data()
{
}

Data::Data(char* byteArray, long* position)
{
    rectangle=MBR(byteArray,position);
}

Data::~Data()
{
}

long Data::getSize()
{
    return sizeof(double)*6+sizeof(int) + 20 * sizeof(char);
}

void Data::toByteArray(char* byteArray, long *position)
{
    rectangle.toByteArray(byteArray, position);
    int i;
    for (i = 0; i < name.size(); i++)
    {
        byteArray[*position] = name[i];
        *position++;
    }
    for (; i < 20; i++)
    {
        byteArray[*position] = '\0';
        *position++;
    }
}

bool Data::operator==(Data* other)
{
    if (rectangle == other->rectangle)
    {
        return name == other->name;
    }
    else
    {
        return false;
    }
}

std::string Data::to_string()
{
    std::string output = "";
    return output;
}