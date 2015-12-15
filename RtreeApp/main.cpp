#include "rtreeapp.h"
#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int mergeTest()
{
    FILE* temp = fopen("mergeTest.txt","w+");
    fclose(temp);
    DatabaseCore database("mergeTest.txt");
    int amount = 2000;
    RealEstate* data = new RealEstate[amount];
    for (int i = 0; i < amount; i++)
    {
        RealEstate *temp = new RealEstate(data[i]);
        int result=database.addRealEstate(temp);
        if (result == 1)
        {
            printf("bla");
        }
    }
    for (int i = 0; i < amount; i++)
    {
        std::vector<Data*> foundData=database.findRealEstate(data[i].rectangle);
        int check = 0;
        if (foundData.size() == 0)
        {
            printf("bla");
            return 1;
        }
        for (int k = 0; k < foundData.size(); k++)
        {
            Data* temp = foundData[k];
            if (data[i] == temp)
            {
                check = 1;
                break;
            }
        }
        for (int k = 0; k < foundData.size(); k++)
        {
            delete foundData[k];
        }
        if (check == 0)
        {
            printf("blabla\n");
            return 1;
        }
    }
    for (int i = 0; i < amount; i++)
    {
        RealEstate *temp = new RealEstate(data[i]);
        int check=database.deleteRealEstate(temp);
        if (check == 1)
        {
            printf("blabla\n");
            return 1;
        }
        delete temp;
    }
    for (int i = 0; i < amount; i++)
    {
        std::vector<Data*> foundData = database.findRealEstate(data[i].rectangle);
        int check = 0;
        for (int k = 0; k < foundData.size(); k++)
        {
            Data* temp = foundData[k];
            if (data[i] == temp)
            {
                check = 1;
                break;
            }
        }
        for (int k = 0; k < foundData.size(); k++)
        {
            delete foundData[k];
        }
        if (check == 1)
        {
            printf("blabla\n");
            return 1;
        }
    }
    delete[]data;
    return 0;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int integrityResult=mergeTest();
    if (integrityResult == 1)
    {
        return 0;
    }
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    QApplication a(argc, argv);
    RtreeApp w;
    DatabaseCore* temp = new DatabaseCore();
    w.setDatabase(temp);
    w.show();
   /* GPS coordinates[60];
    coordinates[0].height = 'Z';
    coordinates[0].width = 'S';
    coordinates[0].heightPosition = 5;
    coordinates[0].widthPosition = 10;
    coordinates[1].height = 'V';
    coordinates[1].width = 'J';
    coordinates[1].heightPosition = 10;
    coordinates[1].widthPosition = 5;
    RealEstate* building = new RealEstate(5, "bla", "blabla", coordinates, 2);
    int result=temp->addRealEstate(building);
    if (result == 1)
    {
        delete building;
    }*/
    int result=a.exec();
    delete temp;
    return result;
}
