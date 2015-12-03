#pragma once
#include "BasicDataFactory.h"
#include "NodeFactory.h"
class BasicNodeFactory :
    public NodeFactory
{
public:
    BasicNodeFactory();
    ~BasicNodeFactory();
    virtual Node *getBasicNode()override;
    virtual Node *getLeafNode()override;
    virtual Node *getNode(char* byteArray, int* position)override;
};

