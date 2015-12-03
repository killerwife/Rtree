#include "BasicNodeFactory.h"


BasicNodeFactory::BasicNodeFactory()
{
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

Node* BasicNodeFactory::getNode(char* byteArray, int* position)
{
    DataFactory* factory = new BasicDataFactory();
    Node* temp = new Node(byteArray,position,factory);
    
    return temp;
}
