#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT



public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    double num1, num2 ,result,num1_p,num2_p;
    QString s;
    int flag;//是否输入了运算符
    int flag_content;//1为加  2为减 3为乘 4为除
    void readnum(double num,int i);
    double Processing_data(int flag_2_op,double num);
    int i;//小数点后i位
    void init_data();
    void equal();//计算
    int flag_2;
    int flag_2_op;// 1为sin 2为cos 3为tan 4为ln 5为开根号
    int pingfang; //是否平方

    void keyPressEvent(QKeyEvent *event);




private slots:



    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_jia_clicked();

    void on_pushButton_jian_clicked();

    void on_pushButton_chen_clicked();

    void on_pushButton_chu_clicked();

    void on_pushButton_deng_clicked();

    void on_pushButton_CE_clicked();

    void on_pushButton_dian_clicked();

    void on_pushButton_pingfang_clicked();

    void on_pushButton_sin_clicked();

    void on_pushButton_cos_clicked();

    void on_pushButton_tan_clicked();

    void on_pushButton_ln_clicked();

    void on_pushButton_sqrt_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
