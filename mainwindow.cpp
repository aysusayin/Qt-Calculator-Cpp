#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <iostream>

using namespace std;
bool firstnum;
//Constructor
//Sets the initial conditions, connects buttons with actions
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton0,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton1,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton2,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton3,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton4,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton5,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton6,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton7,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton8,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton9,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButtonA,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButtonB,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButtonC,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButtonD,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButtonE,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButtonF,SIGNAL(clicked(bool)),this,SLOT(digit_buttons()));
    connect(ui->pushButton_Plus,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Min,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Mult,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Div,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    connect(ui->pushButton_Dec,SIGNAL(clicked(bool)),this,SLOT(control_buttons()));
    connect(ui->pushButton_Hex,SIGNAL(clicked(bool)),this,SLOT(control_buttons()));
    connect(ui->pushButton_Clr,SIGNAL(clicked(bool)),this,SLOT(control_buttons()));
    connect(ui->pushButton_Eql,SIGNAL(clicked(bool)),this,SLOT(operator_buttons()));
    ui->pushButton_Div->setCheckable(true);
    ui->pushButton_Min->setCheckable(true);
    ui->pushButton_Plus->setCheckable(true);
    ui->pushButton_Mult->setCheckable(true);
    ui->pushButton_Plus->setChecked(false);
    ui->pushButton_Mult->setChecked(false);
    ui->pushButton_Div->setChecked(false);
    ui->pushButton_Min->setChecked(false);

    isDec=true;
    stored_number = 0;
}
//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//When a digit button is pressed this method is called
void MainWindow::digit_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender(); //Button which is pressed
    QString number_displayed; //number which will be displayed on the screen (label)

    //If calculator mode is decimal and user presses hex numbers such as A,B etc. a warning appears on screen and calculations are cleared.
    if(isDec && hex.contains(pressed_button->text().toUpper())){
        clear();
        ui->label->setText("Invalid") ;
    }else{
        //If previous value is invalid, clear the screen and display newly pressed button's digit
        if(ui->label->text() == "Invalid" ){
            number_displayed =pressed_button->text();
            //If an operation button is pressed before, clear the screen and display newly pressed button's digit
            //also set isTypingSecondNum to true to get second input
        }else if((ui->pushButton_Div->isChecked() || ui->pushButton_Min->isChecked() || ui->pushButton_Mult->isChecked()
                  || ui->pushButton_Plus->isChecked()) && !isTypingSecNum){
            isTypingSecNum=true;
            number_displayed=pressed_button->text();
            //If previous value is 0, clear the screen and display newly pressed button's digit
        }else if(ui->label->text() == "0"){
            number_displayed =pressed_button->text();
            //Else set add the newly pressed button's digit next to the previous number on the screen
        }else{
            number_displayed =ui->label->text() + pressed_button->text();
        }
        ui->label->setText(number_displayed);
    }


}

