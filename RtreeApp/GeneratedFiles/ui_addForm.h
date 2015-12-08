/********************************************************************************
** Form generated from reading UI file 'addForm.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFORM_H
#define UI_ADDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_realEstateForm
{
public:
    QPushButton *buttonAdd;
    QPushButton *buttonCancel;
    QLineEdit *lineID;
    QLabel *labelID;
    QLabel *labelName;
    QLabel *llabelDescription;
    QPushButton *buttonAddCoordinate;
    QLineEdit *lineName;
    QLineEdit *lineDescription;
    QTextEdit *textEdit;

    void setupUi(QWidget *realEstateForm)
    {
        if (realEstateForm->objectName().isEmpty())
            realEstateForm->setObjectName(QStringLiteral("realEstateForm"));
        realEstateForm->resize(677, 300);
        buttonAdd = new QPushButton(realEstateForm);
        buttonAdd->setObjectName(QStringLiteral("buttonAdd"));
        buttonAdd->setGeometry(QRect(100, 250, 75, 23));
        buttonCancel = new QPushButton(realEstateForm);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setGeometry(QRect(230, 250, 75, 23));
        lineID = new QLineEdit(realEstateForm);
        lineID->setObjectName(QStringLiteral("lineID"));
        lineID->setGeometry(QRect(180, 50, 113, 20));
        labelID = new QLabel(realEstateForm);
        labelID->setObjectName(QStringLiteral("labelID"));
        labelID->setGeometry(QRect(40, 50, 47, 13));
        labelName = new QLabel(realEstateForm);
        labelName->setObjectName(QStringLiteral("labelName"));
        labelName->setGeometry(QRect(40, 90, 47, 13));
        llabelDescription = new QLabel(realEstateForm);
        llabelDescription->setObjectName(QStringLiteral("llabelDescription"));
        llabelDescription->setGeometry(QRect(40, 130, 71, 16));
        buttonAddCoordinate = new QPushButton(realEstateForm);
        buttonAddCoordinate->setObjectName(QStringLiteral("buttonAddCoordinate"));
        buttonAddCoordinate->setGeometry(QRect(150, 190, 101, 23));
        lineName = new QLineEdit(realEstateForm);
        lineName->setObjectName(QStringLiteral("lineName"));
        lineName->setGeometry(QRect(180, 90, 113, 20));
        lineDescription = new QLineEdit(realEstateForm);
        lineDescription->setObjectName(QStringLiteral("lineDescription"));
        lineDescription->setGeometry(QRect(180, 130, 113, 20));
        textEdit = new QTextEdit(realEstateForm);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(320, 10, 331, 271));

        retranslateUi(realEstateForm);

        QMetaObject::connectSlotsByName(realEstateForm);
    } // setupUi

    void retranslateUi(QWidget *realEstateForm)
    {
        realEstateForm->setWindowTitle(QApplication::translate("realEstateForm", "Form", 0));
        buttonAdd->setText(QApplication::translate("realEstateForm", "OK", 0));
        buttonCancel->setText(QApplication::translate("realEstateForm", "Cancel", 0));
        labelID->setText(QApplication::translate("realEstateForm", "ID", 0));
        labelName->setText(QApplication::translate("realEstateForm", "Name", 0));
        llabelDescription->setText(QApplication::translate("realEstateForm", "Description", 0));
        buttonAddCoordinate->setText(QApplication::translate("realEstateForm", "Add Coordinate", 0));
    } // retranslateUi

};

namespace Ui {
    class realEstateForm: public Ui_realEstateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFORM_H
