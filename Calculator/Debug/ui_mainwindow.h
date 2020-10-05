/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QAction *actionOrdinary;
    QAction *actionLog;
    QAction *actionPower;
    QAction *actionCompare;
    QAction *actionTri;
    QAction *actionFirst;
    QAction *actionQuadratic;
    QAction *actionInver;
    QAction *actionExpLog;
    QWidget *centralWidget;
    QLabel *labelShowResult;
    QLineEdit *lineEditInput;
    QPushButton *pBtnStart;
    QLabel *labelHelp;
    QMenuBar *menuBar;
    QMenu *menu_H;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(487, 527);
        actionOrdinary = new QAction(MainWindow);
        actionOrdinary->setObjectName(QStringLiteral("actionOrdinary"));
        actionLog = new QAction(MainWindow);
        actionLog->setObjectName(QStringLiteral("actionLog"));
        actionPower = new QAction(MainWindow);
        actionPower->setObjectName(QStringLiteral("actionPower"));
        actionCompare = new QAction(MainWindow);
        actionCompare->setObjectName(QStringLiteral("actionCompare"));
        actionTri = new QAction(MainWindow);
        actionTri->setObjectName(QStringLiteral("actionTri"));
        actionFirst = new QAction(MainWindow);
        actionFirst->setObjectName(QStringLiteral("actionFirst"));
        actionQuadratic = new QAction(MainWindow);
        actionQuadratic->setObjectName(QStringLiteral("actionQuadratic"));
        actionInver = new QAction(MainWindow);
        actionInver->setObjectName(QStringLiteral("actionInver"));
        actionExpLog = new QAction(MainWindow);
        actionExpLog->setObjectName(QStringLiteral("actionExpLog"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelShowResult = new QLabel(centralWidget);
        labelShowResult->setObjectName(QStringLiteral("labelShowResult"));
        labelShowResult->setGeometry(QRect(20, 20, 451, 61));
        labelShowResult->setWordWrap(true);
        lineEditInput = new QLineEdit(centralWidget);
        lineEditInput->setObjectName(QStringLiteral("lineEditInput"));
        lineEditInput->setGeometry(QRect(20, 100, 300, 40));
        pBtnStart = new QPushButton(centralWidget);
        pBtnStart->setObjectName(QStringLiteral("pBtnStart"));
        pBtnStart->setGeometry(QRect(340, 100, 130, 41));
        labelHelp = new QLabel(centralWidget);
        labelHelp->setObjectName(QStringLiteral("labelHelp"));
        labelHelp->setGeometry(QRect(20, 210, 450, 100));
        labelHelp->setWordWrap(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 487, 17));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QStringLiteral("menu_H"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_H->menuAction());
        menu_H->addAction(actionOrdinary);
        menu_H->addAction(actionLog);
        menu_H->addAction(actionPower);
        menu_H->addAction(actionCompare);
        menu_H->addSeparator();
        menu_H->addAction(actionTri);
        menu_H->addAction(actionFirst);
        menu_H->addAction(actionQuadratic);
        menu_H->addAction(actionInver);
        menu_H->addAction(actionExpLog);
        menu_H->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOrdinary->setText(QApplication::translate("MainWindow", "\346\231\256\351\200\232\350\256\241\347\256\227", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionOrdinary->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\350\277\233\345\210\266\350\275\254\346\215\242", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionLog->setText(QApplication::translate("MainWindow", "\345\215\201\350\277\233\345\210\266\346\225\260_\345\257\271\346\225\260\350\277\220\347\256\227", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLog->setToolTip(QApplication::translate("MainWindow", "\345\257\271\346\225\260", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionLog->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\345\257\271\346\225\260\350\256\241\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionPower->setText(QApplication::translate("MainWindow", "\345\215\201\350\277\233\345\210\266\346\225\260_\345\271\202\350\277\220\347\256\227", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionPower->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\345\271\202\350\277\220\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionCompare->setText(QApplication::translate("MainWindow", "\346\257\224\350\276\203\350\277\220\347\256\227", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionCompare->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\346\257\224\350\276\203\350\277\220\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionTri->setText(QApplication::translate("MainWindow", "\344\270\211\350\247\222\345\207\275\346\225\260", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionTri->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\344\270\211\350\247\222\345\207\275\346\225\260\350\256\241\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionFirst->setText(QApplication::translate("MainWindow", "\344\270\200\345\205\203\344\270\200\346\254\241\345\207\275\346\225\260", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionFirst->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\344\270\200\345\205\203\344\270\200\346\254\241\345\207\275\346\225\260\350\256\241\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionQuadratic->setText(QApplication::translate("MainWindow", "\344\270\200\345\205\203\344\272\214\346\254\241\345\207\275\346\225\260", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionQuadratic->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\344\270\200\345\205\203\344\272\214\346\254\241\345\207\275\346\225\260\350\256\241\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionInver->setText(QApplication::translate("MainWindow", "\345\217\215\346\257\224\344\276\213\345\207\275\346\225\260", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionInver->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\345\217\215\346\257\224\344\276\213\345\207\275\346\225\260\350\256\241\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        actionExpLog->setText(QApplication::translate("MainWindow", "\346\214\207\346\225\260\345\257\271\346\225\260\345\207\275\346\225\260", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        actionExpLog->setStatusTip(QApplication::translate("MainWindow", "\351\200\211\346\213\251\350\277\233\350\241\214\346\214\207\346\225\260\345\257\271\346\225\260\345\207\275\346\225\260\350\256\241\347\256\227", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        labelShowResult->setText(QString());
        pBtnStart->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\256\241\347\256\227", Q_NULLPTR));
        labelHelp->setText(QString());
        menu_H->setTitle(QApplication::translate("MainWindow", "\351\200\211\346\213\251(&H)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
