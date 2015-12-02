#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include "MBR.h"
#pragma once

class Node
{
protected:
    char isLeaf;
    long size; 
    int count;
public:
    MBR rectangle;
    MBR* arrayOfChildren;
    long* arrayOfPositions;
    Node();
    Node(long _blockSize,MBR input);
    virtual ~Node();
    virtual void readFromFile(long position,FILE* file);
    virtual void saveToFile(long position,FILE* file);    
    std::string toString();
    void makeLeaf();
    int getCount();
    int addChild(Node* _node);
};

