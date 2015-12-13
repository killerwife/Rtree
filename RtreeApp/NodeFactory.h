#include "Node.h"
#include "DataFactory.h"
#pragma once
class NodeFactory
{
public:
    DataFactory* factory;
    NodeFactory();
    virtual ~NodeFactory();
    virtual Node *getBasicNode(long _blockSize, MBR input, long _parent, long position) = 0;
    virtual Node *getLeafNode(long _blockSize, MBR input, long _parent, long position) = 0;
    virtual Node *getNode(FILE* treeFile, long position, long blockSize) = 0;
};

