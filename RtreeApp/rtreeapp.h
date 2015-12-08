#ifndef RTREEAPP_H
#define RTREEAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_rtreeapp.h"
#include "gpsform.h"
#include "addform.h"
#include "findform.h"

class RtreeApp : public QMainWindow
{
    Q_OBJECT

public:
    RtreeApp(QWidget *parent = 0);
    ~RtreeApp();

private:
    addForm addFormWindow;
    findForm findFormWindow;
    gpsForm gpsFormWindow;
    Ui::RtreeAppClass ui;
};

#endif // RTREEAPP_H
