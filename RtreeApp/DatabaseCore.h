#pragma once
#include "rtree.h"
#include "RealEstate.h"
#include "BasicNodeFactory.h"
#include "RealEstateDataFactory.h"
class DatabaseCore
{
private:
    Rtree realEstateTree;
public:
    DatabaseCore();
    DatabaseCore(std::string filePath);
    ~DatabaseCore();
    std::vector<Data*> findRealEstate(MBR box);
    int addRealEstate(RealEstate* input);
    int deleteRealEstate(RealEstate* input);
    int editRealEstate(RealEstate* input, Data* old);
    std::string getBlocks();
    void generate(long long amount);
};

