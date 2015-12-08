#ifndef ADDFORM_H
#define ADDFORM_H

#include <QWidget>
#include "ui_addForm.h"

class addForm : public QWidget
{
    Q_OBJECT

public:
    addForm(QWidget *parent = 0);
    ~addForm();
    char option;
    Ui::addForm ui;

private:
    
};

#endif // ADDFORM_H
