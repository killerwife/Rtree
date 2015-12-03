#include <string.h>
#pragma once
class Point
{
public:
    double* points;
    int dimension;
    Point();
    Point(char* byteArray, int* position);
    Point(double *coordinates, int _dimension);
    Point(const Point& other);
    ~Point();
    Point& operator=(const Point& other);
    bool operator==(const Point& other);
    long getSize();
    void toByteArray(char* byteArray, int* position);
};

