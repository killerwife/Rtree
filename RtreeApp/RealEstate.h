#pragma once
#include "Data.h"
#include <float.h>
#include <stdio.h>
#include "time.h"
struct GPS
{
    char width;
    char height;
    double widthPosition;
    double heightPosition;
    GPS()
    {

    };
    GPS(std::string input)
    {
        int i = 0,k=0;
        width = input[i];
        i += 2;
        for (k = i; input[k] != '|'; k++);
        widthPosition = std::stod(input.substr(i,k-i-1).data());
        i = k+1;
        height = input[i];
        i += 2;
        k = input.size();
        heightPosition = std::stod(input.substr(i, k - i).data());
    }
    GPS(char* byteArray, long* position)
    {
        memcpy(&width,byteArray+*position,sizeof(char));
        (*position) += sizeof(char);
        memcpy(&height, byteArray + *position, sizeof(char));
        (*position) += sizeof(char);
        memcpy(&widthPosition, byteArray + *position, sizeof(double));
        (*position) += sizeof(double);
        memcpy(&heightPosition, byteArray + *position, sizeof(double));
        (*position) += sizeof(double);
    };
    std::string to_string()
    {
        std::string one(1,width), two(1,height);
        std::string output = one + "|" + std::to_string(widthPosition) + "|" + two + "|" + std::to_string(heightPosition);
        return output;
    }
    void toByteArray(char* byteArray, long* position)
    {
        memcpy(byteArray + *position, &width, sizeof(char));
        (*position) += sizeof(char);
        memcpy(byteArray + *position, &height, sizeof(char));
        (*position) += sizeof(char);
        memcpy(byteArray + *position, &widthPosition, sizeof(double));
        (*position) += sizeof(double);
        memcpy(byteArray + *position, &heightPosition, sizeof(double));
        (*position) += sizeof(double);
    };
};

class RealEstate :
    public Data
{
public:
    long ID;
    int count;
    std::string description;
    GPS coordinates[60];
    RealEstate();
    RealEstate(long _ID, MBR _rectangle);
    RealEstate(long _ID, std::string name, std::string _description, GPS _coordinates[60],int _count);
    RealEstate(char* byteArray, long* position);
    ~RealEstate();
    void regenerate();
    virtual long getSize()override;
    virtual void toByteArray(char* byteArray, long* position)override;
    virtual bool operator==(Data* other)override;
    virtual std::string to_string()override;
};

unsigned long _LongRand();
