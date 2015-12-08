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
};

class RealEstate :
    public Data
{
public:
    long ID;
    std::string description;
    GPS coordinates[60];
    RealEstate();
    RealEstate(long _ID, std::string name, std::string _description, GPS _coordinates[60]);
    RealEstate(char* byteArray,long* position);
    ~RealEstate();
    virtual long getSize()override;
    virtual void toByteArray(char* byteArray, long* position)override;
    virtual bool operator==(Data* other)override;
    virtual std::string to_string()override;
};

unsigned long _LongRand();
