#include "node.h"


Node::Node()
{

}

Node::Node(long _blockSize, MBR input, long _parent, DataFactory* _factory)
{
    blockSize = _blockSize;
    size = (_blockSize - sizeof(long) - sizeof(char)) / (sizeof(long) + input.getSize());
    parent = _parent;
    factory = _factory;
    rectangle = input;
    isLeaf = 0;
    count = 0;
    arrayOfChildren = new MBR[size + 1];
    arrayOfPositions = new long[size + 1];
    memset(arrayOfPositions, -1, sizeof(long)*size);
}

Node::Node(long _blockSize, char* byteArray, long* position, DataFactory* _factory)
{
    isLeaf = byteArray[0];
    *position++;
    memcpy(&parent, byteArray + *position, sizeof(long));
    *position += 4;
    rectangle = MBR(byteArray, position);
    if (isLeaf == 0)
    {        
        size = (_blockSize - sizeof(long) - sizeof(char)) / (sizeof(long) + rectangle.getSize());
        arrayOfChildren = new MBR[size + 1];
        for (int i = 0; i < size; i++)
        {
            arrayOfChildren[i]=MBR(byteArray,position);
        }
        memcpy(arrayOfPositions, byteArray + *position, sizeof(double)*size);
    }
    else
    {
        size = (_blockSize - sizeof(long) - sizeof(char)) / (_factory->getDataSize());
        for (int i = 0; i < size; i++)
        {
            data[i] = _factory->getData(byteArray, position);
        }
    }
}

Node::~Node()
{
    delete[] arrayOfChildren;
    delete[] arrayOfPositions;
    delete[] data;
}

void Node::readFromFile(long position, FILE* file)
{
    if (isLeaf == 0)
    {
        delete[] arrayOfChildren;
        delete[] arrayOfPositions;
    }
    else
    {
        delete[]data;
    }
    fseek(file, position, SEEK_SET);
    long pos=position;
    char* byteArray = new char[blockSize];
    fread(byteArray, blockSize, 1, file);
    isLeaf = byteArray[0];
    pos++;
    memcpy(&parent, byteArray + pos, sizeof(long));
    pos += 4;
    rectangle = MBR(byteArray, &pos);
    if (isLeaf == 0)
    {
        size = (blockSize - sizeof(long) - sizeof(char)) / (sizeof(long) + rectangle.getSize());
        arrayOfChildren = new MBR[size + 1];
        arrayOfPositions = new long[size + 1];
        for (int i = 0; i < size; i++)
        {
            arrayOfChildren[i] = MBR(byteArray, &pos);
        }
        memcpy(arrayOfPositions, byteArray + pos, sizeof(double)*size);
    }
    else
    {
        size = (blockSize - sizeof(long) - sizeof(char)) / (factory->getDataSize());
        for (int i = 0; i < size; i++)
        {
            data[i] = factory->getData(byteArray, &pos);
        }
    }
}

void Node::saveToFile(long position, FILE* file)
{
    fseek(file, position, SEEK_SET);
    char* byteArray = new char[blockSize];
    byteArray[0] = isLeaf;
    memcpy(byteArray + sizeof(char), &parent, sizeof(long));
    long startIndex = sizeof(char) + sizeof(long);
    if (isLeaf == 0)
    {
        for (int i = 0; i < size; i++)
        {
            arrayOfChildren->toByteArray(byteArray,&startIndex);
        }
        memcpy(byteArray + startIndex, arrayOfPositions, sizeof(long)*size);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] == nullptr)
            {
                count++;
                continue;
            }
            data[i]->toByteArray(byteArray, &startIndex);
            startIndex += data[i]->getSize();
        }
    }
    fwrite(byteArray, 1, blockSize, file);
    delete[]byteArray;
}

std::string Node::toString()
{
    std::string output;
    output += "Non-Leaf NOP:" + rectangle.toString();
    for (int i = 0; i < size; i++)
    {
        if (arrayOfPositions[i] != -1)
        {
            output += "#" + std::to_string(i) + " Position: " + std::to_string(arrayOfPositions[i]) + " NOP:" + arrayOfChildren[i].toString();
        }
        else
        {
            break;
        }
    }
    return output;
}

void Node::makeLeaf()
{
    isLeaf = 1;
    data = new Data*[size + 1];
    memset(data, 0, sizeof(Data)*size + 1);
    totalSize = 0;
}

int Node::getCount()
{
    return count;
}

int Node::addChild(Data* _node)
{
    data[count] = _node;
    totalSize += _node->getSize();
    count++;
    if (count > size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Node::removeChild(Data* _node)
{
    for (int i = 0; i < count; i++)
    {
        if (*_node == data[i])
        {
            totalSize -= data[i]->getSize();
            delete data[i];
            data[i] = nullptr;
            return 0;
        }
    }
    return 1;
}