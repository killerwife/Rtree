#include "rtree.h"


Rtree::Rtree()
{
    fileName = "tempOutput.txt";
    tree = fopen(fileName.data(), "rb+");
    root = -1;
    first = -1;
}

Rtree::Rtree(std::string _fileName, long _blockSize, NodeFactory* _factory)
{
    fileName = _fileName;
    blockSize = _blockSize;
    tree = fopen(fileName.data(), "rb+");
    if (tree == NULL)
    {
        tree = fopen(fileName.data(), "wb+");
    }
    factory = _factory;
    fread(&first, sizeof(long), 0, tree);
    fseek(tree, 0, SEEK_END);
    long checkPos = ftell(tree);
    if (checkPos == 0)
    {
        root = -1;
        first = -1;
    }
    else
    {
        root = sizeof(long) * 2;
        end = checkPos;
        fseek(tree, 0, SEEK_SET);
        fread(&first, sizeof(long), 1, tree);
        fread(&root, sizeof(long), 1, tree);
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
        Node* temp = factory->getLeafNode(blockSize, input->rectangle, -1, useSector());
        int result = temp->addChild(input);
        temp->saveToFile(tree);
        root = defaultRoot;
        delete temp;
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
        double min = 99999999999999;
        for (int i = 0; i < temp->getCount(); i++)
        {
            double num;
            area = temp->arrayOfChildren[i] + input->rectangle;
            if ((num = area.area() - temp->arrayOfChildren[i].area()) < min)
            {
                index = i;
                min = num;
            }
        }
        temp->rectangle = temp->rectangle + input->rectangle;
        temp->arrayOfChildren[index] = temp->arrayOfChildren[index] + input->rectangle;
        temp->saveToFile(tree);
        temp->readFromFile(temp->arrayOfPositions[index], tree);
    }
    for (int i = 0; i < temp->getCount(); i++)
    {
        if (*(temp->data[i]) == input)
        {
            delete temp;
            return 1;
        }
    }
    int result = temp->addChild(input);
    if (result > 0)
    {
        quadraticSplit(temp);
    }
    else
    {
        temp->saveToFile(tree);
        delete temp;
    }
    return 0;
}


