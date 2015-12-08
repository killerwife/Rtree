#ifndef GPSFORM_H
#define GPSFORM_H

#include <QWidget>
#include "ui_gpsform.h"

class gpsForm : public QWidget
{
    Q_OBJECT

public:
    gpsForm(QWidget *parent = 0);
    ~gpsForm();

private:
    Ui::gpsForm ui;
};

#endif // GPSFORM_H
