#include "rtree.h"


Rtree::Rtree()
{
    fileName = "tempOutput.txt";
    tree = fopen(fileName.data(), "w+");
    root = -1;
}

Rtree::Rtree(std::string _fileName, NodeFactory* _factory)
{
    fileName = _fileName;
    tree = fopen(fileName.data(), "w+");
    factory = _factory;
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
    delete factory;
}

int Rtree::insertNode(Node* input)
{
    Node* temp;
    if (root == -1)
    {
        temp = factory->getLeafNode();
        temp->arrayOfChildren[]
    }
    else
    {
        temp = factory->getBasicNode();
        temp->readFromFile(root,tree);
    }
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
