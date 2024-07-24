#include "application.h"
#include "ui_application.h"
#include "QPixmap"
#include "qdebug.h"
#include "QFile"


QLineEdit *SelectedLineEdit=0;

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{

    rectflag=false;
    ui->setupUi(this);
    // ADD USER CODE HERE

    db=QSqlDatabase::addDatabase("QSQLITE");
    QFile dbFile("MyFirstAppDB.db");
    if(!dbFile.exists())
    {
        qDebug()<<"iam here 0";
    db.setDatabaseName("MyFirstAppDB.db");
    db.open();
    QSqlQuery qry;
    qry.exec("CREATE TABLE IF NOT EXISTS userData("
"name TEXT UNIQUE,"
"pass TEXT)"
);
    }
    else{
        qDebug()<<"iam here 1";
    db.setDatabaseName("MyFirstAppDB.db");
        db.open();
    }

    model=new QSqlTableModel(this);
    model->setTable("userData");
    model->select();
    ui->tableView->setModel(model);


    cl_status=0;
    sh_status=0;
    connect(KeyPad::kp_func(),SIGNAL(KeyTouched(QString,QString)),this,SLOT(getKey(QString,QString)));
    connect(this,SIGNAL(Capitalize(int)),KeyPad::kp_func(),SLOT(UpperCase(int)));
    connect(this,SIGNAL(Shift(int)),KeyPad::kp_func(),SLOT(ShiftCase(int)));
    connect(KeyPad::kp_func(),SIGNAL(LongBackSignal()),this,SLOT(LongBack()));






}


Application::~Application()
{
    delete ui;
}

void Application::paintEvent(QPaintEvent *event)
{
if (rectflag)
{
    QPainter fd(this);
    fd.drawRect(QRect(20,20,10,10));
}
}




void Application::on_lineEdit_selectionChanged()
{
    SelectedLineEdit= qobject_cast<QLineEdit *>(sender());

    KeyPad::kp_func();
    KeyPad::kp->show();

}





void Application::on_pushButton_clicked()
{
    rectflag=true;
    update();
    ui->tableView->update();
//if(ui->lineEdit->text()=="userName@gmail.com" && ui->lineEdit_2->text()=="PassKey#123")
//{

//     ui->lineEdit_2->setText("");
//     ui->lineEdit->setText("");
//   int reply= QMessageBox::question(this,"Welcome Box","Hello user you are successfully logged in. Do you want to continue?","Yes","No");
//   qDebug()<<reply;


//}
    QSqlQuery qry;
    qry.prepare("SELECT * FROM userData WHERE name=:name AND pass=:pass");
    qry.bindValue(":name",ui->lineEdit->text());
    qry.bindValue(":pass",ui->lineEdit_2->text());
    qry.exec();
    QList<QString> nameList;
    if(qry.next())
    {
        nameList.append(qry.value(0).toString());
        qDebug()<<qry.value(0).toString();
        qDebug()<<qry.value(1).toString();
         ui->lineEdit_2->setText("");
         ui->lineEdit->setText("");
       int reply= QMessageBox::question(this,"Welcome Box","Hello user you are successfully logged in. Do you want to continue?","Yes","No");

    }
    ui->listWidget->addItem(QString::number(nameList.length()));

}



void Application::getKey(QString key,QString txt)
{
////qDebug()<<key;
//    QLineEdit *SelectedLineEdit= qobject_cast<QLineEdit *>(sender());
//    qDebug()<<SelectedLineEdit;


    if(key=="CL" && txt=="")
    {
        cl_status^=1;
        emit Capitalize(cl_status);
    }
    else if (key=="SH") {
        sh_status^=1;
        qDebug()<<sh_status;
        emit Shift(sh_status);
    }
    else if(key=="SP")
    {
        SelectedLineEdit->setText(SelectedLineEdit->text()+" ");
//    ui->lineEdit->setText(ui->lineEdit->text()+" ");
    }
    else if(key=="EN")
    {
        sh_status=0;
        emit Shift(sh_status);
          KeyPad::kp->hide();

    }
    else if(key=="BK")
    {
        if (ui->lineEdit->text().length()>0){
             SelectedLineEdit->setText(SelectedLineEdit->text().left(SelectedLineEdit->text().length()-1));
//        ui->lineEdit->setText(ui->lineEdit->text().left(ui->lineEdit->text().length()-1));
//    qDebug()<<SelectedLineEdit->cursorPosition();

        }}
    else
    {
        SelectedLineEdit->setCursorPosition(SelectedLineEdit->text().length());
SelectedLineEdit->setText(SelectedLineEdit->text()+txt);


//    ui->lineEdit->setText(ui->lineEdit->text()+txt);

    }


}

void Application::LongBack()
{
//    qDebug()<<SelectedLineEdit;
    SelectedLineEdit->setText("");

}

void Application::on_pushButton_2_clicked()
{
    delete KeyPad::kp;
}


void Application::on_lineEdit_2_selectionChanged()
{
SelectedLineEdit= qobject_cast<QLineEdit *>(sender());
    KeyPad::kp_func();
    KeyPad::kp->show();

}

void Application::on_pushButton_3_clicked()
{
    if(db.open())
    {
        qDebug()<<db.databaseName();

    }
    QSqlQuery qry(db);
    qry.prepare("INSERT INTO userData (name,pass) VALUES (:name, :pass)");
    qry.bindValue(":name",ui->lineEdit->text());
    qry.bindValue(":pass",ui->lineEdit_2->text());
    qry.exec();
    qry.exec("SELECT * FROM userData WHERE name NOT IN ('',' ') AND pass NOT IN (' ','')");

    while(qry.next())
    {
        ui->listWidget->addItem(qry.value(0).toString());
    }
    model->select();
    ui->tableView->update();
}

void Application::on_tableView_doubleClicked(const QModelIndex &index)
{

}
