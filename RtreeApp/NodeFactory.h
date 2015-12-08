#include "Node.h"
#include "DataFactory.h"
#pragma once
class NodeFactory
{
public:
    NodeFactory();
    ~NodeFactory();
    virtual Node *getBasicNode() = 0;
    virtual Node *getLeafNode() = 0;
    virtual Node *getNode(FILE* treeFile, long position, long blockSize) = 0;
};
