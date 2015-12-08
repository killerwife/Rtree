#include "rtree.h"


Rtree::Rtree()
{
    fileName = "tempOutput.txt";
    tree = fopen(fileName.data(), "w+");
    root = -1;
    first = -1;
}

Rtree::Rtree(std::string _fileName, long _blockSize, NodeFactory* _factory)
{
    fileName = _fileName;
    blockSize = _blockSize;
    tree = fopen(fileName.data(), "w+");
    factory = _factory;
    fread(&first,sizeof(long),0,tree);
    long checkPos = fseek(tree, 0, SEEK_END);
    if (checkPos == 0)
    {
        root = -1;
    }
    else
    {
        root = 4;
    }
}

Rtree::~Rtree()
{
    fclose(tree);
    delete factory;
}

int Rtree::insertNode(Data* input)
{
    if (root == -1)
    {
        Node* temp = factory->getLeafNode();
        int result = temp->addChild(input);
        return 0;
    }
    else
    {
        return insertNode(input, nullptr);
    }
}

int Rtree::insertNode(Data* input, Node* start)
{
    Node* temp;
    temp = start == nullptr ? factory->getNode(tree, root, blockSize) : start;
    while (temp->isLeaf != 1)
    {
        MBR area;
        int index;
        double min=99999999999999;
        for (int i = 0; i < temp->getCount(); i++)
        {
            double num;
            area = temp->arrayOfChildren[i] + input->rectangle;
            if ((num=area.area() - temp->arrayOfChildren[i].area())< min)
            {
                index = i;
                min = num;
            }
        }
        temp->arrayOfChildren[index] = temp->arrayOfChildren[index] + input->rectangle;
        temp->readFromFile(temp->arrayOfPositions[index], tree);
    }
    int result = temp->addChild(input);
    if (result > 0)
    {
        quadraticSplit(temp);
    }
    return 0;
}

int Rtree::editNode(Data* input, MBR old)
{
    Node* leaf = findNode(old);
    leaf->editChild(old,input);
    leaf->saveToFile(tree);
    if (!(input->rectangle == old))
    {
        while (leaf->location != root)
        {
            Node* parent = factory->getNode(tree,leaf->parent,blockSize);
            parent->rectangle = parent->rectangle + input->rectangle;
            parent->saveToFile(tree);
            delete leaf;
            leaf = parent;
        }
    }
    return 1;
}

Node* Rtree::findNode(MBR input)
{
    std::vector<long> stackPos;
    Node* leaf;
    stackPos.push_back(root);
    for (int i = 0; i < stackPos.size(); i++)
    {
        Node* temp = factory->getNode(tree, stackPos[i], blockSize);
        for (int k = 0; k < temp->getCount(); k++)
        {
            if (temp->isLeaf == 0)
            {
                if (temp->arrayOfChildren[i].isInside(input))
                {
                    stackPos.push_back(temp->arrayOfPositions[i]);
                }
            }
            else
            {
                if (temp->data[i]->rectangle == input)
                {
                    leaf = temp;
                    i = stackPos.size();
                    break;
                }
            }
        }
        if (i != stackPos.size())
        {
            delete temp;
        }
    }
    return leaf;
}

int Rtree::deleteNode(Data* input)
{
    Node* leaf = findNode(input->rectangle);
    int result = leaf->removeChild(input);
    if (result == 1&&leaf->location!=root)
    {
        merge(leaf);
    }
    delete leaf;
    return 0;
}

