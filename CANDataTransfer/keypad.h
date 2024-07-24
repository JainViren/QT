#ifndef KEYPAD_H
#define KEYPAD_H
#include "QTimer"
#include <QWidget>
#include "QSlider"
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
    QTimer *SP_Timer=new QTimer;



public slots:
    void MyFunc();
    void UpperCase(bool cl_status);
    void ShiftCase(bool sh_status);
    void all_func(QString Data,int pos);

signals:
    void Button_1();
    void KeyTouched(QString text,int Pos);
    void LongBackSignal();


private slots:
    void LongBack();
    void on_Button_BK_pressed();
    void on_Button_BK_released();
    void LongSpace();
    void on_Button_SP_pressed();
    void on_Button_SP_released();

private:
    Ui::KeyPad *ui;
    bool back_release_status;
    bool SP_release_status;
    bool cl_status;
    bool sh_status;
    int Pos;
    int Pos_After_Slider;
    bool sliderStatus;
    void SliderValueChanged();
    QSlider *tempSlider;
    QString data;
    QString Shift1[31]={"q","w","e","r","t","y","u","i","o","p","","","a","s","d","f","g","h","j","k","l","","?123","z","x","c","","v","b","n","m"};
    QString Shift[31]={"1","2","3","4","5","6","7","8","9","0","","{","@","$","#","_","&","-","+","/","*","","ABC","(","<",",","",".",">",")","}"};

};

#endif // KEYPAD_H
