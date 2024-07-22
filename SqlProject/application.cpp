#include "application.h"
#include "ui_application.h"
#include "qdebug.h"
Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE

    db =QSqlDatabase::addDatabase("QSQLITE");
//    db.setConnectOptions();
    db.setDatabaseName("FInally.ini");
    db.open();
    QSqlQuery qry;
    qry.exec("CREATE TABLE IF NOT EXISTS UserData("
"user TEXT,"
"password TEXT)");



}


Application::~Application()
{
    delete ui;
}

void Application::on_pushButton_clicked()
{
    QSqlQuery qry(db);
    qry.prepare("INSERT INTO UserData (user,password) VALUES (:user, :password)");
    qry.bindValue(":user","kyapata");
    qry.bindValue(":password","ok");
    if (qry.exec())
    {
        qDebug()<<"added";
    }
}

void Application::on_pushButton_2_clicked()
{
    QSqlQuery qry("SELECT * FROM UserData WHERE user='kyapata' LIMIT 2 ",db);
    if(qry.exec())
    {
        while(qry.next())
        {

            QString ans=qry.value(0).toString();
            qDebug()<<ans;
        }

    }
}
