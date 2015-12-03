#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include "MBR.h"
#include "DataFactory.h"
#pragma once

class Node
{
protected:
    char isLeaf;
    long size;
    int count;
    long blockSize;
    long totalSize;
public:
    long parent;    
    MBR rectangle;
    MBR* arrayOfChildren;
    long* arrayOfPositions;
    Data** data;
    DataFactory* factory;
    Node();
    Node(long _blockSize, MBR input, long _parent, DataFactory* _factory);
    Node(char* byteArray, int* position, DataFactory* _factory);
    virtual ~Node();
    virtual void readFromFile(long position, FILE* file);
    virtual void saveToFile(long position, FILE* file);
    virtual std::string toString();
    void makeLeaf();
    int getCount();
    int addChild(Data* _node);
    int removeChild(Data* _node);
};

