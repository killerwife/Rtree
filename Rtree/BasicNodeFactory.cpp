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
