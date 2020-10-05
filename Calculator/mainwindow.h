#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myheader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // 普通计算
    void Ordinary();

    // 对数计算
    void Logarithm();

    // 幂运算
    void Power();

    // 比较运算
    void Compare();

    // 三角函数
    void Trigonometric();

    // 一元一次函数
    void UnaryFirstOrderFunction();

    // 一元二次函数
    void UnaryQuadraticFunction();

    // 反比例函数
    void InverseRatioFunction();

    // 指数对数函数
    void ExponentialLogarithmicFunction();

private:
    Ui::MainWindow *ui;

    MyStatus m_statu  = MyStatuOrdinary;    // 当前处于哪种计算模式

    // 根据计算模式初始化界面
    void initInterface();

    // 修改计算模式
    void modifyStatu(MyStatus S);

signals:
    void showResult();  // 显示结果信号

private slots:
    void on_actionOrdinary_triggered()
    { modifyStatu(MyStatuOrdinary); }

    void on_actionLog_triggered()
    { modifyStatu(MyStatuLog); }

    void on_actionPower_triggered()
    { modifyStatu(MyStatuPower); }

    void on_actionCompare_triggered()
    { modifyStatu(MyStatuCompare); }

    void on_actionTri_triggered()
    { modifyStatu(MyStatuTri); }

    void on_actionFirst_triggered()
    { modifyStatu(MyStatuFirst); }

    void on_actionQuadratic_triggered()
    { modifyStatu(MyStatuQuadratic); }

    void on_actionInver_triggered()
    { modifyStatu(MyStatuInver); }

    void on_actionExpLog_triggered()
    { modifyStatu(MyStatuExpLog); }


    // 开始计算按钮
    void StartBtn();


};

#endif // MAINWINDOW_H
