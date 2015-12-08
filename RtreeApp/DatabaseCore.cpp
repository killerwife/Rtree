#include "DatabaseCore.h"


DatabaseCore::DatabaseCore()
{
    realEstateTree = Rtree("temp.txt", 1024, new BasicNodeFactory(new RealEstateDataFactory()));
}


DatabaseCore::~DatabaseCore()
{
  
}

std::vector<Data*> DatabaseCore::findRealEstate(MBR box)
{
    return realEstateTree.searchNode(box);
}

int DatabaseCore::addRealEstate(RealEstate* input)
{
    realEstateTree.insertNode(input);
    return 0;
}

int DatabaseCore::deleteRealEstate(RealEstate* input)
{
    realEstateTree.deleteNode(input);
    return 0;
}

int DatabaseCore::editRealEstate(RealEstate* input,MBR old)
{
    realEstateTree.editNode(input,old);
    return 0;
}
