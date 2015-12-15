#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include "DataFactory.h"
#pragma once
class Node
{
protected:    
    long size;
    long blockSize;
    long totalSize;
public:
    long location;
    long count;
    char isLeaf;
    long parent;    
    MBR rectangle;
    MBR* arrayOfChildren;
    long* arrayOfPositions;
    Data** data;
    DataFactory* factory;
    Node();
    Node(long _blockSize, MBR input, long _parent, DataFactory* _factory, long position);
    Node(long _blockSize, char* byteArray, long* position, DataFactory* _factory,long _location);
    virtual ~Node();
    virtual void readFromFile(long _position, FILE* file);
    virtual void saveToFile(FILE* file);
    virtual std::string toString();
    void makeLeaf();
    int getCount();
    int addChild(MBR box, long pos);
    int removeChild(MBR box, long pos);
    int addChild(Data* _node);
    int removeChild(Data* _node);
    int editChild(MBR box,long pos);
    int editChild(MBR box, Data* _data);
    int getSize();
    long extractLastChild();
    Data* Node::extractLastChildLeaf();
    void recalculate();
};

