#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE
    Application::ix=0;
    ui->AppStack->setCurrentIndex(0);
    ui->AppStack->insertWidget(2,SecondScreen::SecondScreen_current_instance());
 connect(SecondScreen::SecondScreen_current_instance(), SIGNAL(test_1()), this, SLOT(Recieve()));
 connect(this, SIGNAL(ChangeData()), SecondScreen::SecondScreen_current_instance(), SLOT(ChangeData()));
}


Application::~Application()
{
    delete ui;
}

void Application::on_pushButton_clicked()
{

    ui->AppStack->setCurrentIndex(2);
    SecondScreen::SecondScreen_current_instance()->test44=ix;

}

void Application::Recieve()
{
    qDebug()<<"on";
    ui->AppStack->setCurrentIndex(0);



}





void Application::on_add_x_clicked()
{
    Application::ix+=1;
    ui->label->setText(QString::number(ix));
    SecondScreen::SecondScreen_current_instance()->test44=ix;
    emit ChangeData();


}


void Application::on_sub_x_clicked()
{
    Application::ix-=1;
    ui->label->setText(QString::number(ix));
    SecondScreen::SecondScreen_current_instance()->test44=ix;
    emit ChangeData();
}
