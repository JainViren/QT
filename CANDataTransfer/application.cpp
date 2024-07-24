#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE

    connect(KeyPad::kp_func(),SIGNAL(KeyTouched(QString,int)),this,SLOT(KeyPadButton(QString,int)));
}


Application::~Application()
{
    delete ui;
}

void Application::drawCircle(QPainter *paint)
{
    paint->drawRect(10,10,100,100);
}

void Application::KeyPadButton(QString txt,int Pos)
{
    ui->lineEdit->setText(txt);
    ui->lineEdit->setCursorPosition(Pos);
}

void Application::on_pushButton_clicked()
{
CAN_Handler3 *can= new CAN_Handler3;

can->sendCAN(0,0,0,0,0,0,0,0,1);

//ui->lineEdit->setText(data);
}

void Application::on_lineEdit_selectionChanged()
{
    KeyPad::kp_func()->show();
    KeyPad::kp_func()->all_func(ui->lineEdit->text(),ui->lineEdit->cursorPosition());



}

void Application::on_plainTextEdit_selectionChanged()
{



}

void Application::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{

    KeyPad::kp_func()->all_func(ui->lineEdit->text(),arg2);

}
