#include <string.h>
#include <algorithm>
#pragma once
class Point
{
public:
    double* points;
    int dimension;
    Point();
    Point(char* byteArray, long* position, int _dimension);
    Point(double *coordinates, int _dimension);
    Point(const Point& other);
    ~Point();
    Point& operator=(const Point& other);
    bool operator==(const Point& other);
    long getSize();
    void toByteArray(char* byteArray, long* position);
    Point smaller(const Point& other);
    Point bigger(const Point& other);
};