void Rtree::quadraticSplit(Node* temp)
{
    Node* parent;
    Node* sibling;
    int done = 1;
    while (done == 1)
    {
        int splitRoot = 0;
        if (temp->location == root)
        {
            parent = factory->getBasicNode(blockSize, temp->rectangle, -1, useSector());
            temp->parent = parent->location;
            makeRoot(parent->location);
            splitRoot = 1;
        }
        else
        {
            parent = factory->getNode(tree, temp->parent, blockSize);
        }
        done = 0;
        if (temp->isLeaf == 1)
        {
            sibling = factory->getLeafNode(blockSize, MBR(temp->rectangle.bottomLeft.dimension), temp->parent, useSector());
            Data** data = temp->data;
            temp->data = new Data*[temp->getSize() + 1];
            int tempCount = temp->getCount();
            temp->count = 0;
            int furthest, apart;
            double maxDistance = -1;
            for (int i = 0; i < tempCount; i++)
            {
                for (int k = 0; k < tempCount; k++)
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
            temp->addChild(data[furthest]);
            sibling->rectangle = data[apart]->rectangle;
            sibling->addChild(data[apart]);
            for (int i = 0; i < tempCount; i++)
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
            if (splitRoot == 1)
            {
                int output=parent->addChild(temp->rectangle, temp->location);
                if (output != 0)
                {
                    printf("bla");
                }
            }
            else
            {
                int output = parent->editChild(temp->rectangle, temp->location);
                if (output != 0)
                {
                    printf("bla");
                }
            }
            done = parent->addChild(sibling->rectangle, sibling->location);            
            delete[] data;
        }
        else
        {
            sibling = factory->getBasicNode(blockSize, MBR(temp->rectangle.bottomLeft.dimension), temp->parent, useSector());
            MBR* rectangles = temp->arrayOfChildren;
            long* positions = temp->arrayOfPositions;
            temp->arrayOfChildren = new MBR[temp->getSize() + 1];
            temp->arrayOfPositions = new long[temp->getSize() + 1];
            int tempCount = temp->getCount();
            temp->count = 0;
            int furthest, apart;
            double maxDistance = -1;
            for (int i = 0; i < tempCount; i++)
            {
                for (int k = 0; k < tempCount; k++)
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
            temp->addChild(rectangles[furthest], positions[furthest]);
            sibling->rectangle = rectangles[apart];
            sibling->addChild(rectangles[apart], positions[apart]);
            Node* changeParent = factory->getNode(tree, positions[apart], blockSize);
            changeParent->parent = sibling->location;
            changeParent->saveToFile(tree);
            delete changeParent;
            for (int i = 0; i < tempCount; i++)
            {
                if (i != furthest&&i != apart)
                {
                    MBR rec1 = sibling->rectangle + rectangles[i], rec2 = temp->rectangle + rectangles[i];
                    double area1 = rec1.area() - sibling->rectangle.area(), area2 = rec2.area() - temp->rectangle.area();
                    if (area1 > area2)
                    {
                        temp->addChild(rectangles[i], positions[i]);
                    }
                    else
                    {
                        sibling->addChild(rectangles[i], positions[i]);
                        changeParent = factory->getNode(tree, positions[i], blockSize);
                        changeParent->parent = sibling->location;
                        changeParent->saveToFile(tree);
                        delete changeParent;
                    }
                }
            }
            if (splitRoot == 1)
            {
                int output=parent->addChild(temp->rectangle, temp->location);
                if (output != 0)
                {
                    printf("bla");
                }
            }
            else
            {
                int output = parent->editChild(temp->rectangle, temp->location);
                if (output != 0)
                {
                    printf("bla");
                }
            }
            done = parent->addChild(sibling->rectangle, sibling->location);            
            delete[] rectangles;
            delete[] positions;
        }
        temp->saveToFile(tree);
        sibling->saveToFile(tree);
        delete temp;
        delete sibling;
        temp = parent;
    }
    temp->saveToFile(tree);
    delete temp;
}

int Rtree::editNode(Data* input, Data* old)
{
    Node* leaf = findNode(old);
    leaf->editChild(old->rectangle, input);
    leaf->saveToFile(tree);
    if (!(input->rectangle == old->rectangle))
    {
        while (leaf->location != root)
        {
            Node* parent = factory->getNode(tree, leaf->parent, blockSize);
            parent->rectangle = parent->rectangle + input->rectangle;
            parent->saveToFile(tree);
            delete leaf;
            leaf = parent;
        }
    }
    delete leaf;
    return 0;
}

Node* Rtree::findNode(Data* input)
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
                if (temp->arrayOfChildren[k].isInside(input->rectangle))
                {
                    stackPos.push_back(temp->arrayOfPositions[k]);
                }
            }
            else
            {
                if (*(temp->data[k]) == input)
                {
                    leaf = temp;
                    return leaf;
                }
            }
        }
        delete temp;
    }
    return nullptr;
}

std::vector<Data*> Rtree::searchNode(MBR nop)
{
    std::vector<long> stackPos;
    std::vector<Data*> result;
    stackPos.push_back(root);
    for (int i = 0; i < stackPos.size(); i++)
    {
        Node* temp = factory->getNode(tree, stackPos[i], blockSize);
        if (temp->rectangle.isInside(nop) == false)
        {
            delete temp;
            return result;
        }
        for (int k = 0; k < temp->getCount(); k++)
        {
            if (temp->isLeaf == 0)
            {
                if (temp->arrayOfChildren[k].isInside(nop))
                {
                    stackPos.push_back(temp->arrayOfPositions[k]);
                }
            }
            else
            {
                if (temp->data[k]->rectangle.isInside(nop))
                {
                    Data* data = factory->factory->getData(temp->data[k]);
                    result.push_back(data);
                }
            }
        }
        delete temp;
    }
    return result;
}

