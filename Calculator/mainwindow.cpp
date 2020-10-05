#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <math.h>
#include <QRegularExpression>
#include <QStack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("计算器");
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(500, 400);

    ui->mainToolBar->setVisible(false);
    ui->labelShowResult->setAutoFillBackground(true);
    QPalette labPal = ui->labelShowResult->palette();
    labPal.setColor(QPalette::Background, QColor(Qt::white));
    ui->labelShowResult->setPalette(labPal);

    initInterface();

    connect(ui->pBtnStart, SIGNAL(clicked(bool)),
            this, SLOT(StartBtn()));
    connect(ui->lineEditInput, SIGNAL(returnPressed()),
            this, SLOT(StartBtn()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Ordinary()
{
    QString text = ui->lineEditInput->text();
    QString print = text;   // 输出
    print += "\t转化成十进制分别是：";

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("没有输入算式");
        return;
    }

    text = text.simplified();   // 去除空格

    QList<int> listInt;
    QStringList listStr;        // 数值字符
    QList<char> listSym;        // 符号存储
    QString s;
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if((ch >= '0' && ch <= '9') ||
                (ch >= 'a' && ch <= 'f') ||
                (ch >= 'A' && ch <= 'F')) {
            s += text[i];
        }else if(ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/') {
            listStr.append(s);
            s.clear();
            listSym.append(ch);
        }

        if(i == text.length()-1) {
            listStr.append(s);
            s.clear();
        }
    }

    // 转化
    for(int i = 0; i < listStr.length(); ++i) {
        QString str = listStr[i];
        int max = 2;
        for(int j = 0; j < str.length(); ++j) {
            char ch = str[j].toLatin1();
            if(ch >= '0' && ch <= '1') {
                max = 2>max?2:max;
            }else if(ch >= '2' && ch <= '9') {
                max = 10>max?10:max;
            }else if((ch >= 'a' && ch <= 'f') ||
                     (ch >= 'A' && ch <= 'Z')) {
                max = 16>max?16:max;
            }
        }

        listInt.append(str.toInt(0, max));
        print += QString("  %1").arg(str.toInt(0, max));
    }


    // 计算乘除法
    for(int i = 0; i < listSym.length(); ++i) {
        if(listSym[i] == '*') {
            listInt[i] = listInt[i] * listInt[i+1];
            listInt.removeAt(i+1);
            listSym.removeAt(i);
            --i;
        }else if(listSym[i] == '/') {
            listInt[i] = listInt[i] / listInt[i+1];
            listInt.removeAt(i+1);
            listSym.removeAt(i);
            --i;
        }

    }

    // 计算加减法
    for(int i = 0; i < listSym.length(); ++i) {
        if(listSym[i] == '+') {
            listInt[i] = listInt[i] + listInt[i+1];
            listInt.removeAt(i+1);
            listSym.removeAt(i);
            --i;
        }else if(listSym[i] == '-') {
            listInt[i] = listInt[i] - listInt[i+1];
            listInt.removeAt(i+1);
            listSym.removeAt(i);
            --i;
        }
    }

    print += QString(" 结果是 %1")
            .arg(listInt[0]);

    ui->labelShowResult->setText(print);
}

void MainWindow::Logarithm()
{
    QString base = ui->lineEditInput->text();
    if(base.isEmpty()) {
        ui->lineEditInput->clear();
        ui->lineEditInput->setPlaceholderText("没有输入数据");
        return;
    }

    for(int i = 0; i < base.length(); ++i) {
        char c = base[i].toLatin1();
        if(!(c >= '0' && c <= '9')) {
            ui->lineEditInput->clear();
            ui->lineEditInput->setPlaceholderText("请输入十进制数");
            return;
        }
    }

    int num = base.toInt();

    if(num < 1) {
        ui->lineEditInput->clear();
        ui->lineEditInput->setPlaceholderText("负数和0没有对数");
    }

    double ret = log10(num);

    QString print = QString("以10为底%1的对数是%2")
            .arg(QString::number(num))
            .arg(QString::number(ret));

    ui->labelShowResult->setText(print);
}

void MainWindow::Power()
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("没有输入数据");
        return;
    }

    for(int i = 0; i < text.length(); ++i) {
        char c = text[i].toLatin1();
        if(!(c >= '0' && c <= '9')) {
            ui->lineEditInput->clear();
            ui->lineEditInput->setPlaceholderText("请输入十进制数");
            return;
        }
    }

    int num = text.toInt();
    double ret = pow(10, num);

    QString print = QString("底数:10 指数:%1 结果:%2")
            .arg(num).arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::Compare()
{
    QString text = ui->lineEditInput->text();
    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("没有输入数据");
        return;
    }

    QStringList list = text.split(",");
    if(list.length() != 2) {
        ui->lineEditInput->clear();
        ui->lineEditInput->setPlaceholderText("长度异常");
        return;
    }

    QString left = list.at(0);
    QString right = list.at(1);
    int a = left.toInt();
    int b = right.toInt();

    QString print;
    print += "原数字是:" + left + "和" + right;
    print += "较大数是:" + QString::number(a > b? a : b);

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
    }else {
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
    //比较两个数的大小，值大的数为a，值小的数为b
    if (a < b) {
        temp = a;
        a = b;
        b = temp;
    }

    for(int i=a; i>0; i--) {  /*从大数开始寻找满足条件的自然数*/
        if(i%a==0 && i%b==0) {
            print+=QString(" 最小公倍数是:%1").arg(i);
        }
    }

    ui->labelShowResult->setText(print);
}

