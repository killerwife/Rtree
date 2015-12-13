#pragma once
#include "BasicDataFactory.h"
#include "NodeFactory.h"
class BasicNodeFactory :
    public NodeFactory
{
public:    
    BasicNodeFactory(DataFactory* _factory);
    virtual ~BasicNodeFactory() override;
    virtual Node *getBasicNode(long _blockSize, MBR input, long _parent,long position)override;
    virtual Node *getLeafNode(long _blockSize, MBR input, long _parent, long position)override;
    virtual Node *getNode(FILE* treeFile, long position, long blockSize) override;
};