//When a operation button is pressed this method is called
void MainWindow::operator_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();//currently pressed button
    //if calculator is not in the decimal mode, convert the number on the screen to decimal and call calculate
    if(!firstnum){
        stored_number=ui->label->text().toInt();
        firstnum=true;
        pressed_button->setChecked(true);
    }else{
        if(!isDec){
            calculate(pressed_button->text(), hexToDec(ui->label->text()));
            cout<<pressed_button->text().toStdString()<<endl;
            //call calculate
        }else{
            cout<<"pressed "<<pressed_button->text().toStdString()<<endl;
            cout<<"num "<<QString::number( ui->label->text().toInt()).toStdString()<<endl;
            cout<<"stored num "<<QString::number( stored_number).toStdString()<<endl;
            calculate(pressed_button->text(), ui->label->text().toInt());
            cout<<"calculating... "<<QString::number( ui->label->text().toInt()).toStdString()<<endl;
            cout<<"stored num "<<QString::number( stored_number).toStdString()<<endl;
        }
    }



}
//When hex, dec or clr button is pressed this method is called
void MainWindow::control_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();

    //if hex button is pressed change mode to hex
    if(pressed_button->text() == "Hex"){
        ui->label_2->setText("HEX");
        isDec=false;
        //if hex button is pressed change mode to dec
    }else if(pressed_button->text() == "Dec"){
        ui->label_2->setText("DEC");
        isDec=true;
        //if clr button is pressed, call clear method
    }else if(pressed_button->text() == "Clr"){
        clear();
    }

}
//this method does operations
void MainWindow::calculate(QString operation, int secondNum){
    cout<<"HERE ALL"<<endl;

    //if division button is pressed before, do division and store the output value in stored_number
    if(ui->pushButton_Div->isChecked()){
        isTypingSecNum=false;
        stored_number = stored_number / secondNum;
        ui->pushButton_Div->setChecked(false);

        //if subtraction button is pressed before, do subtraction and store the output value in stored_number
    }else if(ui->pushButton_Min->isChecked()){
        isTypingSecNum=false;
        stored_number=  stored_number - secondNum;
        ui->pushButton_Min->setChecked(false);

        //if addition button is pressed before, do addition and store the output value in stored_number
    }else if(ui->pushButton_Plus->isChecked()){
        isTypingSecNum=false;
        stored_number=stored_number+secondNum;
        cout<<"HERE "<<endl;
        ui->pushButton_Plus->setChecked(false);

        //if multiplication button is pressed before, do multiplication and store the output value in stored_number
    }else if(ui->pushButton_Mult->isChecked()){
        isTypingSecNum=false;
        stored_number= stored_number*secondNum;
        ui->pushButton_Mult->setChecked(false);
    }
    if(isDec)
        ui->label->setText(QString::number(stored_number));
    else
        ui->label->setText(decToHex(stored_number));

    if(operation == "+"){
        ui->pushButton_Plus->setChecked(true);
    }else if(operation == "-"){
        ui->pushButton_Min->setChecked(true);
    }else if(operation == "*"){
        ui->pushButton_Mult->setChecked(true);
    }else if(operation == "/"){
        ui->pushButton_Div->setChecked(true);
    }else if(operation == "="){
        stored_number=0;
        firstnum=false;
        isTypingSecNum=false;
    }

}
//this method changes the calculator to its initial settings
void MainWindow::clear(){
    stored_number=0;
    isTypingSecNum=false;
    firstnum=false;
    ui->pushButton_Plus->setChecked(false);
    ui->pushButton_Mult->setChecked(false);
    ui->pushButton_Div->setChecked(false);
    ui->pushButton_Min->setChecked(false);
    ui->label->setText("0");

}
//This method converts hexadecimal number to decimal
int MainWindow::hexToDec(QString hex)
{
    int a = 0;

    for(int i=hex.length()-1;i>=0;i--){
        if(hex.at(i)=='F')
            a+=15 * pow(16,i) ;
        else if(hex.at(i)=='E')
            a+=14 * pow(16,i) ;
        else if(hex.at(i)=='D')
            a+=13 * pow(16,i) ;
        else if(hex.at(i)=='C')
            a+=12 * pow(16,i) ;
        else if(hex.at(i)=='B')
            a+=11 * pow(16,i) ;
        else if(hex.at(i)=='A')
            a+=10 * pow(16,i) ;
        else{
            int temp = hex[i].digitValue();
            a+= temp * pow(16,i);
        }

    }
    return a;
}

QString MainWindow::decToHex(int a){
    QString hex = "";
    while(a>0){
        int temp = a%16;
        if(temp==15)
            hex = "F" +hex;
        else if(temp==14)
            hex = "E" +hex;
        else if(temp==13)
            hex = "D" +hex;
        else if(temp==12)
            hex = "C" +hex;
        else if(temp==11)
            hex = "B" +hex;
        else if(temp==10)
            hex = "A" +hex;
        else{
            hex = QString::number(temp) + hex;
        }
        a=a/16;
    }
    return hex;
}
