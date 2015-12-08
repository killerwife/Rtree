/********************************************************************************
** Form generated from reading UI file 'gpsform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPSFORM_H
#define UI_GPSFORM_H

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

class Ui_gpsForm
{
public:
    QLineEdit *lineWidth;
    QLineEdit *lineHeight;
    QLineEdit *lineX;
    QLineEdit *lineY;
    QLabel *labelWidth;
    QLabel *labelHeight;
    QLabel *labelX;
    QLabel *labelY;
    QPushButton *buttonAddCoordinate;
    QPushButton *buttonExitCoordinate;

    void setupUi(QWidget *gpsForm)
    {
        if (gpsForm->objectName().isEmpty())
            gpsForm->setObjectName(QStringLiteral("gpsForm"));
        gpsForm->resize(400, 300);
        lineWidth = new QLineEdit(gpsForm);
        lineWidth->setObjectName(QStringLiteral("lineWidth"));
        lineWidth->setGeometry(QRect(180, 60, 113, 20));
        lineHeight = new QLineEdit(gpsForm);
        lineHeight->setObjectName(QStringLiteral("lineHeight"));
        lineHeight->setGeometry(QRect(180, 100, 113, 20));
        lineX = new QLineEdit(gpsForm);
        lineX->setObjectName(QStringLiteral("lineX"));
        lineX->setGeometry(QRect(180, 140, 113, 20));
        lineY = new QLineEdit(gpsForm);
        lineY->setObjectName(QStringLiteral("lineY"));
        lineY->setGeometry(QRect(180, 180, 113, 20));
        labelWidth = new QLabel(gpsForm);
        labelWidth->setObjectName(QStringLiteral("labelWidth"));
        labelWidth->setGeometry(QRect(40, 60, 47, 13));
        labelHeight = new QLabel(gpsForm);
        labelHeight->setObjectName(QStringLiteral("labelHeight"));
        labelHeight->setGeometry(QRect(40, 100, 47, 13));
        labelX = new QLabel(gpsForm);
        labelX->setObjectName(QStringLiteral("labelX"));
        labelX->setGeometry(QRect(40, 140, 47, 13));
        labelY = new QLabel(gpsForm);
        labelY->setObjectName(QStringLiteral("labelY"));
        labelY->setGeometry(QRect(40, 180, 47, 13));
        buttonAddCoordinate = new QPushButton(gpsForm);
        buttonAddCoordinate->setObjectName(QStringLiteral("buttonAddCoordinate"));
        buttonAddCoordinate->setGeometry(QRect(90, 240, 75, 23));
        buttonExitCoordinate = new QPushButton(gpsForm);
        buttonExitCoordinate->setObjectName(QStringLiteral("buttonExitCoordinate"));
        buttonExitCoordinate->setGeometry(QRect(250, 240, 75, 23));

        retranslateUi(gpsForm);

        QMetaObject::connectSlotsByName(gpsForm);
    } // setupUi

    void retranslateUi(QWidget *gpsForm)
    {
        gpsForm->setWindowTitle(QApplication::translate("gpsForm", "Form", 0));
        labelWidth->setText(QApplication::translate("gpsForm", "Width", 0));
        labelHeight->setText(QApplication::translate("gpsForm", "Height", 0));
        labelX->setText(QApplication::translate("gpsForm", "X", 0));
        labelY->setText(QApplication::translate("gpsForm", "Y", 0));
        buttonAddCoordinate->setText(QApplication::translate("gpsForm", "Add", 0));
        buttonExitCoordinate->setText(QApplication::translate("gpsForm", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class gpsForm: public Ui_gpsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPSFORM_H
