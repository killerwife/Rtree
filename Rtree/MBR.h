#include "Point.h"
#include <string>
#include <math.h>
#pragma once
class MBR
{
public:
    Point bottomLeft;
    Point topRight;
    std::string toString();
    double perimeter();
    long distance(MBR input);
    bool isInside(MBR input);
    MBR();
    MBR(char* byteArray, long* position);
    MBR(Point _topLeft,Point _bottomRight);
    MBR(const MBR& other);
    ~MBR();
    MBR& operator=(const MBR& other);
    bool operator==(const MBR& other);
    MBR operator+(const MBR& other);
    long getSize();
    void toByteArray(char* byteArray, long* position);
};
