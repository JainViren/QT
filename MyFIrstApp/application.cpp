#include "application.h"
#include "ui_application.h"
#include "QPixmap"
#include "qdebug.h"


QLineEdit *SelectedLineEdit=0;

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE

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




void Application::on_lineEdit_selectionChanged()
{
    SelectedLineEdit= qobject_cast<QLineEdit *>(sender());

    KeyPad::kp_func();
    KeyPad::kp->show();

}





void Application::on_pushButton_clicked()
{
if(ui->lineEdit->text()=="userName@gmail.com" && ui->lineEdit_2->text()=="PassKey#123")
{
   int reply= QMessageBox::information(this,"Welcome Box","Hello user you are successfully logged in. Do you want to continue?","Yes","No");
   qDebug()<<reply;
}
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
