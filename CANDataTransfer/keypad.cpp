#include "keypad.h"
#include "ui_keypad.h"

#include "qdebug.h"
KeyPad::KeyPad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyPad)
{

//    Flags
ui->setupUi(this);
cl_status = false;
sh_status = false;
sliderStatus =false;

connect(BK_Timer,SIGNAL(timeout()),this,SLOT(LongBack()));
connect(SP_Timer,SIGNAL(timeout()),this,SLOT(LongSpace()));

QList<QPushButton *> AllButt= KeyPad::findChildren<QPushButton *>();
for(QPushButton *button:AllButt)
{
    connect(button,&QPushButton::clicked,this,&KeyPad::MyFunc);
    qDebug()<<button->objectName();


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
    QString key=clickedButton->objectName().split("_")[1];
    QString txt=clickedButton->text();
    if (sliderStatus){
        sliderStatus=false;
        tempSlider->hide();
        ui->Button_SP->show();
    }

    int len=data.length();
    QString old_data[2]={data.left(Pos),data.right(len-Pos)};

    if(key=="CL" && txt=="")
    {
        cl_status^=true;
       KeyPad::UpperCase(cl_status);
    }
    else if (key=="SH") {
        sh_status^=true;
        KeyPad::ShiftCase(sh_status);
        txt="";
    }
    else if(key=="SP")
    {
txt=" ";
    }
    else if(key=="EN")
    {
        sh_status=false;
        KeyPad::ShiftCase(sh_status);
          KeyPad::kp->hide();
    }
    else if(key=="BK")
    {
        if (old_data[0].length()>0){

        old_data[0]=old_data[0].left(old_data[0].length()-1);
        Pos-=2;}
        else
        {
            Pos=-1;
        }


        }
    data=old_data[0]+txt+old_data[1];
    emit KeyTouched(data,Pos+1);


}

void KeyPad::UpperCase(bool status)
{

    QList<QPushButton *> AllButt= KeyPad::findChildren<QPushButton *>();
    for(QPushButton *button:AllButt)
    {
        if(status==true){
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

void KeyPad::ShiftCase(bool status)
{
    QList<QPushButton *> AllButt= KeyPad::findChildren<QPushButton *>();
    if (status==true){
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

void KeyPad::all_func(QString Data, int pos)
{
    QString data=Data;
    Pos=pos;
    qDebug()<<QString::number(Pos);
}


void KeyPad::LongBack()
{
    BK_Timer->stop();
    if (back_release_status==true)
    {
        data="";
        emit KeyTouched(data,Pos);
    }
}
void KeyPad::LongSpace()
{
    SP_Timer->stop();
    if (SP_release_status==true)
    {
        ui->Button_SP->hide();
        tempSlider= new QSlider(Qt::Horizontal);
        tempSlider->setFixedWidth(ui->Button_SP->width());
        tempSlider->setMinimum(0);
        tempSlider->setMaximum(data.length());
        tempSlider->setSliderPosition(Pos);
        connect(tempSlider,&QSlider::valueChanged,this,&KeyPad::SliderValueChanged);
        ui->horizontalLayout->insertWidget(4,tempSlider);


    }
}

void KeyPad::on_Button_BK_pressed()
{
    back_release_status=true;
    BK_Timer->start(800);
}

void KeyPad::on_Button_BK_released()
{
    back_release_status=false;
}


void KeyPad::on_Button_SP_pressed()
{
    SP_release_status=true;
    SP_Timer->start(800);
}

void KeyPad::on_Button_SP_released()
{
    SP_release_status=false;
}

void KeyPad::SliderValueChanged()
{
    sliderStatus=true;
    Pos=KeyPad::tempSlider->value();
    emit KeyTouched(data,Pos);
}


