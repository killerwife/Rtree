#include "node.h"


Node::Node()
{

}

Node::Node(long _blockSize, MBR input, long _parent, DataFactory* _factory, long position)
{
    blockSize = _blockSize;
    location = position;
    parent = _parent;
    factory = _factory;
    rectangle = input;
    totalSize = 0;
    isLeaf = 0;
    count = 0;
    size = (blockSize - sizeof(long) * 2 - sizeof(char) - rectangle.getSize()) / (sizeof(long) + rectangle.getSize());
    arrayOfChildren = new MBR[size + 1];
    arrayOfPositions = new long[size + 1];
}

Node::Node(long _blockSize, char* byteArray, long* position, DataFactory* _factory, long _location)
{
    blockSize = _blockSize;
    factory = _factory;
    location = _location;
    isLeaf = byteArray[0];
    (*position)++;
    memcpy(&parent, byteArray + *position, sizeof(long));
    (*position) += sizeof(long);
    memcpy(&count, byteArray + *position, sizeof(long));
    (*position) += sizeof(long);
    rectangle = MBR(byteArray, position);
    if (isLeaf == 0)
    {
        size = (blockSize - sizeof(long) * 2 - sizeof(char) - rectangle.getSize()) / (sizeof(long) + rectangle.getSize());
        arrayOfChildren = new MBR[size + 1];
        arrayOfPositions = new long[size + 1];
        for (int i = 0; i < count; i++)
        {
            arrayOfChildren[i] = MBR(byteArray, position);
        }
        memcpy(arrayOfPositions, byteArray + *position, sizeof(long)*size);
        (*position) += sizeof(double)*size;
    }
    else
    {
        size = (_blockSize - sizeof(long) * 2 - sizeof(char) - rectangle.getSize()) / (_factory->getDataSize());
        data = new Data*[size + 1];
        for (int i = 0; i < count; i++)
        {
            data[i] = _factory->getData(byteArray, position);
        }
    }
}

Node::~Node()
{
    if (isLeaf == 0)
    {
        delete[] arrayOfChildren;
        delete[] arrayOfPositions;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            delete data[i];
        }
        delete[] data;
    }
}

void Node::readFromFile(long _position, FILE* file)
{
    if (isLeaf == 0)
    {
        delete[] arrayOfChildren;
        delete[] arrayOfPositions;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            delete data[i];
        }
        delete[]data;
    }
    fseek(file, _position, SEEK_SET);
    location = _position;
    long pos = 0;
    long* position = &pos;
    totalSize = 0;
    char* byteArray = new char[blockSize];
    fread(byteArray, blockSize, 1, file);
    isLeaf = byteArray[0];
    (*position)++;
    memcpy(&parent, byteArray + *position, sizeof(long));
    (*position) += sizeof(long);
    memcpy(&count, byteArray + *position, sizeof(long));
    (*position) += sizeof(long);
    rectangle = MBR(byteArray, position);
    if (isLeaf == 0)
    {
        size = (blockSize - sizeof(long) * 2 - sizeof(char) - rectangle.getSize()) / (sizeof(long) + rectangle.getSize());
        arrayOfChildren = new MBR[size + 1];
        arrayOfPositions = new long[size + 1];
        for (int i = 0; i < count; i++)
        {
            arrayOfChildren[i] = MBR(byteArray, position);
        }
        memcpy(arrayOfPositions, byteArray + *position, sizeof(long)*size);
        (*position) += sizeof(double)*size;
    }
    else
    {
        size = (blockSize - sizeof(long) * 2 - sizeof(char) - rectangle.getSize()) / (factory->getDataSize());
        data = new Data*[size + 1];
        for (int i = 0; i < count; i++)
        {
            data[i] = factory->getData(byteArray, position);
        }
    }
    delete[] byteArray;
}

