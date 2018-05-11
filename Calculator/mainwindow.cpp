#include "mainwindow.h"
#include "ui_mainwindow.h"

//Constructor
//Sets the initial conditions, connects buttons with actions
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
    connect(ui->pushButton_Dec,SIGNAL(released()),this,SLOT(control_buttons()));
    connect(ui->pushButton_Hex,SIGNAL(released()),this,SLOT(control_buttons()));
    connect(ui->pushButton_Clr,SIGNAL(released()),this,SLOT(control_buttons()));
    connect(ui->pushButton_Clr,SIGNAL(released()),this,SLOT(operator_buttons()));
    ui->pushButton_Div->setCheckable(true);
    ui->pushButton_Min->setCheckable(true);
    ui->pushButton_Plus->setCheckable(true);
    ui->pushButton_Mult->setCheckable(true);
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
                 || ui->pushButton_Plus->isChecked()) & !isTypingSecNum){
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
    if(!isDec){
        calculate(pressed_button, hexToDec(ui->label->text()));
    //call calculate
    }else{
        calculate(pressed_button, ui->label->text().toLong());
    }
    //If it is not the equals button, set button check o indicate that it is pressed
    if(pressed_button->text() != "=")
        pressed_button->setChecked(true);
    //If its the equals button, clear the stored number
    else
        stored_number=0;
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
MainWindow::calculate(QPushButton pressed_button, long secondNum){
    //if division button is pressed before, do division and store the output value in stored_number
    if(ui->pushButton_Div->isChecked()){
        if(pressed_button.text() == "=")isTypingSecNum=false;
        stored_number/=secondNum;
        if(isDec)
            ui->label->setText(""+stored_number);
        else
            ui->label->setText(decToHex(stored_number));
        ui->pushButton_Div->setChecked(false);
    //if subtraction button is pressed before, do subtraction and store the output value in stored_number
    }else if(ui->pushButton_Min->isChecked()){
        if(pressed_button.text() == "=")isTypingSecNum=false;
        stored_number-=secondNum;
        if(isDec)
            ui->label->setText(""+stored_number);
        else
            ui->label->setText(decToHex(stored_number));
        ui->pushButton_Min->setChecked(false);
    //if addition button is pressed before, do addition and store the output value in stored_number
    }else if(ui->pushButton_Plus->isChecked()){
        if(pressed_button.text() == "=")isTypingSecNum=false;
        stored_number+=secondNum;
        if(isDec)
            ui->label->setText(""+stored_number);
        else
            ui->label->setText(decToHex(stored_number));
        ui->pushButton_Plus->setChecked(false);
    //if multiplication button is pressed before, do multiplication and store the output value in stored_number
    }else if(ui->pushButton_Mult->isChecked()){
        if(pressed_button.text() == "=")isTypingSecNum=false;
        stored_number*=secondNum;
        if(isDec)
            ui->label->setText(""+stored_number);
        else
            ui->label->setText(decToHex(stored_number));
        ui->pushButton_Mult->setChecked(false);
    //if no operation button is pressed, store the input number in stored_number
    }else{
        stored_number=secondNum;
    }
}
//this method changes the calculator to its initial settings
MainWindow::clear(){
    stored_number=0;
    isTypingSecNum=false;
    ui->pushButton_Plus->setChecked(false);
    ui->pushButton_Mult->setChecked(false);
    ui->pushButton_Div->setChecked(false);
    ui->pushButton_Min->setChecked(false);
    ui->label->setText(0);
}
//This method converts hexadecimal number to decimal
long MainWindow::hexToDec(QString hex)
{
    reverse(hex.begin(),hex.end());
    char hexa[hex.length()];
    strcpy(hexa,hex.c_str());
    long a = 0;

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
QString MainWindow::DoubleToHex(long a)
{
    QString hex = "";
    while(a>0){
        long temp = a%16;
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