int Rtree::deleteNode(Data* input)
{
    Node* leaf = findNode(input);
    if (leaf == nullptr)
    {
        return 1;
    }
    int result = leaf->removeChild(input);
    long position = leaf->parent;
    long childPosition = leaf->location;
    MBR newRectangle = leaf->rectangle;
    Node* temp;
    while (position != -1)
    {
        temp = factory->getNode(tree,position,blockSize);
        temp->editChild(newRectangle,childPosition);
        childPosition = temp->location;
        position = temp->parent;
        newRectangle = temp->rectangle;
        temp->saveToFile(tree);
        delete temp;
    }
    if (result == 1 && leaf->location != root)
    {
        merge(leaf);
    }
    else
    {
        if (result == 2)
        {
            printf("bla");
        }
        leaf->saveToFile(tree);
        delete leaf;
    }
    return 0;
}

void Rtree::merge(Node* temp)
{
    int check = 1;
    while (temp->location != root&&check == 1)
    {
        check = 0;
        Node* parent = factory->getNode(tree, temp->parent, blockSize);
        Node* child = nullptr;
        for (int k = 0; k < parent->getCount(); k++)
        {
            if (parent->arrayOfPositions[k] == temp->location)
            {
                continue;
            }
            child = factory->getNode(tree, parent->arrayOfPositions[k], blockSize);
            if (child->count - 1 >= sqrt(child->getSize()))
            {
                check = -1;
                break;
            }
            delete child;
            child = nullptr;
        }
        if (child != nullptr)
        {
            if (temp->isLeaf == 1)
            {
                temp->addChild(child->extractLastChildLeaf());
            }
            else
            {
                MBR rectangle(child->arrayOfChildren[child->count - 1]);
                long tempPos = child->extractLastChild();
                temp->addChild(rectangle, tempPos);
                Node* changeParent = factory->getNode(tree, tempPos, blockSize);
                changeParent->parent = temp->location;
                changeParent->saveToFile(tree);
                delete changeParent;
            }
            parent->editChild(temp->rectangle,temp->location);
            parent->editChild(child->rectangle, child->location);
            child->saveToFile(tree);
            delete child;
        }
        else
        {
            child = factory->getNode(tree, parent->arrayOfPositions[parent->count - 1] == temp->location ? parent->arrayOfPositions[parent->count - 2] : parent->arrayOfPositions[parent->count - 1], blockSize);
            if (temp->isLeaf == 1)
            {
                while (child->count > 0)
                {
                    temp->addChild(child->data[child->count - 1]);
                    child->count--;
                }
            }
            else
            {
                while (child->count > 0)
                {
                    temp->addChild(child->arrayOfChildren[child->count - 1], child->arrayOfPositions[child->count - 1]);                    
                    Node* changeParent = factory->getNode(tree, child->arrayOfPositions[child->count - 1], blockSize);
                    changeParent->parent = temp->location;
                    changeParent->saveToFile(tree);
                    delete changeParent;
                    child->count--;
                }
            }
            check=parent->removeChild(child->rectangle, child->location);
            if (check == 1)
            {
                printf("bla");
            }
            parent->editChild(temp->rectangle, temp->location);
            storeSector(child->location);            
            delete child;
        }
        temp->saveToFile(tree);
        delete temp;
        temp = parent;
    }
    if (check == 1)
    {
        Node* firstChild = factory->getNode(tree,temp->arrayOfPositions[0],blockSize);
        if (firstChild->isLeaf == 1)
        {
            long squareRoot = sqrt(firstChild->getSize());
            if (temp->count <= squareRoot)
            {
                long sum = firstChild->count;
                Node** childrenArray = new Node*[squareRoot];
                for (int i = 0; i+1 < temp->count; i++)
                {
                    childrenArray[i] = factory->getNode(tree, temp->arrayOfPositions[i+1],blockSize);
                    sum += childrenArray[i]->count;
                }
                if (sum <= firstChild->getSize())
                {
                    for (int i = 0; i+1 < temp->count; i++)
                    {
                        while (childrenArray[i]->count > 0)
                        {
                            firstChild->addChild(childrenArray[i]->extractLastChildLeaf());
                        }
                        storeSector(childrenArray[i]->location);
                        delete childrenArray[i];
                    }
                    makeRoot(firstChild->location);
                    firstChild->parent = -1;
                    firstChild->saveToFile(tree);
                }
                else
                {
                    for (int i = 0; i + 1 < temp->count; i++)
                    {
                        delete childrenArray[i];
                    }
                    temp->saveToFile(tree);
                }
                delete[] childrenArray;
            }
            else
            {
                temp->saveToFile(tree);
            }
        }
        else
        {
            storeSector(temp->location);
            makeRoot(firstChild->location);
            firstChild->parent = -1;
            for (int i = 1; i < temp->count; i++)
            {
                Node* tempChild = factory->getNode(tree, temp->arrayOfPositions[i], blockSize);
                while (tempChild->count > 0)
                {
                    MBR rectangle(tempChild->arrayOfChildren[tempChild->count - 1]);
                    long tempPos = tempChild->extractLastChild();
                    firstChild->addChild(rectangle, tempPos);
                    Node* changeParent = factory->getNode(tree, tempPos, blockSize);
                    changeParent->parent = firstChild->location;
                    changeParent->saveToFile(tree);
                    delete changeParent;
                }
                storeSector(tempChild->location);
                delete tempChild;
            }
            firstChild->saveToFile(tree);
        }
        delete firstChild;
    }
    else
    {
        temp->saveToFile(tree);
    }
    delete temp;
}

