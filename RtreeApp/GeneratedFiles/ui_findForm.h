/********************************************************************************
** Form generated from reading UI file 'findForm.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDFORM_H
#define UI_FINDFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_findRealEstateForm
{
public:
    QLabel *labelMBR;
    QLabel *labelBL;
    QLabel *labelTR;
    QLabel *labelBLX;
    QLabel *labelBLY;
    QLineEdit *lineBLX;
    QLineEdit *lineTRX;
    QLineEdit *lineTRY;
    QLineEdit *lineBLY;
    QLineEdit *lineID;
    QLabel *labelTRX;
    QLabel *labelTRY;
    QLabel *labelID;
    QPushButton *buttonFind;
    QPushButton *buttonCancel;

    void setupUi(QWidget *findRealEstateForm)
    {
        if (findRealEstateForm->objectName().isEmpty())
            findRealEstateForm->setObjectName(QStringLiteral("findRealEstateForm"));
        findRealEstateForm->resize(400, 300);
        labelMBR = new QLabel(findRealEstateForm);
        labelMBR->setObjectName(QStringLiteral("labelMBR"));
        labelMBR->setGeometry(QRect(20, 20, 47, 13));
        labelBL = new QLabel(findRealEstateForm);
        labelBL->setObjectName(QStringLiteral("labelBL"));
        labelBL->setGeometry(QRect(90, 20, 71, 16));
        labelTR = new QLabel(findRealEstateForm);
        labelTR->setObjectName(QStringLiteral("labelTR"));
        labelTR->setGeometry(QRect(90, 110, 47, 13));
        labelBLX = new QLabel(findRealEstateForm);
        labelBLX->setObjectName(QStringLiteral("labelBLX"));
        labelBLX->setGeometry(QRect(150, 20, 47, 13));
        labelBLY = new QLabel(findRealEstateForm);
        labelBLY->setObjectName(QStringLiteral("labelBLY"));
        labelBLY->setGeometry(QRect(150, 70, 47, 13));
        lineBLX = new QLineEdit(findRealEstateForm);
        lineBLX->setObjectName(QStringLiteral("lineBLX"));
        lineBLX->setGeometry(QRect(200, 20, 113, 20));
        lineTRX = new QLineEdit(findRealEstateForm);
        lineTRX->setObjectName(QStringLiteral("lineTRX"));
        lineTRX->setGeometry(QRect(200, 110, 113, 20));
        lineTRY = new QLineEdit(findRealEstateForm);
        lineTRY->setObjectName(QStringLiteral("lineTRY"));
        lineTRY->setGeometry(QRect(200, 160, 113, 20));
        lineBLY = new QLineEdit(findRealEstateForm);
        lineBLY->setObjectName(QStringLiteral("lineBLY"));
        lineBLY->setGeometry(QRect(200, 60, 113, 20));
        lineID = new QLineEdit(findRealEstateForm);
        lineID->setObjectName(QStringLiteral("lineID"));
        lineID->setGeometry(QRect(200, 200, 113, 20));
        labelTRX = new QLabel(findRealEstateForm);
        labelTRX->setObjectName(QStringLiteral("labelTRX"));
        labelTRX->setGeometry(QRect(150, 110, 47, 13));
        labelTRY = new QLabel(findRealEstateForm);
        labelTRY->setObjectName(QStringLiteral("labelTRY"));
        labelTRY->setGeometry(QRect(150, 160, 47, 13));
        labelID = new QLabel(findRealEstateForm);
        labelID->setObjectName(QStringLiteral("labelID"));
        labelID->setGeometry(QRect(20, 200, 47, 13));
        buttonFind = new QPushButton(findRealEstateForm);
        buttonFind->setObjectName(QStringLiteral("buttonFind"));
        buttonFind->setGeometry(QRect(170, 250, 75, 23));
        buttonCancel = new QPushButton(findRealEstateForm);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setGeometry(QRect(270, 250, 75, 23));

        retranslateUi(findRealEstateForm);

        QMetaObject::connectSlotsByName(findRealEstateForm);
    } // setupUi

    void retranslateUi(QWidget *findRealEstateForm)
    {
        findRealEstateForm->setWindowTitle(QApplication::translate("findRealEstateForm", "Form", 0));
        labelMBR->setText(QApplication::translate("findRealEstateForm", "MBR", 0));
        labelBL->setText(QApplication::translate("findRealEstateForm", "BottomLeft", 0));
        labelTR->setText(QApplication::translate("findRealEstateForm", "TopRight", 0));
        labelBLX->setText(QApplication::translate("findRealEstateForm", "X", 0));
        labelBLY->setText(QApplication::translate("findRealEstateForm", "Y", 0));
        labelTRX->setText(QApplication::translate("findRealEstateForm", "X", 0));
        labelTRY->setText(QApplication::translate("findRealEstateForm", "Y", 0));
        labelID->setText(QApplication::translate("findRealEstateForm", "ID", 0));
        buttonFind->setText(QApplication::translate("findRealEstateForm", "Find", 0));
        buttonCancel->setText(QApplication::translate("findRealEstateForm", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class findRealEstateForm: public Ui_findRealEstateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDFORM_H
