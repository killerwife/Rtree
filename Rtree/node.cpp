#include "node.h"


Node::Node()
{

}

Node::Node(long _blockSize, MBR input,long _parent,DataFactory* _factory)
{
    blockSize = _blockSize;
    size = (_blockSize -sizeof(long) -sizeof(char))/(sizeof(long)+input.getSize());
    parent = _parent;
    factory = _factory;
    rectangle.topLeft = input.topLeft;
    rectangle.bottomRight = input.bottomRight;
    isLeaf = 0;
    count = 0;
    arrayOfChildren = new MBR[size+1];
    arrayOfPositions = new long[size + 1];
    memset(arrayOfPositions, -1, sizeof(long)*size);
}

Node(long _blockSize,char* byteArray, int* position, DataFactory* _factory)
{
    isLeaf = byteArray[0];
    *position++;
    memcpy(&parent, byteArray + *position, sizeof(long));
    *position += 4;
    if (isLeaf == 0)
    {
        size = (_blockSize - sizeof(long) - sizeof(char)) / (sizeof(long) + _factory.getMBRSize());
        memcpy(arrayOfPositions, byteArray + *position, sizeof(double)*size);
    }
}

Node::~Node()
{
    delete[] arrayOfChildren;
    delete[] arrayOfPositions;
}

void Node::readFromFile(long position, FILE* file)
{
    fseek(file, position, SEEK_SET);
    int pointSize = rectangle.topLeft.dimension*sizeof(double);
    int MBRSize = 2 * pointSize;
    int inputSize = sizeof(char) + sizeof(long)*size + MBRSize*size;
    char* byteArray = new char[inputSize];
    fread(byteArray, 1, inputSize, file);
    isLeaf = byteArray[0];
    memcpy(&parent, byteArray + sizeof(char), sizeof(long));
    int startIndex = sizeof(char)+sizeof(long);
    for (int i = 0; i < size; i++)
    {
        memcpy(arrayOfChildren[i].topLeft.points,byteArray+startIndex,pointSize);
        memcpy(arrayOfChildren[i].bottomRight.points, byteArray + startIndex + pointSize, pointSize);
        startIndex += MBRSize;
    }
    
    delete[]byteArray;
}
void Node::saveToFile(long position, FILE* file)
{
    fseek(file, position, SEEK_SET);
    int pointSize = rectangle.topLeft.dimension*sizeof(double);
    int MBRSize = 2 * pointSize;
    int outputSize = sizeof(char) + sizeof(long)*size + MBRSize*size;
    char* byteArray = new char[blockSize];
    byteArray[0] = isLeaf;   
    memcpy(byteArray + sizeof(char), &parent, sizeof(long));
    int startIndex = sizeof(char) + sizeof(long);
    for (int i = 0; i < size; i++)
    {
        memcpy(arrayOfChildren[i].topLeft.points, byteArray + startIndex, pointSize);
        memcpy(arrayOfChildren[i].bottomRight.points, byteArray + startIndex + pointSize, pointSize);
        startIndex += MBRSize;
    }
    if (isLeaf == 0)
    {
        memcpy(byteArray + startIndex, arrayOfPositions, sizeof(double)*size);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] == nullptr)
            {
                i--;
                continue;
            }
            data[i]->toByteArray(byteArray,&startIndex);
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
    data = new Data*[size+1];
    memset(data,0,sizeof(Data)*size+1);
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