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
    long stored_number = 0; //the number that is stored
    bool isDec=true; //calculators mode decimal when its true, hexadecimal otherwise
    bool isTypingSecNum=false; //if program is getting a new number after a operation button is pressed true otherwise false
    QString hex = "ABCDEF"; //Characters in Hex Numbers

    void calculate(QPushButton pressed_button, long secondNum); //does calculations
    void clear(); //clears the calculator
private slots:

    void digit_buttons(); //when a digit button is pressed
    void operator_buttons(); //when an operation button is pressed
    void control_buttons(); //when clr, hex or dec pressed
    long hexToDec(QString hex); //converts hexadecimal to decimal
    QString decToHex(long dec); //converts decimal to hexadecimal

};

#endif // MAINWINDOW_H
