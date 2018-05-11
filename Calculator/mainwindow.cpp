#include "mainwindow.h"
#include "ui_mainwindow.h"
double stored_number = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton0,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton1,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton2,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton3,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton4,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton5,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton6,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton7,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton8,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton9,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButtonA,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButtonB,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButtonC,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButtonD,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButtonE,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButtonF,SIGNAL(released()),this,SLOT(digit_buttons()));
    connect(ui->pushButton_Plus,SIGNAL(released()),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Min,SIGNAL(released()),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Mult,SIGNAL(released()),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Div,SIGNAL(released()),this,SLOT(operator_buttons()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();
    double number_displayed =(ui->label->text() + pressed_button->text()).toDouble();

    QString display = QString::number(number_displayed,'g',10); // 10 kaç basamak gösterileceği

    ui->label->setText(display) ;
}

void MainWindow::operator_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();


}

double MainWindow::HexToDouble(string hex)
{
    reverse(hex.begin(),hex.end());
    char hexa[hex.length()];
    strcpy(hexa,hex.c_str());
    double a = 0;

    for(int i=0;i<hex.length();i++){
        if(hexa[i]=='F')
            a+=15 * pow(16,i) ;
        else if(hexa[i]=='E')
            a+=14 * pow(16,i) ;
        else if(hexa[i]=='D')
            a+=13 * pow(16,i) ;
        else if(hexa[i]=='C')
            a+=12 * pow(16,i) ;
        else if(hexa[i]=='B')
            a+=11 * pow(16,i) ;
        else if(hexa[i]=='A')
            a+=10 * pow(16,i) ;
        else{
            int temp = hex[i] -'0';
            a+= temp * pow(16,i);
        }

    }
    return a;
}
