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
    void RtreeApp::handleAddRealEstateForm();
    void RtreeApp::handleEditRealEstateForm();
    void RtreeApp::handleFindRealEstateForm();
    void RtreeApp::handleRemoveRealEstateForm();
    void RtreeApp::handleGenerate();
    void RtreeApp::handleAddCoordinate();
    void RtreeApp::handleExitCoordinateForm();
    void RtreeApp::handleOpenCoordinateForm();
    void RtreeApp::handleAddRealEstate();
    void RtreeApp::handleCancelAddRealEstate();
    void RtreeApp::handleCancelFindRealEstate();
    void RtreeApp::handleFindRealEstate();


private:
    DatabaseCore* database;
    addForm addFormWindow;
    findForm findFormWindow;
    gpsForm gpsFormWindow;
    Ui::RtreeAppClass ui;
};

#endif // RTREEAPP_H
