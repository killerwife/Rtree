#include "RealEstate.h"


unsigned long _LongRand()
{

    unsigned char MyBytes[4];
    unsigned long MyNumber = 0;
    unsigned char * ptr = (unsigned char *)&MyNumber;

    MyBytes[0] = rand() % 256; //0-255
    MyBytes[1] = rand() % 256; //256 - 65535
    MyBytes[2] = rand() % 256; //65535 -
    MyBytes[3] = rand() % 256; //16777216

    memcpy(ptr + 0, &MyBytes[0], 1);
    memcpy(ptr + 1, &MyBytes[1], 1);
    memcpy(ptr + 2, &MyBytes[2], 1);
    memcpy(ptr + 3, &MyBytes[3], 1);

    return(MyNumber);
}

RealEstate::RealEstate()
{
    srand(time(NULL));
    ID = _LongRand();
    char nameTemp[5];
    nameTemp[0] = ((char)(rand() % 26) + 'A');
    nameTemp[1] = ((char)(rand() % 26) + 'A');
    nameTemp[2] = ((char)(rand() % 26) + 'A');
    nameTemp[3] = ((char)(rand() % 26) + 'A');
    nameTemp[4] = '\0';
    name = nameTemp;
    long originX = _LongRand();
    long originY = _LongRand();
    for (int i = 0; i < 4; i++)
    {
        coordinates[i].heightPosition = originX + abs(rand()) % 50;
        coordinates[i].widthPosition = originY + abs(rand()) % 50;
        coordinates[i].height = abs(rand() % 2) == 0 ? 'S' : 'J';
        coordinates[i].width = abs(rand() % 2) == 0 ? 'V' : 'Z';
    }
    double bottom = DBL_MAX, left = DBL_MAX, top = DBL_MIN, right = DBL_MIN;
    for (int i = 0; i < 4; i++)
    {
        if (coordinates[i].height > top)
        {
            top = coordinates[i].height;
        }
        if (coordinates[i].height < bottom)
        {
            bottom = coordinates[i].height;
        }
        if (coordinates[i].width > right)
        {
            right = coordinates[i].width;
        }
        if (coordinates[i].width < left)
        {
            left = coordinates[i].width;
        }
    }
    double* first = new double[2], *second = new double[2];
    first[0] = left;
    first[1] = bottom;
    second[0] = right;
    second[1] = top;
    rectangle = MBR(Point(first, 2), Point(second, 2));
}

RealEstate::RealEstate(long _ID, MBR _rectangle)
{
    ID = _ID;
    rectangle = rectangle;
}

RealEstate::RealEstate(long _ID, std::string _name,std::string _description, GPS _coordinates[60])
{
    ID = _ID;
    name = _name;
    description = _description;
    for (int i = 0; i < 60; i++)
    {
        coordinates[i].height = _coordinates[i].height;
        coordinates[i].width = _coordinates[i].width;
        coordinates[i].heightPosition = _coordinates[i].heightPosition;
        coordinates[i].widthPosition = _coordinates[i].widthPosition;
    }
    double bottom = DBL_MAX, left = DBL_MAX, top = DBL_MIN, right = DBL_MIN;
    for (int i = 0; i < 60; i++)
    {
        if (coordinates[i].height > top)
        {
            top = coordinates[i].height;
        }
        if (coordinates[i].height < bottom)
        {
            bottom = coordinates[i].height;
        }
        if (coordinates[i].width > right)
        {
            right = coordinates[i].width;
        }
        if (coordinates[i].width < left)
        {
            left = coordinates[i].width;
        }
    }
    double* first = new double[2], *second = new double[2];
    first[0] = left;
    first[1] = bottom;
    second[0] = right;
    second[1] = top;
    rectangle = MBR(Point(first,2),Point(second,2));
}

RealEstate::RealEstate(char* byteArray, long* position)
{
    rectangle = MBR(byteArray,position);
    char _name[20];
    char _description[60];
    memcpy(&ID, byteArray + *position, sizeof(long));
    *position += sizeof(long);
    memcpy(_name,byteArray+*position,sizeof(char)*20);
    *position += sizeof(char) * 20;
    memcpy(_description, byteArray + *position, sizeof(char) * 60);
    *position += sizeof(char) * 60;
    for (int i = 0; i < 60; i++)
    {
        memcpy(&coordinates[i], byteArray + *position, sizeof(GPS));
        *position += sizeof(GPS);
    }
}

RealEstate::~RealEstate()
{

}

void RealEstate::regenerate()
{
    ID = _LongRand();
}

long RealEstate::getSize()
{
    return sizeof(long) + sizeof(char) * 80 + sizeof(GPS) * 60+sizeof(double)*2+sizeof(int);
}

void RealEstate::toByteArray(char* byteArray, long* position)
{
    rectangle.toByteArray(byteArray, position);
    memcpy(byteArray + *position,&ID, sizeof(long));
    *position += sizeof(long);
    int i;
    for (i = 0; i < name.size(); i++)
    {
        byteArray[*position] = name[i];
        *position++;
    }
    for (; i < 20; i++)
    {
        byteArray[*position] = '\0';
        *position++;
    }
    for (i = 0; i < description.size(); i++)
    {
        byteArray[*position] = description[i];
        *position++;
    }
    for (; i < 60; i++)
    {
        byteArray[*position] = '\0';
        *position++;
    }
    for (i = 0; i < 60; i++)
    {
        memcpy(byteArray + *position, &coordinates[i], sizeof(GPS));
        *position += sizeof(GPS);
    }
}

bool RealEstate::operator==(Data* other)
{
    if (rectangle == other->rectangle)
    {
        return ID == ((RealEstate*)other)->ID;
    }
    else
    {
        return false;
    }
}

std::string RealEstate::to_string()
{
    std::string output = "";
    return output;
}
