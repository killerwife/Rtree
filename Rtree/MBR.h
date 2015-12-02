#include "Point.h"
#include <string>
#include <math.h>
#pragma once
class MBR
{
public:
    Point topLeft;
    Point bottomRight;
    std::string toString();
    long perimeter();
    long distance(MBR input);
    bool isInside(MBR input);
    MBR();
    MBR(Point _topLeft,Point _bottomRight);
    MBR(const MBR& other);
    ~MBR();
    MBR& operator=(const MBR& other);
};
