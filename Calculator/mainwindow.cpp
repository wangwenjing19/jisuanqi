#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <math.h>
#include <QRegularExpression>
#include <QStack>

#define pi 3.14159265358979323846

// 把度数转化成弧度，用于三角函数
double r2d(double a){return pi*a/180;}

// 普通计算数值与符号链表
QList<int> listOrdinaryInt;     // 数值
QList<char> listOrdinarySym;    // 符号

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("计算器");
    setAttribute(Qt::WA_DeleteOnClose); //关闭窗口时Qt能够自动回收该窗口所占用的资源，有用利于节约内存空间
    setFixedSize(500, 400);   //固定窗口大小

    ui->mainToolBar->setVisible(false);//隐藏工具栏，使界面更美观

    //为输出框设置背景
    ui->labelShowResult->setAutoFillBackground(true);
    QPalette labPal = ui->labelShowResult->palette();
    labPal.setColor(QPalette::Background, QColor(Qt::white));
    ui->labelShowResult->setPalette(labPal);

    initInterface();//在界面显示提示语句

    connect(ui->pBtnStart, SIGNAL(clicked(bool)),this, SLOT(StartBtn()));
    //点击开始计算按钮触发开始计算槽函数
    connect(ui->lineEditInput, SIGNAL(returnPressed()),this, SLOT(StartBtn()));
    //在输入框里按enter键触发开始计算槽函数

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Ordinary()
{
    //若两个数组长度相同，则必定没有输入或者一个符号后没有数字
    if(listOrdinaryInt.length() == listOrdinarySym.length()) {
        ui->lineEditInput->setPlaceholderText("无输入或符号后没有数字，请重新输入");
        return;
    }

    //若其中一个数组为空，则将两个数组都清零
    if(listOrdinaryInt.isEmpty() ||listOrdinarySym.isEmpty()) {
        listOrdinaryInt.clear();
        listOrdinarySym.clear();
        return;
    }

    //在输出框中输出“数值：输入的数字”
    QString print = QString("数值：");
    for(int i = 0; i < listOrdinaryInt.length(); ++i) {
        print += QString(" %1").arg(listOrdinaryInt[i]);//arg()用于填充字符串中的%1
    }

    //在输出框中输出“符号：输入的符号”
    print += "\n符号：";
    for(int i = 0; i < listOrdinarySym.length(); ++i) {
        print += QString(" %1").arg(listOrdinarySym[i]);
    }

    //加减和乘除分开写，且乘除写在前面，因为乘除的优先级高于加减
    // 计算乘除法
    for(int i = 0; i < listOrdinarySym.length(); ++i) {
        if(listOrdinarySym[i] == '*') {
            listOrdinaryInt[i] = listOrdinaryInt[i] * listOrdinaryInt[i+1];
            listOrdinaryInt.removeAt(i+1);//清空第i+1个数值
            listOrdinarySym.removeAt(i);
            --i;//处理完数据后，把数据移出链表，由于后面程序执行下一次的时候会＋＋，会跳过一个数据，所以在循环内--
        }
        else if(listOrdinarySym[i] == '/') {
            listOrdinaryInt[i] = listOrdinaryInt[i] / listOrdinaryInt[i+1];
            listOrdinaryInt.removeAt(i+1);
            listOrdinarySym.removeAt(i);
            --i;
        }

    }

    // 计算加减法
    for(int i = 0; i < listOrdinarySym.length(); ++i) {
        if(listOrdinarySym[i] == '+') {
            listOrdinaryInt[i] = listOrdinaryInt[i] + listOrdinaryInt[i+1];
            listOrdinaryInt.removeAt(i+1);
            listOrdinarySym.removeAt(i);
            --i;
        }
        else if(listOrdinarySym[i] == '-') {
            listOrdinaryInt[i] = listOrdinaryInt[i] - listOrdinaryInt[i+1];
            listOrdinaryInt.removeAt(i+1);
            listOrdinarySym.removeAt(i);
            --i;
        }
    }

    //在输出框中输出“结果是：计算结果”
    print += QString("\n结果是：%1").arg(listOrdinaryInt[0]);

    ui->labelShowResult->setText(print);//在输出框中显示以上

    listOrdinaryInt.clear();
    listOrdinarySym.clear();//置空

    ui->pBtnBin->setEnabled(true);
    ui->pBtnDec->setEnabled(true);
    ui->pBtnHex->setEnabled(true);//按钮可点击
    ui->pBtnSym->setEnabled(false);//按钮不可点击

}

