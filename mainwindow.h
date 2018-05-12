#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(); //destructor

private:
    Ui::MainWindow *ui; //layout of the program
    int stored_number = 0; //the number that is stored
    bool isDec=true; //calculators mode decimal when its true, hexadecimal otherwise
    bool isTypingSecNum=false; //if program is getting a new number after a operation button is pressed true otherwise false
    bool firstnum=false; //true if a first number is entered false otherwise
    QString lastOperand=""; //stores the last operand
    QString hex = "ABCDEF"; //Characters in Hex Numbers
    void calculate(QString operation, int secondNum); //does calculations
    void clear(); //clears the calculator
    int hexToDec(QString hex); //converts hexadecimal to decimal
    QString decToHex(int dec); //converts decimal to hexadecimal

private slots:

    void digit_buttons(); //when a digit button is pressed
    void operator_buttons(); //when an operation button is pressed
    void control_buttons(); //when clr, hex or dec pressed


};

#endif // MAINWINDOW_H
