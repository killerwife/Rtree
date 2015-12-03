#include "MBR.h"


MBR::MBR()
{

}

MBR::MBR(char* byteArray, int* position)
{
    topLeft = Point(byteArray, position);
    bottomRight = Point(byteArray, position);
}

MBR::MBR(Point _topLeft, Point _bottomRight)
{
    topLeft = _topLeft;
    bottomRight = _bottomRight;
}

MBR::MBR(const MBR& other)
{
    topLeft = other.topLeft;
    bottomRight = other.bottomRight;
}

MBR::~MBR()
{
}

MBR& MBR::operator=(const MBR& other)
{
    topLeft = other.topLeft;
    bottomRight = other.bottomRight;
    return *this;
}

std::string MBR::toString(){
    std::string output;
    output += "Top Left: ";
    for (int i = 0; i < topLeft.dimension; i++)
    {
        output += "x" + std::to_string(i) + ":" + std::to_string(topLeft.points[i]) + " ";
    }
    output += "\n";
    output += "Bottom Right: ";
    for (int i = 0; i < topLeft.dimension; i++)
    {
        output += "x" + std::to_string(i) + ":" + std::to_string(bottomRight.points[i]) + " ";
    }
    output += "\n";
    return output;
}
long MBR::perimeter()
{
    long output = 0;
    long power = pow(2,topLeft.dimension-1);
    for (int i = 0; i < topLeft.dimension;i++)
    {
        output += abs(topLeft.points[i] - bottomRight.points[i]);
    }
    return output;
}
bool MBR::isInside(MBR input)
{
    for (int i = 0; i < topLeft.dimension; i++)
    {
        if (!((topLeft.points[i]<input.topLeft.points[i] && bottomRight.points[i]>input.topLeft.points[i]) ||
            (topLeft.points[i]<input.bottomRight.points[i] && bottomRight.points[i]>input.bottomRight.points[i]) ||
            (topLeft.points[i]<input.bottomRight.points[i] && topLeft.points[i]>input.topLeft.points[i]) ||
            (bottomRight.points[i]<input.bottomRight.points[i] && bottomRight.points[i]>input.topLeft.points[i])))
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
    return topLeft == other.topLeft&&bottomRight == other.bottomRight;
}

long MBR::getSize()
{
    return topLeft.getSize() * 2;
}

void MBR::toByteArray(char* byteArray, int* position)
{
    topLeft.toByteArray(byteArray, position);
    bottomRight.toByteArray(byteArray, position);
}