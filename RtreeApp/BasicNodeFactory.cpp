#include "BasicNodeFactory.h"


BasicNodeFactory::BasicNodeFactory(DataFactory* _factory)
{
    factory = _factory;
}


BasicNodeFactory::~BasicNodeFactory()
{
    delete factory;
}

Node* BasicNodeFactory::getBasicNode(long _blockSize, MBR input, long _parent, long position)
{
    return new Node(_blockSize,input,_parent,factory,position);
}
Node* BasicNodeFactory::getLeafNode(long _blockSize, MBR input, long _parent, long position)
{
    Node* temp = new Node(_blockSize, input, _parent, factory, position);
    temp->makeLeaf();
    return temp;
}

Node* BasicNodeFactory::getNode(FILE* treeFile, long position,long blockSize)
{
    char* byteArray = new char[blockSize];
    fseek(treeFile,position,SEEK_SET);
    long pos = 0;
    fread(byteArray,blockSize,1,treeFile);
    Node* temp = new Node(blockSize, byteArray, &pos, factory, position);
    delete[]byteArray;
    return temp;
}
