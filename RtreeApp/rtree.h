#include <string>
#include "node.h"
#include <windows.h>
#include <io.h>
#include "MBR.h"
#include "NodeFactory.h"
#include <iostream>
#include <vector>
#pragma once
class Rtree
{
private:
    std::string fileName;
    long root;
    FILE* tree;
    long blockSize;
    NodeFactory* factory;
    long first;
public:
    Rtree();
    Rtree(std::string _fileName,long _blockSize,NodeFactory* factory);
    ~Rtree();
    int insertNode(Data* input);
    int insertNode(Data* input, Node* start);
    int deleteNode(Data* input);
    std::vector<Data*> searchNode(MBR nop);
    int editNode(Data* input, Data* old);
    Node* findNode(Data* input);
    void merge(Node* temp);
    void quadraticSplit(Node* temp);
    long useSector();
    void storeSector(long _sector);
    void freeSectors();
};

