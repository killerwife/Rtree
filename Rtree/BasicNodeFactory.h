#pragma once
#include "NodeFactory.h"
class BasicNodeFactory :
    public NodeFactory
{
public:
    BasicNodeFactory();
    ~BasicNodeFactory();
    virtual Node *getBasicNode()override;
    virtual Node *getLeafNode()override;
};

