#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <iostream>

using namespace std;
//Constructor
//Sets the initial conditions, connects buttons with slots
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
        //if the last operand is "=" then clear the screen and display newly pressed button's digit
        }else if(lastOperand=="="){
            lastOperand="";
            number_displayed =pressed_button->text();
            ui->label_3->setText(lastOperand);
        //If an operation button is pressed before, clear the screen and display newly pressed button's digit
        //also set isTypingSecondNum to true to get second input
        }else if(lastOperand!="" && !isTypingSecNum){
            isTypingSecNum=true;
            number_displayed=pressed_button->text();
        //If previous value is 0, clear the screen and display newly pressed button's digit
        }else if(ui->label->text() == "0"){
            number_displayed =pressed_button->text();
        //Else add the newly pressed button's digit next to the previous number on the screen
        }else{
            number_displayed =ui->label->text() + pressed_button->text();
        }
        ui->label->setText(number_displayed);//set the label
    }


}

//When a operation button is pressed this method is called
void MainWindow::operator_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();//currently pressed button

    //If there is no number given before, store this number in stored_number
    if(!firstnum){
         if(isDec)
             stored_number=ui->label->text().toInt();
         else
             stored_number=hexToDec(ui->label->text());//convert hexadecimal to decimal

        firstnum=true; //first num is stored
        //if an operation button is pressed make it last operand
        if(pressed_button->text()=="+" ||pressed_button->text()=="*" || pressed_button->text()=="/" ||pressed_button->text()=="-") lastOperand=pressed_button->text();
        //if "=" button is pressed clear
        else clear();
        ui->label_3->setText(lastOperand);
    }else{
        //if calculator is not in the decimal mode, convert the number on the screen to decimal and call calculate
        if(!isDec){
            calculate(pressed_button->text(), hexToDec(ui->label->text()));

        //call calculate
        }else{
            calculate(pressed_button->text(), ui->label->text().toInt());
        }
    }

}
//When hex, dec or clr button is pressed this method is called
void MainWindow::control_buttons()
{
    QPushButton * pressed_button = (QPushButton*) sender();

    //if hex button is pressed change mode to hex and clear
    if(pressed_button->text() == "Hex"){
        ui->label_2->setText("HEX");
        isDec=false;
        clear();
    //if hex button is pressed change mode to dec and clear
    }else if(pressed_button->text() == "Dec"){
        ui->label_2->setText("DEC");
        isDec=true;
        clear();
    //if clr button is pressed, call clear method
    }else if(pressed_button->text() == "Clr"){
        clear();
    }

}
//this method does operations
//operation: currently pressed buttons operation
//secondNum: current num on the screen, right operand
void MainWindow::calculate(QString operation, int secondNum){

    //if division button is pressed before, do division and store the output value in stored_number
    if(lastOperand=="/" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number = stored_number / secondNum;
        lastOperand="";

    //if subtraction button is pressed before, do subtraction and store the output value in stored_number
    }else if(lastOperand=="-" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number=  stored_number - secondNum;
       lastOperand="";

    //if addition button is pressed before, do addition and store the output value in stored_number
    }else if(lastOperand=="+" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number=stored_number+secondNum;
        lastOperand="";

    //if multiplication button is pressed before, do multiplication and store the output value in stored_number
    }else if(lastOperand=="*" && isTypingSecNum){
        isTypingSecNum=false;
        stored_number= stored_number*secondNum;
        lastOperand="";
    }
    //Display the result in the label
    if(isDec)
        ui->label->setText(QString::number(stored_number));
    else
        ui->label->setText(decToHex(stored_number));

    //If the operation is "=", reset the variables
    if(operation == "="){
        lastOperand="=";
        stored_number=0;
        firstnum=false;
        isTypingSecNum=false;
    //last operation is currently presssed button's operation
    }else{
        lastOperand=operation;
    }
    ui->label_3->setText(lastOperand);

}
//this method changes the calculator to its initial settings
void MainWindow::clear(){
    lastOperand="";
    stored_number=0;
    isTypingSecNum=false;
    firstnum=false;
    ui->label->setText("0");
    ui->label_3->setText(lastOperand);

}
//This method converts hexadecimal number to decimal
//hex: hexadecimal value to be converted
int MainWindow::hexToDec(QString hex){
    int dec = 0;

    bool negate=false; // checks if hex is negative
    int lastInd=0;
    //if hex is negative
    if(hex.at(0) == '-'){
        negate=true;
        lastInd=1;
    }
    for(int i=hex.length()-1;i>=lastInd;i--){
        if(hex.at(i)=='F')
            dec+=15 * pow(16,hex.length()-i-1) ;
        else if(hex.at(i)=='E')
            dec+=14 * pow(16,hex.length()-i-1) ;
        else if(hex.at(i)=='D')
            dec+=13 * pow(16,hex.length()-i-1) ;
        else if(hex.at(i)=='C')
            dec+=12 * pow(16,hex.length()-i-1) ;
        else if(hex.at(i)=='B')
            dec+=11 * pow(16,hex.length()-i-1) ;
        else if(hex.at(i)=='A')
            dec+=10 * pow(16,hex.length()-i-1) ;
        else{
            int temp = hex.at(i).digitValue();
            dec+= temp * pow(16,hex.length()-i-1);
        }

    }
    if(negate) return dec*-1;

    return dec;
}
//This method converts decimal number to hexadecimal
//dec: decimal value to be converted
QString MainWindow::decToHex(int dec){
    if(dec==0) return "0";
    bool negate=false; //checks if dec is negative
    if(dec<0){
        negate = true;
        dec=dec*-1;
    }
    QString hex = "";
    while(dec>0){
        int temp = dec%16;
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
        dec=dec/16;
    }
    if(negate) return "-"+hex;
    return hex;
}
