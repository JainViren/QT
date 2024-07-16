#include "application.h"
#include "ui_application.h"
#include "qdebug.h"
#include "qtreewidget.h"


Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE
    Application::iPageCount = 0;
    Application::iCurrentPage = 0;
    ui->NextScreen0->hide();
     ui->stackedWidget->setCurrentIndex(0);




}


Application::~Application()
{
    delete ui;
}

void Application::on_AddScreen0_clicked()
{
ui->listWidget->verticalScrollBar();
ui->listWidget->horizontalScrollBar();
    ui->NextScreen0->show();


    Application::iPageCount+=1;
   cs= new(CommonScreen);
   cs->LabelNumber=iPageCount;
    ui->stackedWidget->insertWidget(iPageCount,cs);
    ui->listWidget->addItem(QString::number(iPageCount));
    ui->tableWidget->setColumnCount(iPageCount+1);
    ui->tableWidget->setRowCount(iPageCount+1);
    ui->tableWidget->setItem(0,iPageCount,new QTableWidgetItem(QString::number(iPageCount)));
    ui->treeWidget->setColumnCount(2);

    connect(this,SIGNAL(ChangeText()),cs,SLOT(ChangeText()));
    connect(cs,SIGNAL(back()),this,SLOT(Home()));
    connect(cs,SIGNAL(next()),this,SLOT(Next()));
    emit ChangeText();

}

void Application::on_NextScreen0_clicked()
{
//    Application::iCurrentPage+=1;
//   ui->stackedWidget->setCurrentIndex(1);
}

void Application::on_NextScreen0_released()
{
     Application::iCurrentPage+=1;
    ui->stackedWidget->setCurrentIndex(1);
}

void Application::Home()
{
    Application::iCurrentPage=0;
    ui->stackedWidget->setCurrentIndex(0);

}

void Application::on_pushButton_clicked()
{
    Application::iCurrentPage=0;
   ui->stackedWidget->setCurrentIndex(0);
}

void Application::Next()
{
    Application::iCurrentPage+=1;
    ui->stackedWidget->setCurrentIndex(iCurrentPage);

}


void Application::on_listWidget_clicked(const QModelIndex &index)
{


    ui->stackedWidget->setCurrentIndex(index.row()+1);
}




void Application::on_calendarWidget_clicked(const QDate &date)
{
    ui->label0->setText(date.toString("dd"));
}
