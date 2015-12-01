#include "rtree.h"


Rtree::Rtree()
{
    fileName = "tempOutput.txt";
    treeFile = "tempTree.txt";
    tree = fopen(treeFile.data(),"w+");
    data = fopen(fileName.data(), "w+");
    root = -1;
}

Rtree::Rtree(std::string _fileName, std::string _treeFile)
{
    fileName = _fileName;
    treeFile = _treeFile;
    tree = fopen(treeFile.data(), "w+");
    data = fopen(fileName.data(), "w+");
    long checkPos = fseek(tree,0,SEEK_END);
    if (checkPos == 0)
    {
        root = -1;
    }
    else
    {
        root = 0;
    }
}

Rtree::~Rtree()
{
    fclose(tree);
}

int Rtree::insertNode(Node* input)
{
    return 1;
}
int Rtree::deleteNode(Node* input)
{
    return 1;
}
int Rtree::searchNode(MBR nop)
{
    return 1;
}
