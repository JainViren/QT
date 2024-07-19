#ifndef KEYPAD_H
#define KEYPAD_H
#include "QTimer"
#include <QWidget>

namespace Ui {
class KeyPad;
}

class KeyPad : public QWidget
{
    Q_OBJECT

public:
    explicit KeyPad(QWidget *parent = nullptr);
    ~KeyPad();
    static KeyPad *kp;
    static KeyPad *kp_func();
    QTimer *BK_Timer=new QTimer;



public slots:
    void MyFunc();
    void UpperCase(int cl_status);
    void ShiftCase(int sh_status);

signals:
    void Button_1();
    void KeyTouched(QString key,QString text);
    void LongBackSignal();


private slots:

    void LongBack();

    void on_Button_BK_pressed();

    void on_Button_BK_released();

private:
    Ui::KeyPad *ui;
    int back_release_status=1;
    QString Shift1[31]={"q","w","e","r","t","y","u","i","o","p","","?123","a","s","d","f","g","h","j","k","l","","","z","x","c","","v","b","n","m"};
    QString Shift[31]={"1","2","3","4","5","6","7","8","9","0","","ABC","@","$","#","_","&","-","+","/","*","","{","(","<",",","",".",">",")","}"};

};

#endif // KEYPAD_H
