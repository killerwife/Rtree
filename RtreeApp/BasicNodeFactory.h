#pragma once
#include "BasicDataFactory.h"
#include "NodeFactory.h"
class BasicNodeFactory :
    public NodeFactory
{
public:
    DataFactory* factory;
    BasicNodeFactory(DataFactory* _factory);
    ~BasicNodeFactory();
    virtual Node *getBasicNode()override;
    virtual Node *getLeafNode()override;
    virtual Node *getNode(FILE* treeFile, long position, long blockSize) override;
};

