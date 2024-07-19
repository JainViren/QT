#include "application.h"
#include "ui_application.h"
#include <QFile>
#include "QTextStream"
#include "qdebug.h"
#include "QFileInfo"
#include "QDir"

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);


    // ADD USER CODE HERE
    connect(this,SIGNAL(StartThread1()),this,SLOT(thread1working()));
    connect(this,SIGNAL(StartThread2()),this,SLOT(thread2working()));
}


Application::~Application()
{
    delete ui;
}



void Application::on_pushButton_clicked()
{
//    QFile MyFile(":/GeneralFile");

//    if (!MyFile.open(QFile::WriteOnly | QFile::Text))
//    {
//        ui->textEdit->setText("not open");
//        return;
//    }
//    QTextStream out(&MyFile);
//    out << "THis is new file";
//    MyFile.flush();
//    MyFile.close();


    QFile MyFile1(":/GeneralFile");

    if (!MyFile1.open(QFile::ReadOnly | QFile::Text ))
    {
        ui->textEdit->setText("not open 1");
        qDebug()<<MyFile1.fileName();
        return;
    }
    QTextStream in(&MyFile1);
    QString mText=in.readAll();
    ui->textEdit->setText(mText);
    qDebug()<<MyFile1.fileName();


    MyFile1.close();



}

void Application::thread1working()
{
    if (thread2.isRunning())
    {
        thread2.terminate();
    }

    thread1.start();
//    thread2.start();

    if (thread1.isRunning()){
        qDebug()<<"THread 1 working";}
    if (thread2.isRunning()){
        qDebug()<<"THread 2 working";}

    if (!thread1.isRunning()){
        qDebug()<<"THread 1 is not  working";}
    if (!thread2.isRunning()){
        qDebug()<<"THread 2 is not working";}


}


void Application::thread2working()
{
    if (thread1.isRunning())
    {
        thread1.terminate();
    }

    thread2.start();

    if (thread2.isRunning()){
        qDebug()<<"THread 2 working";}
    if (thread1.isRunning()){
        qDebug()<<"THread 1 working";}

    if (!thread1.isRunning()){
        qDebug()<<"THread 1 is not  working";}
    if (!thread2.isRunning()){
        qDebug()<<"THread 2 is not working";}

}





void Application::on_pushButton_2_clicked()
{
        emit StartThread1();
}

void Application::on_pushButton_3_clicked()
{
    emit StartThread2();
}

