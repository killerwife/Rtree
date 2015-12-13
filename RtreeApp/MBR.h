#include "Point.h"
#include <string>
#include <math.h>
#pragma once
class MBR
{
public:
    Point bottomLeft;
    Point topRight;
    bool undefined;
    std::string toString();
    double area();
    double perimeter();
    double distance(MBR input);
    bool isInside(MBR input);
    MBR();
    MBR(int dimension);
    MBR(char* byteArray, long* position);
    MBR(Point _bottomLeft, Point _topRight);
    MBR(const MBR& other);
    ~MBR();
    MBR& operator=(const MBR& other);
    bool operator==(const MBR& other);
    MBR operator+(const MBR& other);
    long getSize();
    void toByteArray(char* byteArray, long* position);
};
