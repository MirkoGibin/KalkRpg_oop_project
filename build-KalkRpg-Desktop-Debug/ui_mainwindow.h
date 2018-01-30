/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionvacca;
    QAction *actionbanana;
    QAction *actionbabab;
    QAction *actionsecondo;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuKalkRPG;
    QMenu *menubanana;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(527, 493);
        actionvacca = new QAction(MainWindow);
        actionvacca->setObjectName(QStringLiteral("actionvacca"));
        actionbanana = new QAction(MainWindow);
        actionbanana->setObjectName(QStringLiteral("actionbanana"));
        actionbabab = new QAction(MainWindow);
        actionbabab->setObjectName(QStringLiteral("actionbabab"));
        actionsecondo = new QAction(MainWindow);
        actionsecondo->setObjectName(QStringLiteral("actionsecondo"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 150, 80, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 527, 22));
        menuKalkRPG = new QMenu(menuBar);
        menuKalkRPG->setObjectName(QStringLiteral("menuKalkRPG"));
        menubanana = new QMenu(menuBar);
        menubanana->setObjectName(QStringLiteral("menubanana"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuKalkRPG->menuAction());
        menuBar->addAction(menubanana->menuAction());
        menuKalkRPG->addSeparator();
        menuKalkRPG->addAction(actionvacca);
        menubanana->addAction(actionbanana);
        menubanana->addAction(actionbabab);
        menubanana->addSeparator();
        menubanana->addSeparator();
        menubanana->addAction(actionsecondo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionvacca->setText(QApplication::translate("MainWindow", "vacca", Q_NULLPTR));
        actionbanana->setText(QApplication::translate("MainWindow", "banana", Q_NULLPTR));
        actionbabab->setText(QApplication::translate("MainWindow", "babab", Q_NULLPTR));
        actionsecondo->setText(QApplication::translate("MainWindow", "secondo", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
        menuKalkRPG->setTitle(QApplication::translate("MainWindow", "KalkRPG", Q_NULLPTR));
        menubanana->setTitle(QApplication::translate("MainWindow", "banana", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
