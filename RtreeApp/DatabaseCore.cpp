#include "DatabaseCore.h"


DatabaseCore::DatabaseCore() : realEstateTree("temp.txt", 10240, new BasicNodeFactory(new RealEstateDataFactory()))
{

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
    return realEstateTree.insertNode(input);
}

int DatabaseCore::deleteRealEstate(RealEstate* input)
{    
    return realEstateTree.deleteNode(input);
}

int DatabaseCore::editRealEstate(RealEstate* input,Data* old)
{    
    return realEstateTree.editNode(input, old);
}

void DatabaseCore::generate(long long amount)
{
    for (int i = 0; i < amount; i++)
    {
        int check = 0;
        RealEstate* temp = new RealEstate();
        check = realEstateTree.insertNode(temp);
        while (check == 1)
        {
            temp->regenerate();
            check=realEstateTree.insertNode(temp);
        }
    }
}
