#include "rtree.h"


Rtree::Rtree()
{
    fileName = "tempOutput.txt";
    tree = fopen(fileName.data(), "w+");
    root = -1;
}

Rtree::Rtree(std::string _fileName,long _blockSize, NodeFactory* _factory)
{
    fileName = _fileName;
    blockSize = _blockSize;
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

int Rtree::insertNode(Data* input)
{
    Node* temp;
    if (root == -1)
    {
        temp = factory->getLeafNode();
        int result = temp->addChild(input);
        if (result > 0)
        {
            quadraticSplit(temp);
        }
        return 0;
    }
    else
    {
        temp = factory->getNode(tree,root,blockSize);
        while (temp->isLeaf != 1)
        {
            MBR area;
            int index;
            double min;
            for (int i = 0; i < temp->getCount(); i++)
            {
                area = temp->arrayOfChildren[i] + input->rectangle;
                if (area.perimeter() < min)
                {
                    index = i;
                    min = area.perimeter();
                }
            }
            temp->readFromFile(temp->arrayOfPositions[index],tree);            
        }
        int result=temp->addChild(input);
        if (result > 0)
        {
            quadraticSplit(temp);
        }
        return 0;
    }
    return 1;
}
int Rtree::deleteNode(Data* input)
{
    return 1;
}
int Rtree::searchNode(MBR nop)
{
    return 1;
}
