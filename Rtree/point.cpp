#include "point.h"

Point::Point()
{
    dimension = 1;
    points = new double[dimension];
    points[0] = 0;
}

Point::Point(char* byteArray, int* position)
{
    memcpy(&dimension, byteArray + *position, sizeof(double));
    *position += sizeof(double);
    points = new double[dimension];
    memcpy(points, byteArray + *position, sizeof(double)*dimension);
    *position += sizeof(double)*dimension;    
}

Point::Point(double *coordinates,int _dimension)
{
    dimension = _dimension;
    points = new double[dimension];
    for (int i = 0; i < dimension; i++)
    {
        points[i] = coordinates[i];
    }
}

Point::Point(const Point& other)
{
    dimension = other.dimension;
    points = new double[dimension];
    for (int i = 0; i < dimension; i++)
    {
        points[i] = other.points[i];
    }
}

Point::~Point()
{
    delete[]points;
}

Point& Point::operator=(const Point& other)
{
    dimension = other.dimension;
    points = new double[dimension];
    for (int i = 0; i < dimension; i++)
    {
        points[i] = other.points[i];
    }
    return *this;
}

bool Point::operator==(const Point& other)
{
    for (int i = 0; i < dimension; i++)
    {
        if (points[i] != other.points[i])
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

long Point::getSize()
{
    return sizeof(double)*dimension + sizeof(int);
}

void Point::toByteArray(char* byteArray, int* position)
{
    memcpy(byteArray + *position, &dimension, sizeof(double));
    *position += sizeof(double);
    memcpy(byteArray+*position,points,sizeof(double)*dimension);
    *position += sizeof(double)*dimension;    
}