void MainWindow::Trigonometric()
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    QStringList list = text.split(" ");
    if(list.length() != 2) {
        ui->lineEditInput->clear();
        qDebug() << list.length();
        ui->lineEditInput->setPlaceholderText("输入不合法，请重新输入");
        return;
    }

    QString left = list.at(0);
    QString right = list.at(1);
    QString s;

    for(int i = 0;i<right.length(); ++i) {
        if(right[i].toLatin1() >= '0' &&
                right[i].toLatin1() <= '9') {
            s += right[i];
        }else{
            break;
        }
    }

    int num = s.toInt();
    double ret = 0;


    if(left == QString("sin")) {
        ret = sin(num);
    }else if(left == QString("cos")){
        ret = cos(num);
    }else if(left == QString("tan")) {
        ret = tan(num);
    }else if(left == QString("arcsin")) {
        ret = asin(num);
    }else if(left == QString("arccos")) {
        ret = acos(num);
    }else if(left == QString("arctan")) {
        ret = atan(num);
    }else if(left == QString("sinh")) {
        ret = sinh(num);
    }else if(left == QString("cosh")) {
        ret = cosh(num);
    }else if(left == QString("tanh")) {
        ret = tanh(num);
    }

    QString print = text;
    print += QString(" = %1").arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::UnaryFirstOrderFunction()
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }


    QList<int> listInt;
    int isCSym = 0;   // 常数项是否存在，不存在为0，存在+_1  -_2
    QString s;
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s += text[i];
        }else if((ch >= 'a' && ch <= 'z') ||
                 (ch >='A' && ch <= 'Z')) {
            listInt.append(s.toInt());
            s.clear();
        }else if(ch == '+') {
            isCSym = 1;
        }else if(ch == '-') {
            isCSym = 2;
        }else if(ch == '=') {
            listInt.append(s.toInt());
            s.clear();
        }

        if(i == text.length()-1) {
            listInt.append(s.toInt());
            s.clear();
        }
    }

    int r = 0;  // 常数和
    if(isCSym) {
        r = (isCSym == 1 ? listInt[2] - listInt[1] : listInt[2] + listInt[1]);
    }else {
        r = listInt[1];
    }

    int ret = r/listInt[0];

    QString print = text;
    print+= QString(" 自变量的值为: %1").arg(ret);

    ui->labelShowResult->setText(print);
}

void MainWindow::UnaryQuadraticFunction()
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
        }else if(ch == '=') {
            if(!s.isEmpty()) {
                listInt.append(s.toInt());
                s.clear();
            }
        }else if((ch >= 'a' && ch <= 'z') ||
                 (ch >= 'A' && ch <= 'Z')) {
            if(c == 0) { c = ch; }
            else if(c != ch) {
                ui->lineEditInput->clear();
                ui->lineEditInput->setPlaceholderText("不止一个自变量");
                return;
            }

            if(!s.isEmpty()) {
                listInt.append(s.toInt());
                s.clear();
            }
        }else if(ch == '+' || ch == '-') {
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

    int x1 = (-listInt[1] + sqrt(n))/(2*listInt[0]);
    int x2 = (-listInt[1] - sqrt(n))/(2*listInt[0]);

    print += QString("\t实数根1：%1\t实数根2：%2")
            .arg(x1).arg(x2);

    ui->labelShowResult->setText(print);
}

void MainWindow::InverseRatioFunction()
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    QString s;
    int molecule = 0;   // 分子
    int ret = 0;        // 结果
    int result = 0;     // 自变量的值
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s+=text[i];
        }else if(ch == '/'){
            if(s.isEmpty()) {
                molecule = 1;
            }else {
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

void MainWindow::ExponentialLogarithmicFunction()
{
    QString text = ui->lineEditInput->text();

    if(text.isEmpty()) {
        ui->lineEditInput->setPlaceholderText("请输入数据");
        return;
    }

    int a = 0;
    int ret = 0;
    int result = 0;
    QString s;
    for(int i = 0; i < text.length(); ++i) {
        char ch = text[i].toLatin1();
        if(ch >= '0' && ch <= '9') {
            s += text[i];
        }else if(ch == '^') {
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

void MainWindow::initInterface()
{
    ui->labelShowResult->clear();
    ui->lineEditInput->clear();
    ui->lineEditInput->setPlaceholderText("");
    ui->labelHelp->setText("");

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
        ui->lineEditInput->setPlaceholderText("输入算式");
        ui->labelHelp->setText("可输入二进制、十进制、十六进制数(输入其他数字可能出现未知错误)\n"
                                   "由于进制转化问题，10会被转成10进制数2\n"
                                   "支持+ - * /运算");
        break;
    case MyStatuLog:
        ui->statusBar->showMessage(QString("对数"));
        ui->lineEditInput->setPlaceholderText("输入真数");

        break;
    case MyStatuPower:
        ui->statusBar->showMessage(QString("幂运算"));
        ui->lineEditInput->setPlaceholderText("输入指数");

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
                               "由于结果是整数，可能出现小的误差");
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

void MainWindow::modifyStatu(MyStatus S)
{
    m_statu = S;
    initInterface();
}

void MainWindow::StartBtn()
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

