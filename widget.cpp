#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QtMath>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init_data();
}

Widget::~Widget()
{
    delete ui;

}

void Widget::keyPressEvent(QKeyEvent *event)//键盘按键绑定
{
    switch (event->key()) {
    case Qt::Key_0:
        on_pushButton_0_clicked();
        break;
    case Qt::Key_1:
        on_pushButton_1_clicked();


        break;
    case Qt::Key_2:
        on_pushButton_2_clicked();

        break;
    case Qt::Key_3:
        on_pushButton_3_clicked();


        break;
    case Qt::Key_4:
        on_pushButton_4_clicked();

        break;
    case Qt::Key_5:
        on_pushButton_5_clicked();

        break;
    case Qt::Key_6:
        on_pushButton_6_clicked();

        break;
    case Qt::Key_7:
        on_pushButton_7_clicked();

        break;
    case Qt::Key_8:
        on_pushButton_8_clicked();

        break;
    case Qt::Key_9:
        on_pushButton_9_clicked();

        break;
    case Qt::Key_Asterisk:
        on_pushButton_chen_clicked();
        break;
    case Qt::Key_Plus:
        on_pushButton_jia_clicked();
        break;
    case Qt::Key_Minus:
        on_pushButton_jian_clicked();
        break;
    case Qt::Key_Slash:
        on_pushButton_chu_clicked();
        break;
    case Qt::Key_Enter:
        on_pushButton_deng_clicked();
        break;
    

    }
}

void Widget::init_data()  //数据初始化
{
    num1=0;
    num2=0;
    flag=0;
    flag_content=0;
    flag_2=0;
    flag_2_op=0;
    pingfang=0;
    i=0;// 小数个数
    s="";
    ui->textEdit->setText(s);
}

double Widget::Processing_data(int flag_2_op,double num)// 数据的高阶处理函数
{
    switch (flag_2_op)
    {
        case 1: return (qSin(num));
        case 2:return (qCos(num));
        case 3: return (qTan(num));
        case 4: return(qLn(num));
        case 5:return (qSqrt(num));
        default: return 0;
    }
}

void Widget::readnum(double num,int i)//数据的读取
{

        if(flag==0)
        {
            if(i)
                num1= num1 + num/ pow(10,i);
            else
                num1=num1*10+num;
            if(flag_2)
            {
                num1_p=Processing_data(flag_2_op,num1);
            }
        }
        else
        {
            if(i)
                num2= num2 + num/ pow(10,i);
            else
                num2=num2*10+num;
            if(flag_2)
            {
                num2_p=Processing_data(flag_2_op,num2);
            }
        }
}

void Widget::equal()// 数据的计算
{
    if(flag_2&& pingfang==0)
        num2=num2_p;
    if(flag)
    {
        switch(flag_content)
        {
        case 1:
            result=num1 + num2;break;
        case 2:
            result=num1 - num2;break;
        case 3:
            result=num1 * num2;break;
        case 4:
            result=num1 / num2;break;

        }
    }
    else
    {
        if(flag_2 && pingfang==0) num1=num1_p;
        result=num1;
    }
    init_data();
    num1=result;
    s.setNum(result);
    ui->textEdit->setText(s);
}

void Widget::on_pushButton_1_clicked()//输入数字1
{
    s+="1";
    ui->textEdit->setText(s);
    readnum(1,i);
    if(i) i++;

}

void Widget::on_pushButton_2_clicked()//输入数字2
{
    s+="2";
    ui->textEdit->setText(s);
    readnum(2,i);
    if(i) i++;


}

void Widget::on_pushButton_3_clicked()//输入数字3
{
    s+="3";
    ui->textEdit->setText(s);
    readnum(3,i);
    if(i) i++;


}

void Widget::on_pushButton_4_clicked()//输入数字4
{
    s+="4";
    ui->textEdit->setText(s);
    readnum(4,i);
    if(i) i++;


}

void Widget::on_pushButton_5_clicked()//输入数字5
{
    s+="5";
    ui->textEdit->setText(s);
    readnum(5,i);
    if(i) i++;

}

