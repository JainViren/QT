#include "application.h"
#include "ui_application.h"
#include "qdebug.h"
Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE
    ui->label->setText("NLALNO P RAGIJP poersoijniuwetiojhp;hg eajklnbilfg ");
    timer1=new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(t1()));


}


Application::~Application()
{
    delete ui;
}

void Application::t1()
{
    ui->label->setText("Timer Working");
}

void Application::on_spinBox_valueChanged(int arg1)
{
    qDebug()<<arg1;

}

void Application::on_dial_valueChanged(int value)
{
    qDebug()<<value;
    ui->lcdNumber->display(value);
    timer1->start(2000);
}

void Application::on_fontComboBox_currentFontChanged(const QFont &f)
{


    ui->label->setFont(f);

}

void Application::on_comboBox_activated(const QString &arg1)
{
    ui->toolBox->setCurrentIndex(0);
     ui->tabWidget->setCurrentIndex(1);
}

void Application::on_timeEdit_userTimeChanged(const QTime &time)
{
    ui->label->setText(time.toString("hh:mm:ss"));

}

void Application::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->label->setText(date.toString("dd/MM/yyyy"));
}
