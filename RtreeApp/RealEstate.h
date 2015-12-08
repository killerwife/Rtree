#pragma once
#include "Data.h"
#include <float.h>
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
        widthPosition = std::stod(input.substr(i,k-i-1));
        i = k+1;
        height = input[i];
        i += 2;
        for (k = i; input[k] != '\n'; k++);
        heightPosition = std::stod(input.substr(i, k - i - 1));
    }
    std::string to_string()
    {
        std::string output = width + "|" + std::to_string(widthPosition) + "|" + height + "|" + std::to_string(heightPosition);
        return output;
    }
};

class RealEstate :
    public Data
{
public:
    long ID;
    std::string description;
    GPS coordinates[60];
    RealEstate();
    RealEstate(long _ID, MBR _rectangle);
    RealEstate(long _ID, std::string name, std::string _description, GPS _coordinates[60]);
    RealEstate(char* byteArray, long* position);
    ~RealEstate();
    void regenerate();
    virtual long getSize()override;
    virtual void toByteArray(char* byteArray, long* position)override;
    virtual bool operator==(Data* other)override;
    virtual std::string to_string()override;
};

unsigned long _LongRand();
