#ifndef GPSFORM_H
#define GPSFORM_H

#include <QWidget>
#include "ui_gpsform.h"
#include "RealEstate.h"

class gpsForm : public QWidget
{
    Q_OBJECT

public:
    GPS coordinates[60];
    int count;
    gpsForm(QWidget *parent = 0);
    ~gpsForm();
    Ui::gpsForm ui;
private:
    
};

#endif // GPSFORM_H
