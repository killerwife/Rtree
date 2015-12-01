#pragma once
#include <string>
#include "node.h"
#include <windows.h>
#include <io.h>
#include "MBR.h"
class Rtree
{
private:
    std::string fileName;
    std::string treeFile;
    long root;
    FILE* tree;
    FILE* data;
    long nodeSize;
public:
    Rtree();
    Rtree(std::string _fileName, std::string _treeFile);
    ~Rtree();
    int insertNode(Node* input);
    int deleteNode(Node* input);
    int searchNode(MBR nop);
};