void Node::saveToFile(FILE* file)
{
    fseek(file, location, SEEK_SET);
    char* byteArray = new char[blockSize];
    byteArray[0] = isLeaf;
    memcpy(byteArray + sizeof(char), &parent, sizeof(long));
    long startIndex = sizeof(char) + sizeof(long);
    long* indexPointer = &startIndex;
    memcpy(byteArray + startIndex, &count, sizeof(long));
    startIndex += sizeof(long);
    rectangle.toByteArray(byteArray, indexPointer);
    if (isLeaf == 0)
    {
        for (int i = 0; i < count; i++)
        {
            arrayOfChildren[i].toByteArray(byteArray, &startIndex);
        }
        memcpy(byteArray + startIndex, arrayOfPositions, sizeof(long)*size);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            data[i]->toByteArray(byteArray, indexPointer);
        }
    }
    fwrite(byteArray, 1, blockSize, file);
    delete[]byteArray;
    fflush(file);
}

std::string Node::toString()
{
    std::string output;
    output += "NOP:" + rectangle.toString();
    if (isLeaf == 1)
    {
        for (int k = 0; k < count; k++)
        {
            output += data[k]->to_string() + "\n";
        }
    }
    else
    {
        for (int k = 0; k < count; k++)
        {
            output += arrayOfChildren[k].toString();
            output += "Position: " + std::to_string(arrayOfPositions[k]) + "\n";
        }
    }
    return output;
}

void Node::makeLeaf()
{
    isLeaf = 1;
    delete[]arrayOfChildren;
    delete[]arrayOfPositions;
    size = (blockSize - sizeof(long) * 2 - sizeof(char) - rectangle.getSize()) / (factory->getDataSize());
    data = new Data*[size + 1];
    totalSize = 0;
    count = 0;
}

int Node::getCount()
{
    return count;
}

int Node::addChild(MBR box, long pos)
{
    arrayOfPositions[count] = pos;
    arrayOfChildren[count] = box;
    rectangle = rectangle + box;
    count++;
    if (count >= size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Node::addChild(Data* _node)
{
    data[count] = _node;
    totalSize += _node->getSize();
    rectangle = rectangle + _node->rectangle;
    count++;
    if (count >= size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Node::removeChild(MBR box, long pos)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (arrayOfChildren[i] == box&&arrayOfPositions[i] == pos)
        {
            arrayOfChildren[i] = arrayOfChildren[count - 1];
            arrayOfPositions[i] = arrayOfPositions[count - 1];
            count--;
            if (count > 0)
            {
                recalculate();
            }
            if (count < sqrt(size))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 2;
}

int Node::removeChild(Data* _node)
{
    for (int i = 0; i < count; i++)
    {
        if (*_node == data[i])
        {
            totalSize -= data[i]->getSize();
            delete data[i];
            data[i] = data[count - 1];
            data[count - 1] = nullptr;
            count--;
            if (count > 0)
            {
                recalculate();
            }
            if (count < sqrt(size))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 2;
}

int Node::editChild(MBR box, long pos)
{
    for (int i = 0; i < count; i++)
    {
        if (arrayOfPositions[i] == pos)
        {
            arrayOfChildren[i] = box;
            recalculate();
            return 0;
        }
    }
    return 1;
}

int Node::editChild(MBR box, Data* _data)
{
    for (int i = 0; i < count; i++)
    {
        if (data[i]->rectangle == box)
        {
            delete data[i];
            data[i] = _data;
            recalculate();
            return 0;
        }
    }
    return 1;
}

long Node::extractLastChild()
{
    long temp = arrayOfPositions[count - 1];
    count--;
    if (count > 0)
    {
        recalculate();
    }
    return temp;
}

Data* Node::extractLastChildLeaf()
{
    Data* temp = data[count - 1];
    count--;
    if (count > 0)
    {
        recalculate();
    }
    return temp;
}

void Node::recalculate()
{
    MBR temp;
    if (isLeaf == 1)
    {
        for (int i = 0; i < count; i++)
        {
            temp = temp + data[i]->rectangle;
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            temp = temp + arrayOfChildren[i];
        }
    }
    rectangle = temp;
}

int Node::getSize()
{
    return size;
}