#ifndef RTREEAPP_H
#define RTREEAPP_H

#include <QtWidgets/QMainWindow>
#include "ui_rtreeapp.h"
#include "gpsform.h"
#include "addform.h"
#include "findform.h"
#include <QInputDialog>
#include "DatabaseCore.h"
#include <QMessageBox>

class RtreeApp : public QMainWindow
{
    Q_OBJECT

public:
    RtreeApp(QWidget *parent = 0);
    ~RtreeApp();
    void setDatabase(DatabaseCore* _database);

    private slots:
    void handleAddRealEstateForm();
    void handleEditRealEstateForm();
    void handleFindRealEstateForm();
    void handleRemoveRealEstateForm();
    void handleGenerate();
    void handleAddCoordinate();
    void handleExitCoordinateForm();
    void handleOpenCoordinateForm();
    void handleAddRealEstate();
    void handleCancelAddRealEstate();
    void handleCancelFindRealEstate();
    void handleFindRealEstate();


private:
    DatabaseCore* database;
    addForm addFormWindow;
    findForm findFormWindow;
    gpsForm gpsFormWindow;
    Ui::RtreeAppClass ui;
};

#endif // RTREEAPP_H
