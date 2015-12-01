#include "node.h"


Node::Node()
{

}

Node::Node(long _blockSize, MBR input)
{
    size = _blockSize / sizeof(Node);
    rectangle.topLeft = input.topLeft;
    rectangle.bottomRight = input.bottomRight;
    isLeaf = 1;
    arrayOfChildren = new MBR[size];
    arrayOfPointers = new long[size];
    memset(arrayOfPointers, -1, sizeof(long)*size);
}

Node::~Node()
{
    delete[] arrayOfChildren;
    delete[] arrayOfPointers;
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
    int startIndex = 1;
    for (int i = 0; i < size; i++)
    {
        memcpy(arrayOfChildren[i].topLeft.points,byteArray+startIndex,pointSize);
        memcpy(arrayOfChildren[i].bottomRight.points, byteArray + startIndex + pointSize, pointSize);
        startIndex += MBRSize;
    }
    memcpy(arrayOfPointers, byteArray + startIndex, sizeof(double)*size);
    delete[]byteArray;
}
void Node::saveToFile(long position, FILE* file)
{
    fseek(file, position, SEEK_SET);
    int pointSize = rectangle.topLeft.dimension*sizeof(double);
    int MBRSize = 2 * pointSize;
    int outputSize = sizeof(char) + sizeof(long)*size + MBRSize*size;
    char* byteArray = new char[outputSize];
    byteArray[0] = isLeaf;
    int startIndex = 1;
    for (int i = 0; i < size; i++)
    {
        memcpy(arrayOfChildren[i].topLeft.points, byteArray + startIndex, pointSize);
        memcpy(arrayOfChildren[i].bottomRight.points, byteArray + startIndex + pointSize, pointSize);
        startIndex += MBRSize;
    }
    memcpy(byteArray + startIndex, arrayOfPointers, sizeof(double)*size);
    fwrite(byteArray, 1, outputSize, file);
    delete[]byteArray;
}

std::string Node::toString()
{
    std::string output;
    output += "Non-Leaf NOP:" + rectangle.toString();
    for (int i = 0; i < size; i++)
    {
        if (arrayOfPointers[i] != -1)
        {
            output += "#" + std::to_string(i) + " Position: " + std::to_string(arrayOfPointers[i]) + " NOP:" + arrayOfChildren[i].toString();
        }
        else
        {
            break;
        }
    }
    return output;
}