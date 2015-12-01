#pragma once
class Point
{
public:
    double* points;
    int dimension;
    Point();
    Point(double *coordinates, int _dimension);
    Point(const Point& other);
    ~Point();
    Point& operator=(const Point& rhs);
};

