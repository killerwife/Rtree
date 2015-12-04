#include "MBR.h"


MBR::MBR()
{

}

MBR::MBR(char* byteArray, long* position)
{
    int dimension;
    memcpy(&dimension, byteArray + *position, sizeof(int));
    *position += sizeof(int);
    bottomLeft = Point(byteArray, position, dimension);
    topRight = Point(byteArray, position,dimension);
}

MBR::MBR(Point _bottomLeft, Point _topRight)
{
    bottomLeft = _bottomLeft;
    topRight = _topRight;
}

MBR::MBR(const MBR& other)
{
    bottomLeft = other.bottomLeft;
    topRight = other.topRight;
}

MBR::~MBR()
{
}

MBR& MBR::operator=(const MBR& other)
{
    bottomLeft = other.bottomLeft;
    topRight = other.topRight;
    return *this;
}

std::string MBR::toString(){
    std::string output;
    output += "Top Left: ";
    for (int i = 0; i < bottomLeft.dimension; i++)
    {
        output += "x" + std::to_string(i) + ":" + std::to_string(bottomLeft.points[i]) + " ";
    }
    output += "\n";
    output += "Bottom Right: ";
    for (int i = 0; i < bottomLeft.dimension; i++)
    {
        output += "x" + std::to_string(i) + ":" + std::to_string(topRight.points[i]) + " ";
    }
    output += "\n";
    return output;
}
double MBR::perimeter()
{
    double output = 0;
    double power = pow(2,topRight.dimension);
    for (int i = 0; i < bottomLeft.dimension; i++)
    {
        output += (topRight.points[i]-bottomLeft.points[i])*power;
    }
    return output;
}
bool MBR::isInside(MBR input)
{
    for (int i = 0; i < bottomLeft.dimension; i++)
    {
        if (!((bottomLeft.points[i]<input.bottomLeft.points[i] && topRight.points[i]>input.bottomLeft.points[i]) ||
            (bottomLeft.points[i]<input.topRight.points[i] && topRight.points[i]>input.topRight.points[i]) ||
            (bottomLeft.points[i]<input.topRight.points[i] && bottomLeft.points[i]>input.bottomLeft.points[i]) ||
            (topRight.points[i]<input.topRight.points[i] && topRight.points[i]>input.bottomLeft.points[i])))
        {
            return false;
        }
    }
    return true;
}

long MBR::distance(MBR input)
{
    
}

bool MBR::operator==(const MBR& other)
{
    return bottomLeft == other.bottomLeft&&topRight == other.topRight;
}

MBR MBR::operator+(const MBR& other)
{
    MBR temp;
    Point tempBot = bottomLeft.smaller(other.bottomLeft);
    Point tempTop = topRight.smaller(other.topRight);
    return temp;
}

long MBR::getSize()
{
    return bottomLeft.getSize()*2 +sizeof(int);
}

void MBR::toByteArray(char* byteArray, long* position)
{
    memcpy(byteArray+*position,&bottomLeft.dimension,sizeof(int));
    *position += sizeof(int);
    bottomLeft.toByteArray(byteArray, position);
    topRight.toByteArray(byteArray, position);
}