#include "point.h"

Point::Point()
{
    dimension = 1;
    points = new double[dimension];
    points[0] = 0;
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
