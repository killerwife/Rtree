#pragma once
#include "node.h"
class TestingNode :
    public Node
{
public:
    TestingNode(long _blockSize, MBR input) :Node(_blockSize,input);
    virtual ~TestingNode()override;
};

