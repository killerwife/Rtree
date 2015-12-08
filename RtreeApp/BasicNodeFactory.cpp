#include "BasicNodeFactory.h"


BasicNodeFactory::BasicNodeFactory(DataFactory* _factory)
{
    factory = _factory;
}


BasicNodeFactory::~BasicNodeFactory()
{
}

Node* BasicNodeFactory::getBasicNode()
{
    return new Node();
}
Node* BasicNodeFactory::getLeafNode()
{
    Node* temp = new Node();
    temp->makeLeaf();
    return temp;
}

Node* BasicNodeFactory::getNode(FILE* treeFile, long position,long blockSize)
{
    char* byteArray = new char[blockSize];
    long pos = position;
    fread(byteArray,blockSize,1,treeFile);
    Node* temp = new Node(blockSize,byteArray,&pos,factory);
    delete[]byteArray;
    return temp;
}
