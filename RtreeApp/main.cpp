#include "rtreeapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RtreeApp w;
    DatabaseCore* temp = new DatabaseCore();
    w.setDatabase(temp);
    w.show();
    srand(time(NULL));
    GPS coordinates[60];
    coordinates[0].height = 'Z';
    coordinates[0].width = 'S';
    coordinates[0].heightPosition = 5;
    coordinates[0].widthPosition = 10;
    coordinates[1].height = 'V';
    coordinates[1].width = 'J';
    coordinates[1].heightPosition = 10;
    coordinates[1].widthPosition = 5;
    temp->addRealEstate(new RealEstate(5,"bla","blabla",coordinates,2));
    int result=a.exec();
    delete temp;
    return result;
}
