#include "keypad.h"
#include "ui_keypad.h"

#include "qdebug.h"
KeyPad::KeyPad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyPad)
{
    ui->setupUi(this);
//    connect(ui->Button_1,SIGNAL(clicked(bool)),)
    connect(BK_Timer,SIGNAL(timeout()),this,SLOT(LongBack()));
QList<QPushButton *> AllButt= KeyPad::findChildren<QPushButton *>();
for(QPushButton *button:AllButt)
{
    connect(button,&QPushButton::clicked,this,&KeyPad::MyFunc);

}


}

KeyPad::~KeyPad()
{
    delete ui;

}

KeyPad * KeyPad::kp=0;
KeyPad *KeyPad::kp_func()
{
    if(!KeyPad::kp)
    {
        KeyPad::kp=new  KeyPad;
        kp->move(0,295);
        //ui->setupUi(kp);
        kp->setAttribute(Qt::WA_TranslucentBackground);
    }
    return KeyPad::kp;
}

void KeyPad::MyFunc()
{
    QPushButton *clickedButton=qobject_cast<QPushButton *>(sender());
    QString buttonObject=clickedButton->objectName().split("_")[1];
    QString buttonText=clickedButton->text();
    emit KeyTouched(buttonObject,buttonText);
}

void KeyPad::UpperCase(int status)
{

    QList<QPushButton *> AllButt= KeyPad::findChildren<QPushButton *>();
    for(QPushButton *button:AllButt)
    {
        if(status==1){
        ui->Button_CL->setIcon(QIcon(":/Images/cl2.svg"));
        button->setText(button->text().toUpper());
    }
        else
        {
                ui->Button_CL->setIcon(QIcon(":/Images/cl1.svg"));
                    button->setText(button->text().toLower());
        }
    }


    }

void KeyPad::ShiftCase(int status)
{
    QList<QPushButton *> AllButt= KeyPad::findChildren<QPushButton *>();
    if (status==1){
    for (int i=0;i<AllButt.length();i++)
    {
        ui->Button_CL->setIcon(QIcon());
        AllButt[i]->setText(Shift[i]);
    }}
    else
    {
        for (int i=0;i<AllButt.length();i++)
        {
            ui->Button_CL->setIcon(QIcon(":/Images/cl1.svg"));
            AllButt[i]->setText(Shift1[i]);
        }
    }
}







//QAbstractButton::keyPressEvent(e)
//{
//    qDebug()<<e;
//}






void KeyPad::LongBack()
{
    BK_Timer->stop();
    if (back_release_status==1)
    {
        emit LongBackSignal();
    }
}

void KeyPad::on_Button_BK_pressed()
{
    back_release_status=1;

    BK_Timer->start(800);
}

void KeyPad::on_Button_BK_released()
{
    back_release_status=0;
}