void Widget::on_pushButton_6_clicked()//输入数字6
{
    s+="6";
    ui->textEdit->setText(s);
    readnum(6,i);
    if(i) i++;

}

void Widget::on_pushButton_7_clicked()//输入数字7
{
    s+="7";
    ui->textEdit->setText(s);
    readnum(7,i);
    if(i) i++;

}

void Widget::on_pushButton_8_clicked()//输入数字8
{
    s+="8";
    ui->textEdit->setText(s);
    readnum(8,i);
    if(i) i++;


}

void Widget::on_pushButton_9_clicked()//输入数字9
{
    s+="9";
    ui->textEdit->setText(s);
    readnum(9,i);
    if(i) i++;


}

void Widget::on_pushButton_0_clicked()//输入数字0
{
    s+="0";
    ui->textEdit->setText(s);
    readnum(0,i);
    if(i) i++;

}

void Widget::on_pushButton_jia_clicked()//输入+号
{
    if(flag==0)
    {
        s+="+";
        ui->textEdit->setText(s);
        flag=1;
        flag_content=1;
        if(flag_2 && pingfang==0)
            num1=num1_p;
        i=0;
        flag_2=0;
        flag_2_op=0;
        pingfang=0;

    }
}

void Widget::on_pushButton_jian_clicked()//输入-号
{
    if(flag==0)
    {
        s+="-";
        ui->textEdit->setText(s);
        flag=1;
        flag_content=2;
        if(flag_2 && pingfang==0)
            num1=num1_p;
        i=0;
        flag_2=0;
        flag_2_op=0;
        pingfang=0;

    }
}

void Widget::on_pushButton_chen_clicked()//输入x号
{
    if(flag==0)
    {
        s+="x";
        ui->textEdit->setText(s);
        flag=1;
        flag_content=3;
        if(flag_2 && pingfang==0)
            num1=num1_p;
        i=0;
        flag_2=0;
        pingfang=0;
        flag_2_op=0;

    }
}

void Widget::on_pushButton_chu_clicked()//输入/号
{
    if(flag==0)
    {
        s+="/";
        ui->textEdit->setText(s);
        flag=1;
        flag_content=4;
        if(flag_2 && pingfang==0)
            num1=num1_p;
        i=0;
        pingfang=0;
        flag_2=0;
        flag_2_op=0;

    }
}

void Widget::on_pushButton_deng_clicked()//等号，进行运算
{
    equal();

}

void Widget::on_pushButton_CE_clicked()//归零
{
    init_data();

}

void Widget::on_pushButton_dian_clicked()//输入小数点
{
    s+=".";
    ui->textEdit->setText(s);
    i=1;

}

void Widget::on_pushButton_pingfang_clicked()//进行平方处理
{
    s+= "²";
    ui->textEdit->setText(s);
     pingfang=1;
    if(flag==0)
    {
        if(flag_2)
            num1=num1_p;
        num1=pow(num1,2);
    }
     else
    {
        if(flag_2)
            num2=num2_p;
        num2=pow(num2,2);
    }

}

void Widget::on_pushButton_sin_clicked()//sin函数
{
    s+="sin";
    ui->textEdit->setText(s);
    flag_2=1;
    flag_2_op=1;

}

void Widget::on_pushButton_cos_clicked()//cos函数
{
    s+= "cos";
    ui->textEdit->setText(s);
    flag_2=1;
    flag_2_op=2;

}

void Widget::on_pushButton_tan_clicked()//tan函数
{
    s+="tan";
    ui->textEdit->setText(s);
    flag_2=1;
    flag_2_op=3;

}

void Widget::on_pushButton_ln_clicked()//ln对数
{
    s+="ln";
    ui->textEdit->setText(s);
    flag_2=1;
    flag_2_op=4;


}

void Widget::on_pushButton_sqrt_clicked()//开根号
{
    s+="Sqrt";
    ui->textEdit->setText(s);
    flag_2=1;
    flag_2_op=5;


}