void Rtree::merge(Node* temp)
{
    int check=1;
    while (temp->location != root&&check==1)
    {
        check = 0;
        Node* parent = factory->getNode(tree, temp->parent, blockSize);
        int result = parent->removeChild(temp->rectangle);
        for (int i = 0; i < temp->getCount(); i++)
        {
            MBR area;
            int index;
            double min = 99999999999999;
            for (int k = 0; k < temp->getCount(); k++)
            {
                double num;
                if (temp->isLeaf == 1)
                {
                    area = parent->arrayOfChildren[k] + temp->data[i]->rectangle;
                }
                else
                {
                    area = parent->arrayOfChildren[k] + temp->arrayOfChildren[i];
                }                
                if ((num = area.area() - parent->arrayOfChildren[k].area())< min)
                {
                    index = k;
                    min = num;
                }
            }
            parent->editChild(parent->arrayOfChildren[index] + (temp->isLeaf == 1 ? temp->data[i]->rectangle : temp->arrayOfChildren[i]), parent->arrayOfPositions[index]);
            Node* sibling = factory->getNode(tree, parent->arrayOfPositions[index], blockSize);
            if (temp->isLeaf == 1)
            {
                int result2=sibling->addChild(temp->data[index]);
                if (result2 == 1)
                {
                    quadraticSplit(sibling);
                }
            }
            else
            {
                int result2 = sibling->addChild(temp->arrayOfChildren[index], temp->arrayOfPositions[index]);
                if (result2 == 1)
                {
                    quadraticSplit(sibling);
                }
            }
            delete sibling;
        }
        storeSector(temp->location);
        delete temp;
        temp = parent;
        check = result;
    }
    delete temp;
}

std::vector<Data*> Rtree::searchNode(MBR nop)
{   
    std::vector<long> stackPos;
    std::vector<Data*> result;
    stackPos.push_back(root);
    for (int i = 0; i < stackPos.size(); i++)
    {
        Node* temp = factory->getNode(tree, stackPos[i], blockSize);
        for (int k = 0; k < temp->getCount(); k++)
        {
            if (temp->isLeaf == 0)
            {
                if (temp->arrayOfChildren[i].isInside(nop))
                {
                    stackPos.push_back(temp->arrayOfPositions[i]);
                }
            }
            else
            {
                if (temp->data[i]->rectangle.isInside(nop))
                {
                    result.push_back(temp->data[i]);
                }
            }
        }
        delete temp;
    }
    return result;
}

