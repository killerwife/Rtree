#include "Node.h"
#pragma once
class NodeFactory
{
public:
    NodeFactory();
    ~NodeFactory();
    virtual Node *getBasicNode() = 0;
    virtual Node *getLeafNode() = 0;
};

