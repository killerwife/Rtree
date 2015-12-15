#include "point.h"

Point::Point()
{
    points = nullptr;
    dimension = 2;
}

Point::Point(char* byteArray, long* position, int _dimension)
{
    dimension = _dimension;
    points = new double[dimension];
    memcpy(points, byteArray + *position, sizeof(double)*dimension);
    (*position) += sizeof(double)*dimension;    
}

Point::Point(double *coordinates,int _dimension)
{
    dimension = _dimension;
    points = coordinates;
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
    if (points != nullptr)
    {
        delete[]points;
        points = new double[dimension];
    }
    else
    {
        points = new double[dimension];
    }
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
    }
    return true;
}

Point Point::smaller(const Point& other)
{
    double *tempPoints = new double[dimension];
    for (int i = 0; i < dimension; i++)
    {
        tempPoints[i] = std::min(points[i], other.points[i]);
    }
    Point temp(tempPoints,dimension);
    return temp;
}

Point Point::bigger(const Point& other)
{
    double *tempPoints = new double[dimension];
    for (int i = 0; i < dimension; i++)
    {
        tempPoints[i] = std::max(points[i], other.points[i]);
    }
    Point temp(tempPoints, dimension);
    return temp;
}

long Point::getSize()
{
    return sizeof(double)*dimension;
}

void Point::toByteArray(char* byteArray, long* position)
{
    memcpy(byteArray+*position,points,sizeof(double)*dimension);
    (*position) += sizeof(double)*dimension;    
}