void Rtree::quadraticSplit(Node* temp)
{
    Node* parent;
    Node* sibling;
    int done = 0;
    while (done == 0)
    {
        if (temp->location == root)
        {
            parent = factory->getBasicNode();
            parent->location = useSector();
            temp->parent = parent->location;
        }
        else
        {
            parent = factory->getNode(tree, temp->parent, blockSize);
        }
        done = 1;
        if (temp->isLeaf == 1)
        {
            sibling = factory->getLeafNode();
            sibling->parent = temp->parent;
            sibling->location = useSector();
            Data** data = temp->data;
            temp->data = new Data*[temp->getSize() + 1];
            int furthest, apart;
            for (int i = 0; i < temp->getCount(); i++)
            {
                double maxDistance = -1;
                for (int k = 0; k < temp->getCount(); k++)
                {
                    double temp;
                    if (i == k)
                    {
                        continue;
                    }
                    if (maxDistance != -1)
                    {
                        if ((temp = data[i]->rectangle.distance(data[k]->rectangle))>maxDistance)
                        {
                            maxDistance = temp;
                            furthest = i;
                            apart = k;
                        }
                    }
                    else
                    {
                        maxDistance = data[i]->rectangle.distance(data[k]->rectangle);
                        furthest = i;
                        apart = k;
                    }
                }
            }
            temp->rectangle = data[furthest]->rectangle;
            sibling->rectangle = data[apart]->rectangle;            
            for (int i = 0; i < temp->getCount(); i++)
            {
                if (i != furthest&&i != apart)
                {
                    MBR rec1 = sibling->rectangle + data[i]->rectangle, rec2 = temp->rectangle + data[i]->rectangle;
                    double area1 = rec1.area() - sibling->rectangle.area(), area2 = rec2.area() - temp->rectangle.area();
                    if (area1 > area2)
                    {
                        temp->addChild(data[i]);
                    }
                    else
                    {
                        sibling->addChild(data[i]);
                    }
                }
            }
            parent->addChild(sibling->rectangle, sibling->location);
            parent->editChild(temp->rectangle, temp->location);
            delete[] data;
        }
        else
        {
            sibling = factory->getBasicNode();
            sibling->parent = temp->parent;
            sibling->location = useSector();
            MBR* rectangles = temp->arrayOfChildren;
            long* positions = temp->arrayOfPositions;
            temp->arrayOfChildren = new MBR[temp->getSize() + 1];
            temp->arrayOfPositions = new long[temp->getSize() + 1];
            int furthest, apart;
            for (int i = 0; i < temp->getCount(); i++)
            {
                double maxDistance = -1;
                for (int k = 0; k < temp->getCount(); k++)
                {
                    double temp;
                    if (i == k)
                    {
                        continue;
                    }
                    if (maxDistance != -1)
                    {
                        if ((temp = rectangles[i].distance(rectangles[k]))>maxDistance)
                        {
                            maxDistance = temp;
                            furthest = i;
                            apart = k;
                        }
                    }
                    else
                    {
                        maxDistance = rectangles[i].distance(rectangles[k]);
                        furthest = i;
                        apart = k;
                    }
                }
            }
            temp->rectangle = rectangles[furthest];
            sibling->rectangle = rectangles[apart];            
            for (int i = 0; i < temp->getCount(); i++)
            {
                if (i != furthest&&i != apart)
                {
                    MBR rec1=sibling->rectangle+rectangles[i], rec2=temp->rectangle+rectangles[i];
                    double area1 = rec1.area() - sibling->rectangle.area(), area2 = rec2.area() - temp->rectangle.area();
                    if (area1 > area2)
                    {
                        temp->addChild(rectangles[i],positions[i]);
                    }
                    else
                    {
                        sibling->addChild(rectangles[i], positions[i]);
                    }
                }
            }
            parent->addChild(sibling->rectangle, sibling->location);
            parent->editChild(temp->rectangle, temp->location);
            delete[] rectangles;
            delete[] positions;
        }
        temp->saveToFile(tree);
        sibling->saveToFile(tree);
        delete temp;
        delete sibling;
        temp = parent;
    }
}

long Rtree::useSector()
{
    if (first == -1)
    {
        fseek(tree,0,SEEK_END);
        return ftell(tree);
    }
    else
    {
        fseek(tree, 0, first);
        long temp = first;
        char byteArray[5];
        fread(byteArray,sizeof(long),1,tree);
        memcpy(&temp,byteArray+sizeof(char),sizeof(long));
        return temp;
    }
}

void Rtree::storeSector(long _sector)
{
    char empty = -1;
    long zero = -1;
    fseek(tree, 0, _sector);
    char byteArray[9];
    byteArray[0] = -1;
    memcpy(byteArray + sizeof(char), &first, sizeof(long));
    memcpy(byteArray + sizeof(char)+sizeof(long), &zero, sizeof(long));
    fwrite(byteArray,sizeof(long)*2+sizeof(char),1,tree);
    first = _sector;
}

void Rtree::freeSectors()
{
    char empty=-1;
    while (empty == -1)
    {
        fseek(tree, -blockSize, SEEK_END);
        char byteArray[9];
        fread(byteArray, sizeof(char) + sizeof(long) * 2, 1, tree);
        empty = byteArray[0];
        if (empty == -1)
        {
            long temp;
            long previous;
            memcpy(&temp, byteArray + sizeof(char), sizeof(long));
            memcpy(&previous, byteArray + sizeof(char) + sizeof(long), sizeof(long));
            SetEndOfFile((HANDLE)_get_osfhandle(_fileno(tree)));
            fseek(tree, 1, previous);
            fwrite(&temp, sizeof(long), 1, tree);
        }
        else
        {
            return;
        }
    }    
}