#include "rtreeapp.h"

RtreeApp::RtreeApp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.actionAdd, SIGNAL(triggered()), this, SLOT(handleAddRealEstateForm()));
    connect(ui.actionEdit, SIGNAL(triggered()), this, SLOT(handleEditRealEstateForm()));
    connect(ui.actionFind, SIGNAL(triggered()), this, SLOT(handleFindRealEstateForm()));
    connect(ui.actionRemove, SIGNAL(triggered()), this, SLOT(handleRemoveRealEstateForm()));
    connect(ui.actionGenerate, SIGNAL(triggered()), this, SLOT(handleGenerate()));
    connect(ui.actionBlock_view, SIGNAL(triggered()), this, SLOT(handleBlockView()));
    connect(gpsFormWindow.ui.buttonAddCoordinate, SIGNAL(released()), this, SLOT(handleAddCoordinate()));
    connect(gpsFormWindow.ui.buttonExitCoordinate, SIGNAL(released()), this, SLOT(handleExitCoordinateForm()));
    connect(addFormWindow.ui.buttonAddCoordinate, SIGNAL(released()), this, SLOT(handleOpenCoordinateForm()));
    connect(addFormWindow.ui.buttonAdd, SIGNAL(released()), this, SLOT(handleAddRealEstate()));
    connect(addFormWindow.ui.buttonCancel, SIGNAL(released()), this, SLOT(handleCancelAddRealEstate()));
    connect(findFormWindow.ui.buttonCancel, SIGNAL(released()), this, SLOT(handleCancelFindRealEstate()));
    connect(findFormWindow.ui.buttonFind, SIGNAL(released()), this, SLOT(handleFindRealEstate()));
}

RtreeApp::~RtreeApp()
{

}

void RtreeApp::handleAddRealEstateForm()
{
    gpsFormWindow.count = 0;
    addFormWindow.option = 0;
    addFormWindow.ui.textEdit->setText("");
    addFormWindow.ui.lineName->setText("");
    addFormWindow.ui.lineID->setText("");
    addFormWindow.ui.lineDescription->setText("");
    addFormWindow.ui.buttonAdd->setText("Add");
    addFormWindow.show();
}

void RtreeApp::handleEditRealEstateForm()
{
    findFormWindow.ui.labelID->show();
    findFormWindow.ui.lineID->show();
    findFormWindow.ui.lineBLX->setText("");
    findFormWindow.ui.lineBLY->setText("");
    findFormWindow.ui.lineTRX->setText("");
    findFormWindow.ui.lineTRY->setText("");
    findFormWindow.ui.lineID->setText("");
    findFormWindow.option = 2;
    findFormWindow.show();
}

void RtreeApp::handleFindRealEstateForm()
{
    findFormWindow.ui.labelID->hide();
    findFormWindow.ui.lineID->hide();
    findFormWindow.ui.buttonFind->setText("Find");
    findFormWindow.ui.lineBLX->setText("");
    findFormWindow.ui.lineBLY->setText("");
    findFormWindow.ui.lineTRX->setText("");
    findFormWindow.ui.lineTRY->setText("");
    findFormWindow.option = 0;
    findFormWindow.show();
}

void RtreeApp::handleRemoveRealEstateForm()
{
    findFormWindow.ui.labelID->show();
    findFormWindow.ui.lineID->show();
    findFormWindow.ui.buttonFind->setText("Delete");
    findFormWindow.option = 1;
    findFormWindow.show();
}

void RtreeApp::handleGenerate()
{
    bool ok;
    QString temp = QInputDialog::getText(this, "Generation", "Amount", QLineEdit::Normal, "", &ok);
    if (ok && !temp.isEmpty())
    {
        database->generate(temp.toLongLong());
    }
}

void RtreeApp::handleAddCoordinate()
{
    QString height = gpsFormWindow.ui.lineHeight->text();
    QString width = gpsFormWindow.ui.lineWidth->text();
    QString X = gpsFormWindow.ui.lineX->text();
    QString Y = gpsFormWindow.ui.lineY->text();
    gpsFormWindow.coordinates[gpsFormWindow.count].height = height.at(0).toLatin1();
    gpsFormWindow.coordinates[gpsFormWindow.count].width = width.at(0).toLatin1();
    gpsFormWindow.coordinates[gpsFormWindow.count].heightPosition = X.toDouble();
    gpsFormWindow.coordinates[gpsFormWindow.count].widthPosition = Y.toDouble();
    gpsFormWindow.count++;
    gpsFormWindow.ui.lineHeight->setText("");
    gpsFormWindow.ui.lineWidth->setText("");
    gpsFormWindow.ui.lineX->setText("");
    gpsFormWindow.ui.lineY->setText("");
}

void RtreeApp::handleExitCoordinateForm()
{
    gpsFormWindow.hide();
}

void RtreeApp::handleOpenCoordinateForm()
{    
    gpsFormWindow.ui.lineHeight->setText("");
    gpsFormWindow.ui.lineWidth->setText("");
    gpsFormWindow.ui.lineX->setText("");
    gpsFormWindow.ui.lineY->setText("");
    gpsFormWindow.show();
}