void MainWindow::Logarithm()
{
    QString base = ui->lineEditInput->text();//从输入框中读取字符串到base
    ui->lineEditInput->clear();//清空输入框

    if(base.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("没有输入数据");
        return;
    }

    QStringList list = base.split(",");//将字符串用“,”进行分割，分割后的字符串数组放在list中
    if(list.length() != 2) {
        ui->lineEditInput->setPlaceholderText("缺少底数或真数");
        return;
    }

    // 转化成整数
    QList<int> listInt;
    //外圈循环整个链表，内圈循环单个链表元素是否为10进制，如果是十进制就把这个是放入整数链表
    for(int i = 0; i < list.length(); ++i) {
        QString s = list[i];
        for(int j = 0; j < s.length(); ++j) {
            char ch = s[j].toLatin1();
            if(!(ch >= '0' && ch <= '9')){
                ui->lineEditInput->setPlaceholderText("底数和真数只能输入十进制数");
                return;
            }
        }
        listInt.append(s.toInt());
    }

    double ret = log(listInt[1])/log(listInt[0]);

    //在输出框中输出“以x为底y的对数是z”
    QString print = QString("以%1为底%2的对数是%3")
            .arg(QString::number(listInt[0]))
            .arg(QString::number(listInt[1]))
            .arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::Power()
{
    QString text = ui->lineEditInput->text();//从输入框中读取字符串到text

    QStringList list = text.split("^");//将字符串用“^”进行分割，分割后的字符串数组放在list中
    if(list.length() != 2) {
        ui->lineEditInput->clear();
        ui->lineEditInput->setPlaceholderText("出现未知错误！");
        return;
    }

    QList<int> listInt;
    for(int i = 0; i < list.length(); ++i) {
        QString s = list[i];
        for(int j = 0; j < s.length(); ++j) {
            char ch = s[j].toLatin1();
            if(!(ch >= '0' && ch <= '9')) {
                ui->lineEditInput->setPlaceholderText("只能输入十进制数");
                return;
            }
        }
        listInt.append(s.toInt());
    }

    int ret = pow(listInt[0], listInt[1]);

    QString print = QString("底数:%1 指数:%2 结果:%3")
            .arg(listInt[0]).arg(listInt[1]).arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::Compare()
{
    QString text = ui->lineEditInput->text();//从输入框中读取字符串到text
    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("没有输入数据");
        return;
    }

    QStringList list = text.split(",");//将字符串用“,”进行分割，分割后的字符串数组放在list中
    if(list.length() != 2) {
        ui->lineEditInput->clear();
        ui->lineEditInput->setPlaceholderText("长度异常");
        return;
    }

    QString left = list.at(0);
    QString right = list.at(1);
    //把链表里的数据转成int形
    int a = left.toInt();
    int b = right.toInt();

    QString print;
    print += "原数字是:" + left + "和" + right;
    print += " 较大数是:" + QString::number(a > b? a : b);

    // 求公约数
    int temp;
    //比较两个数的大小，值大的数为a，值小的数为b
    if (a < b) {
        temp = a;
        a = b;
        b = temp;
    }

    temp = a % b;
    if(temp == 0) {
        print+=QString(" 最大公约数是:%1").arg(b);
    }
    else {
        int c = b;
        while(a%b!=0) {
            c = a%b;
            a = b;
            b = c;
        }
        print+=QString(" 最大公约数是:%1").arg(c);
    }

    // 公倍数
    a = left.toInt();
    b = right.toInt();

    if(a<b){
        int d=a;
        a=b;
        b=d;
    }
    for(int i=1; i<=b; i++) {
        if((a*i)%b==0) {
            print+=QString(" 最小公倍数是:%1").arg(a*i);
        }
    }

    ui->labelShowResult->setText(print);
}

void MainWindow::Trigonometric()//三角函数
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    QStringList list = text.split(" ");//将字符串用“ ”进行分割，分割后的字符串数组放在list中
    if(list.length() != 2) {
        ui->lineEditInput->clear();
        qDebug() << list.length();
        ui->lineEditInput->setPlaceholderText("输入不合法，请重新输入");
        return;
    }

    QString left = list.at(0);
    QString right = list.at(1);
    QString s;

    //循环单个链表元素是否为10进制，如果是十进制就把这个是放入整数链表
    for(int i = 0;i<right.length(); ++i) {
        if(right[i].toLatin1() >= '0' &&
                right[i].toLatin1() <= '9') {
            s += right[i];
        }
        else{
            break;
        }
    }

    int num = s.toInt();//把s转成int形
    double ret = 0;


    if(left == QString("sin")) {
        ret = sin(r2d(num));
    }
    else if(left == QString("cos")){
        ret = cos(r2d(num));
    }
    else if(left == QString("tan")) {
        ret = tan(r2d(num));
    }
    else if(left == QString("arcsin")) {
        ret = asin(r2d(num));
    }
    else if(left == QString("arccos")) {
        ret = acos(r2d(num));
    }
    else if(left == QString("arctan")) {
        ret = atan(r2d(num));
    }
    else if(left == QString("sinh")) {
        ret = sinh(r2d(num));
    }
    else if(left == QString("cosh")) {
        ret = cosh(r2d(num));
    }
    else if(left == QString("tanh")) {
        ret = tanh(r2d(num));
    }

    QString print = text;
    print += QString(" = %1").arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::UnaryFirstOrderFunction()//一元一次函数
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    // 转化成整数
    QList<double> listInt;
    int isCSym = 0;   // 常数项是否存在，不存在为0，存在的话1代表+，2代表-
    QString s;

    //把输入的算式中的整数放入链表listInt
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s += text[i];
        }
        else if((ch >= 'a' && ch <= 'z') ||(ch >='A' && ch <= 'Z')) {
            listInt.append(s.toDouble());//把数字字符(s)转成对应类型(double)放入链表
            s.clear();
        }//把前两个数字放入链表
        else if(ch == '+') {
            isCSym = 1;
        }
        else if(ch == '-') {
            isCSym = 2;
        }
        else if(ch == '=') {
            listInt.append(s.toInt());
            s.clear();
        }

        if(i == text.length()-1) {
            listInt.append(s.toDouble());
            s.clear();
        }//将等于号后的数字放入链表
    }

    double r = 0;  // 常数和
    if(isCSym) {
        r = (isCSym == 1 ? listInt[2] - listInt[1] : listInt[2] + listInt[1]);
    }
    else {
        r = listInt[1];
    }

    double ret = r/listInt[0];

    QString print = text;
    print+= QString(" 自变量的值为: %1").arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::UnaryQuadraticFunction()//一元二次函数
{
    QString text = ui->lineEditInput->text();
    QString print = text;
    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("没有输入一元二次函数");
        return;
    }

    QList<int> listInt;
    QList<char> listSym;
    QString s;
    char c = 0;
    // 找出二次项、一次项、常数项、结果的值，并判断是否只有一个未知数
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s += text[i];
        }
        else if(ch == '=') {
            if(!s.isEmpty()) {
                listInt.append(s.toInt());
                s.clear();
            }
        }
        else if((ch >= 'a' && ch <= 'z') ||(ch >= 'A' && ch <= 'Z')) {
            if(c == 0) { c = ch;}
            else if(c != ch) {
                ui->lineEditInput->clear();
                ui->lineEditInput->setPlaceholderText("不止一个自变量");
                return;
            }

            if(!s.isEmpty()) {
                listInt.append(s.toInt());
                s.clear();
            }
        }
        else if(ch == '+' || ch == '-') {
            listSym.append(ch);
            if(!s.isEmpty()) {
                listInt.append(s.toInt());
                s.clear();
            }
        }

        if(i == text.length()-1) {
            listInt.append(s.toInt());
            s.clear();
        }
    }

    if(listInt[1] == 2) {
        listInt.removeAt(1);
    }

    if(listSym[0] == '-') {
        listInt[1] = -listInt[1];
    }

    if(listSym[1] == '-') {
        listInt[2] = -listInt[2];
    }

    int in = listInt[2]-listInt[3];

    int n = listInt[1] * listInt[1] - 4 * listInt[0] * in;

    if(n < 0) {
        print += "\t该函数没有实数根";
        ui->labelShowResult->setText(print);
    }

    double x1 = (-listInt[1] + sqrt(n))/(2*listInt[0]);
    double x2 = (-listInt[1] - sqrt(n))/(2*listInt[0]);

    print += QString("\n实数根1：%1\t实数根2：%2")
            .arg(x1).arg(x2);

    ui->labelShowResult->setText(print);
}

