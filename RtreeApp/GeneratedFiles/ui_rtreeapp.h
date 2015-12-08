/********************************************************************************
** Form generated from reading UI file 'rtreeapp.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTREEAPP_H
#define UI_RTREEAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RtreeAppClass
{
public:
    QAction *actionAdd;
    QAction *actionRemove;
    QAction *actionEdit;
    QAction *actionFind;
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menuActions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RtreeAppClass)
    {
        if (RtreeAppClass->objectName().isEmpty())
            RtreeAppClass->setObjectName(QStringLiteral("RtreeAppClass"));
        RtreeAppClass->resize(600, 400);
        actionAdd = new QAction(RtreeAppClass);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionRemove = new QAction(RtreeAppClass);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        actionEdit = new QAction(RtreeAppClass);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        actionFind = new QAction(RtreeAppClass);
        actionFind->setObjectName(QStringLiteral("actionFind"));
        centralWidget = new QWidget(RtreeAppClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(240, 20, 341, 281));
        RtreeAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RtreeAppClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QStringLiteral("menuActions"));
        RtreeAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RtreeAppClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        RtreeAppClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RtreeAppClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RtreeAppClass->setStatusBar(statusBar);

        menuBar->addAction(menuActions->menuAction());
        menuActions->addAction(actionAdd);
        menuActions->addAction(actionRemove);
        menuActions->addAction(actionEdit);
        menuActions->addAction(actionFind);

        retranslateUi(RtreeAppClass);

        QMetaObject::connectSlotsByName(RtreeAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *RtreeAppClass)
    {
        RtreeAppClass->setWindowTitle(QApplication::translate("RtreeAppClass", "RtreeApp", 0));
        actionAdd->setText(QApplication::translate("RtreeAppClass", "add", 0));
        actionRemove->setText(QApplication::translate("RtreeAppClass", "remove", 0));
        actionEdit->setText(QApplication::translate("RtreeAppClass", "edit", 0));
        actionFind->setText(QApplication::translate("RtreeAppClass", "find", 0));
        menuActions->setTitle(QApplication::translate("RtreeAppClass", "actions", 0));
    } // retranslateUi

};

namespace Ui {
    class RtreeAppClass: public Ui_RtreeAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTREEAPP_H
