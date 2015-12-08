#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>
#include "ui_findForm.h"

class findForm : public QWidget
{
    Q_OBJECT

public:
    findForm(QWidget *parent = 0);
    ~findForm();
    char option;
    Ui::findRealEstateForm ui;
private:
    
};

#endif // FINDFORM_H
