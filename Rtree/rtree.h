#pragma once
#include <string>
#include "node.h"
#include <windows.h>
#include <io.h>
#include "MBR.h"
#include "NodeFactory.h"
class Rtree
{
private:
    std::string fileName;
    long root;
    FILE* tree;
    long blockSize;
    NodeFactory* factory;
public:
    Rtree();
    Rtree(std::string _fileName,long _blockSize,NodeFactory* factory);
    ~Rtree();
    int insertNode(Data* input);
    int deleteNode(Data* input);
    int searchNode(MBR nop);
    void quadraticSplit(Node* temp);
};