void MainWindow::InverseRatioFunction()//反比例函数
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    QString s;
    double molecule = 0;   // 分子
    double ret = 0;        // 结果
    double result = 0;     // 自变量的值
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s+=text[i];
        }
        else if(ch == '/'){
            if(s.isEmpty()) {
                molecule = 1;
            }
            else {
                molecule = s.toInt();
            }
            s.clear();
        }

        if(i == text.length() - 1) {
            ret = s.toInt();
            s.clear();
        }
    }

    result = molecule / ret;
    QString print = text;
    print += QString(" 自变量的值为：%1").arg(result);

    ui->labelShowResult->setText(print);
}

void MainWindow::ExponentialLogarithmicFunction()//指数对数函数
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    double a = 0;
    double ret = 0;
    double result = 0;
    QString s;
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s += text[i];
        }
        else if(ch == '^') {
            a = s.toInt();
            s.clear();
        }

        if(i == text.length()-1) {
            ret = s.toInt();
            s.clear();
        }
    }
    result = log(ret)/log(a);

    QString print = text;
    print += QString(" 自变量的值是：%1")
            .arg(result);
    ui->labelShowResult->setText(print);
}

void MainWindow::initInterface()//根据计算模式，初始化界面
{
    ui->labelShowResult->clear();
    ui->lineEditInput->clear();
    ui->lineEditInput->setPlaceholderText("");
    ui->labelHelp->setText("");

    // 进制数按钮隐藏
    ui->pBtnBin->setVisible(false);
    ui->pBtnDec->setVisible(false);
    ui->pBtnHex->setVisible(false);
    ui->pBtnSym->setVisible(false);

    //正则表达式
    // 对数
    QRegularExpression regLog("[\\d]{1,}[,]{1}[\\d]{1,}");
    // 幂
    QRegularExpression regPower("[\\d]{1,}[\\^]{1}[\\d]{1,}");
    // 一元一次函数
    QRegularExpression reg("[\\d]*[a-zA-Z]?[+]?[-]?[\\d]{0,10}[=]{1}[\\d]{0,10}");
    // 一元二次函数
    QRegularExpression regQua("[\\d]{1,}[a-zA-Z]{1}[\\^]{1}[2]{1}"
                              "[+ | -]{1}[\\d]{1,}[a-zA-Z]{1,}[+ | -]{1}([\\d]{1,}[=]{1}[\\d]{1,})");
    // 反比例函数
    QRegularExpression regInver("[\\d]{1,}[/]{1}[a-zA-Z]{1}[=]{1}[\\d]{1,}");
    // 指数对数函数
    QRegularExpression regExpLog("[\\d]{1,}[\\^]{1}[a-zA-Z]{1}[=]{1}[\\d]{1,}");

    switch (m_statu) {
    case MyStatuOrdinary:
        ui->statusBar->showMessage(QString("普通计算"));
        ui->lineEditInput->setPlaceholderText("输入数值");
        ui->pBtnBin->setVisible(true);
        ui->pBtnDec->setVisible(true);
        ui->pBtnHex->setVisible(true);
        ui->pBtnSym->setVisible(true);
        ui->pBtnSym->setEnabled(false);
        ui->labelHelp->setText("可输入二进制、十进制、十六进制数(输入超出该进制的字符或符号可能出现未知错误)\n"
                                   "点击按钮输入相应的进制\n"
                                   "点击符号按钮输入符号\n"
                                   "支持+ - * /运算");
        break;
    case MyStatuLog:
        ui->statusBar->showMessage(QString("对数"));
        ui->lineEditInput->setPlaceholderText("输入底数和真数");
        ui->lineEditInput->setValidator(new QRegularExpressionValidator(regLog));
        ui->labelHelp->setText("如果a的x次方等于N（a>0，且a≠1），那么数x叫做以a为底N的对数（logarithm），记作x=log_a N。其中，a叫做对数的底数，N叫做真数。\n"
                               "两个数之间以英文状态下的逗号隔开\n"
                               "示例：要求以2为底8的对数，则输入2,8");
        break;
    case MyStatuPower:
        ui->statusBar->showMessage(QString("幂运算"));
        ui->lineEditInput->setPlaceholderText("输入");
        ui->lineEditInput->setValidator(new QRegularExpressionValidator(regPower));
        ui->labelHelp->setText("只能以n^m形式输入\n"
                               "n:底数  m:指数\n"
                               "示例：10^3 表示10的3次幂");
        break;
    case MyStatuCompare:
        ui->statusBar->showMessage(QString("比较运算"));
        ui->lineEditInput->setPlaceholderText("输入两个数");
        ui->labelHelp->setText("输入的两个数需以英文状态下的逗号隔开");
        break;
    case MyStatuTri:
        ui->statusBar->showMessage(QString("三角函数"));
        ui->lineEditInput->setPlaceholderText("输入三角函数");
        ui->labelHelp->setText("函数类型和度数之间用空格隔开，例：sin 30\n"
                               "支持三角函数：sin cos tan\n"
                               "反三角函数：arcsin arccos arctan\n"
                               "双曲三角函数：sinh cosh tanh");
        break;
    case MyStatuFirst:
        ui->statusBar->showMessage(QString("一元一次函数"));
        ui->lineEditInput->setPlaceholderText("请输入一元一次函数");
        ui->lineEditInput->setValidator(new QRegularExpressionValidator(reg));
        ui->labelHelp->setText("函数形式只能是：ax+b=c\n"
                               "示例：2x+3=5");
        break;
    case MyStatuQuadratic:
        ui->statusBar->showMessage(QString("一元二次函数"));
        ui->lineEditInput->setPlaceholderText("请输入一元二次函数");
        ui->lineEditInput->setValidator(new QRegularExpressionValidator(regQua));
        ui->labelHelp->setText("函数形式只能是：ax^2+bx+c=d\n"
                               "a:二次项系数     b:一次项系数\n"
                               "c:常数项系数\n"
                               "b,c,d均不可省略，如果没有b,c,d要写0");
        break;
    case MyStatuInver:
        ui->statusBar->showMessage(QString("反比例函数"));
        ui->lineEditInput->setPlaceholderText("");
        ui->lineEditInput->setValidator(new QRegularExpressionValidator(regInver));
        ui->labelHelp->setText("函数形式只能是：a/x=y\n"
                               "示例：10/x=2");
        break;
    case MyStatuExpLog:
        ui->statusBar->showMessage(QString("指数对数函数"));
        ui->lineEditInput->setPlaceholderText("请输入指数对数函数");
        ui->lineEditInput->setValidator(new QRegularExpressionValidator(regExpLog));
        ui->labelHelp->setText("函数形式只能是：a^x=b"
                               "示例：10^x=100");
        break;
    default:
        break;
    }


}

