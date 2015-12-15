#include "MBR.h"

MBR::MBR()
{
    undefined = 1;
}

MBR::MBR(int dimension) : bottomLeft(new double[dimension], dimension), topRight(new double[dimension], dimension)
{
    undefined = 1;
}

MBR::MBR(char* byteArray, long* position)
{
    int dimension;
    undefined = 0;
    memcpy(&dimension, byteArray + *position, sizeof(int));
    (*position) += sizeof(int);
    bottomLeft = Point(byteArray, position, dimension);
    topRight = Point(byteArray, position,dimension);
}

MBR::MBR(Point _bottomLeft, Point _topRight) : bottomLeft(_bottomLeft), topRight(_topRight)
{
    undefined = 0;
}

MBR::MBR(const MBR& other)
{
    undefined = other.undefined;
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
    undefined = other.undefined;
    return *this;
}

std::string MBR::toString(){
    std::string output;
    output += "Bottom Left: ";
    for (int i = 0; i < bottomLeft.dimension; i++)
    {
        output += "x" + std::to_string(i) + ":" + std::to_string(bottomLeft.points[i]) + " ";
    }
    output += "\n";
    output += "Top Right: ";
    for (int i = 0; i < bottomLeft.dimension; i++)
    {
        output += "x" + std::to_string(i) + ":" + std::to_string(topRight.points[i]) + " ";
    }
    output += "\n";
    return output;
}

double MBR::area()
{
    double area = 1;
    for (int i = 0; i < topRight.dimension; i++)
    {
        area *= (topRight.points[i] - bottomLeft.points[i]);
    }
    return area;
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
        if (!((bottomLeft.points[i]<=input.bottomLeft.points[i] && topRight.points[i]>=input.bottomLeft.points[i]) ||
            (bottomLeft.points[i]<=input.topRight.points[i] && topRight.points[i]>=input.topRight.points[i]) ||
            (bottomLeft.points[i]<=input.topRight.points[i] && bottomLeft.points[i]>=input.bottomLeft.points[i]) ||
            (topRight.points[i]<=input.topRight.points[i] && topRight.points[i]>=input.bottomLeft.points[i])))
        {
            return false;
        }
    }
    return true;
}

double MBR::distance(MBR input)
{
    double *distances = new double[topRight.dimension];
    for (int i = 0; i < topRight.dimension; i++)
    {
        if (((bottomLeft.points[i]<input.bottomLeft.points[i] && topRight.points[i]>input.bottomLeft.points[i]) ||
            (bottomLeft.points[i]<input.topRight.points[i] && topRight.points[i]>input.topRight.points[i]) ||
            (bottomLeft.points[i]<input.topRight.points[i] && bottomLeft.points[i]>input.bottomLeft.points[i]) ||
            (topRight.points[i]<input.topRight.points[i] && topRight.points[i]>input.bottomLeft.points[i])))
        {
            distances[i] = 0;
        }
        else
        {
            distances[i] = std::min(input.bottomLeft.points[i] - topRight.points[i], bottomLeft.points[i] - input.topRight.points[i]);
        }
    }
    double distance=0;
    for (int i = 0; i < topRight.dimension; i++)
    {
        distance += distances[i] * distances[i];
    }
    sqrt(distance);
    delete[] distances;
    return distance;
}

bool MBR::operator==(const MBR& other)
{
    return bottomLeft == other.bottomLeft&&topRight == other.topRight;
}

MBR MBR::operator+(const MBR& other)
{
    if (undefined == 1)
    {
        MBR temp(other);    
        return temp;
    }
    else
    {
        Point tempBot = bottomLeft.smaller(other.bottomLeft);
        Point tempTop = topRight.bigger(other.topRight);
        return MBR(tempBot,tempTop);
    }
}

long MBR::getSize()
{
    return bottomLeft.getSize()*2 +sizeof(int);
}

void MBR::toByteArray(char* byteArray, long* position)
{
    memcpy(byteArray+*position,&bottomLeft.dimension,sizeof(int));
    (*position) += sizeof(int);
    bottomLeft.toByteArray(byteArray, position);
    topRight.toByteArray(byteArray, position);
}