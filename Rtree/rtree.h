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
    long nodeSize;
    NodeFactory* factory;
public:
    Rtree();
    Rtree(std::string _fileName,NodeFactory* factory);
    ~Rtree();
    int insertNode(Node* input);
    int deleteNode(Node* input);
    int searchNode(MBR nop);
    void quadraticSplit();
};

