#include "rtreeapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RtreeApp w;
    w.show();
    return a.exec();
}