void RtreeApp::handleAddRealEstate()
{
    QString ID = addFormWindow.ui.lineID->text();
    QString name = addFormWindow.ui.lineName->text();
    QString description = addFormWindow.ui.lineDescription->text();
    GPS coordinates[60];
    int i, k;
    for (i = 0; i < gpsFormWindow.count; i++)
    {
        coordinates[i] = gpsFormWindow.coordinates[i];
    }
    std::string temp = addFormWindow.ui.textEdit->toPlainText().toStdString();
    for (k = 0; i < 60&&k<temp.size(); i++)
    {
        int lineStart = k;
        std::string line;
        for (; k < temp.size() && temp[k] != '\n'; k++);
        line = temp.substr(lineStart, k - lineStart);
        coordinates[i] = GPS(line);
        k++;
    }
    RealEstate* input = new RealEstate(ID.toLong(), name.toStdString(), description.toStdString(), coordinates,i);
    if (addFormWindow.option == 0)
    {
        int result = database->addRealEstate(input);
        if (result > 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Real Estate already found.");
            msgBox.exec();
        }
        else
        {
            addFormWindow.hide();
        }
    }
    else
    {
        int result = database->editRealEstate(input,tempData);
        addFormWindow.hide();
        delete tempData;
    }
}

void RtreeApp::handleCancelAddRealEstate()
{
    addFormWindow.hide();
}

void RtreeApp::handleCancelFindRealEstate()
{
    findFormWindow.hide();
}

void RtreeApp::handleFindRealEstate()
{
    if (findFormWindow.option == 0)
    {
        double* first = new double[2], *second = new double[2];
        first[0] = findFormWindow.ui.lineBLX->text().toDouble();
        first[1] = findFormWindow.ui.lineBLY->text().toDouble();
        second[0] = findFormWindow.ui.lineTRX->text().toDouble();
        second[1] = findFormWindow.ui.lineTRY->text().toDouble();
        MBR rectangle = MBR(Point(first, 2), Point(second, 2));
        std::vector<Data*> data = database->findRealEstate(rectangle);
        std::string output;
        for (int i = 0; i < data.size(); i++)
        {
            output += data[i]->to_string();
            delete data[i];
        }
        ui.textBrowser->setText(output.data());
        findFormWindow.hide();
    }
    else if (findFormWindow.option == 1)
    {
        double* first = new double[2];
        double *second = new double[2];
        first[0] = findFormWindow.ui.lineBLX->text().toDouble();
        first[1] = findFormWindow.ui.lineBLY->text().toDouble();
        second[0] = findFormWindow.ui.lineTRX->text().toDouble();
        second[1] = findFormWindow.ui.lineTRY->text().toDouble();
        long ID = findFormWindow.ui.lineID->text().toLong();
        MBR rectangle = MBR(Point(first, 2), Point(second, 2));
        RealEstate temp(ID, rectangle);
        int result = database->deleteRealEstate(&temp);
        if (result > 0)
        {
            QMessageBox msgBox;
            switch (result)
            {
            case 1:
                msgBox.setText("Real Estate with given Data does not exist.");
                break;
            }
            msgBox.exec();
        }
        else
        {
            findFormWindow.hide();
        }
    }
    else
    {
        addFormWindow.option = 1;
        double* first = new double[2], *second = new double[2];
        first[0] = findFormWindow.ui.lineBLX->text().toDouble();
        first[1] = findFormWindow.ui.lineBLY->text().toDouble();
        second[0] = findFormWindow.ui.lineTRX->text().toDouble();
        second[1] = findFormWindow.ui.lineTRY->text().toDouble();
        long ID = findFormWindow.ui.lineID->text().toLong();
        MBR rectangle = MBR(Point(first, 2), Point(second, 2));
        std::vector<Data*> data = database->findRealEstate(rectangle);
        int i;
        for (i = 0; i < data.size(); i++)
        {
            if (((RealEstate*)data[i])->ID == ID)
            {
                break;
            }
        }
        if (i == data.size())
        {
            QMessageBox msgBox;
            msgBox.setText("Real Estate with given Data does not exist.");
            msgBox.exec();
        }
        else
        {
            RealEstate* temp = new RealEstate(*((RealEstate*)data[i]));
            addFormWindow.ui.lineID->setText(std::to_string(temp->ID).data());
            addFormWindow.ui.lineName->setText(temp->name.data());
            addFormWindow.ui.lineDescription->setText(temp->description.data());
            std::string output;
            for (int i = 0; i < temp->count; i++)
            {
                output += temp->coordinates[i].to_string() + "\n";
            }
            addFormWindow.ui.textEdit->setText(output.data());
            tempData = temp;
            findFormWindow.hide();
            gpsFormWindow.count = 0;
            addFormWindow.ui.buttonAdd->setText("Edit");
            addFormWindow.show();
            for (int i = 0; i < data.size(); i++)
            {
                delete data[i];
            }
        }        
    }
}

void RtreeApp::handleBlockView()
{
    ui.textBrowser->setText(database->getBlocks().data());
}

void RtreeApp::setDatabase(DatabaseCore* _database)
{
    database = _database;
}
