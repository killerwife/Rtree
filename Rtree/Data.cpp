#include "Data.h"


Data::Data()
{
}

Data::Data(char* byteArray, int* position)
{
    rectangle=MBR(byteArray,position);
}

Data::~Data()
{
}

long Data::getSize()
{
    return rectangle.getSize() + 20 * sizeof(char);
}

void Data::toByteArray(char* byteArray, int *position)
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

long Data::getMBRSize()
{
    double points[3] = {1,2,3};
    double points2[3] = {3,4,5};
    MBR temp(Point(points,3),Point(points2,3));
    return temp.getSize();
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