long Rtree::useSector()
{
    if (root == -1)
    {
        long temp = -1;
        fwrite(&temp, sizeof(long), 1, tree);
        temp = defaultRoot;
        fwrite(&temp, sizeof(long), 1, tree);
        end = ftell(tree);
        return end;
    }
    else if (first == -1)
    {
        end += blockSize;
        char temp = 1;
        fseek(tree, end, SEEK_SET);
        fwrite(&temp, sizeof(char), 1, tree);
        return end;
    }
    else
    {
        fseek(tree, first, SEEK_SET);
        long temp = first;
        char byteArray[5];
        fread(byteArray, sizeof(long), 1, tree);
        memcpy(&first, byteArray + sizeof(char), sizeof(long));
        return temp;
    }
}

void Rtree::storeSector(long _sector)
{
    fseek(tree, -blockSize, SEEK_END);    
    char empty = -1;
    long zero = -1;
    fseek(tree, _sector, SEEK_SET);
    char byteArray[9];
    byteArray[0] = empty;
    memcpy(byteArray + sizeof(char), &first, sizeof(long));
    memcpy(byteArray + sizeof(char) + sizeof(long), &zero, sizeof(long));
    fwrite(byteArray, sizeof(long) * 2 + sizeof(char), 1, tree);
    first = _sector;
    fseek(tree, 0, SEEK_SET);
    fwrite(&first, sizeof(long), 1, tree);
    fflush(tree);
    fseek(tree, -blockSize, SEEK_END);
    if (_sector == ftell(tree))
    {
        freeSectors();
    }
    fflush(tree);
}

void Rtree::freeSectors()
{
    char empty = -1;
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
            fseek(tree, -blockSize, SEEK_END);
            _chsize(fileno(tree), ftell(tree));
            fseek(tree, previous + 1, SEEK_SET);
            fwrite(&temp, sizeof(long), 1, tree);
        }
        else
        {
            return;
        }
    }
}

void Rtree::makeRoot(long location)
{
    root = location;
    fseek(tree, sizeof(long), SEEK_SET);
    fwrite(&location, sizeof(long), 1, tree);
}

std::string Rtree::sequentialRead()
{
    long position = defaultRoot;
    std::string output;
    fseek(tree,0,SEEK_END);
    long end = ftell(tree);
    int i = 0;
    long number = 0;
    while (position < end)
    {
        output += "#" + std::to_string(i)+":";
        Node* temp = factory->getNode(tree,position,blockSize);
        MBR check;
        for (int k = 0; k < temp->count; k++)
        {
            if (temp->isLeaf == 1)
            {
                check = check + temp->data[k]->rectangle;
            }
            else
            {
                check = check + temp->arrayOfChildren[k];
            }
        }
        if (!(check == temp->rectangle))
        {
            delete temp;
            return output;
        }
        if (temp->isLeaf == 1)
        {
            number += temp->count;
        }
        position += blockSize;
        output += temp->toString()+"\n";
        i++;
        delete temp;
    }
    output += "Pocet prvkov:"+std::to_string(number);
    return output;
}