void MainWindow::modifyStatu(MyStatus S)//修改计算模式
{
    m_statu = S;
    initInterface();
}

void MainWindow::StartBtn()//开始计算按钮
{
    ui->labelShowResult->clear();

    switch (m_statu) {
    case MyStatuOrdinary:
        Ordinary();
        break;
    case MyStatuLog:
        Logarithm();
        break;
    case MyStatuPower:
        Power();
        break;
    case MyStatuCompare:
        Compare();
        break;
    case MyStatuTri:
        Trigonometric();
        break;
    case MyStatuFirst:
        UnaryFirstOrderFunction();
        break;
    case MyStatuQuadratic:
        UnaryQuadraticFunction();
        break;
    case MyStatuInver:
        InverseRatioFunction();
        break;
    case MyStatuExpLog:
        ExponentialLogarithmicFunction();
        break;
    default:
        break;
    }


}

void MainWindow::pBtnBase(int base)//进制按钮
{
    QString s = ui->lineEditInput->text();
    if(s.isEmpty()) { return; }

    listOrdinaryInt.append(s.toInt(0, base));//把输入的数按指定的进制（十进制）插入链表

    ui->lineEditInput->clear();
    ui->lineEditInput->setPlaceholderText("输入符号");

    ui->pBtnBin->setEnabled(false);
    ui->pBtnDec->setEnabled(false);
    ui->pBtnHex->setEnabled(false);
    ui->pBtnSym->setEnabled(true);
}

void MainWindow::on_pBtnSym_clicked()//符号按钮
{
    QString s = ui->lineEditInput->text();
    if(s.isEmpty()) { return; }

    char ch = 0;
    for(int i = 0;i < s.length(); ++i) {
        ch = s[i].toLatin1();
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            break;
        }
    }

    if(!(ch == '+' || ch == '-' || ch == '*' || ch == '/')) {
        return;
    }

    listOrdinarySym.append(ch);//把符号加入符号链表

    ui->lineEditInput->clear();
    ui->lineEditInput->setPlaceholderText("输入数字");

    ui->pBtnBin->setEnabled(true);
    ui->pBtnDec->setEnabled(true);
    ui->pBtnHex->setEnabled(true);
    ui->pBtnSym->setEnabled(false);

}
