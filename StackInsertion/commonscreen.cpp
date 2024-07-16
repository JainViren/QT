#include "commonscreen.h"
#include "ui_commonscreen.h"
#include "qdebug.h"



CommonScreen::CommonScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonScreen)
{
    ui->setupUi(this);
    CommonScreen::LabelNumber=0;

}

CommonScreen::~CommonScreen()
{
    delete ui;
}

void CommonScreen::on_pushButton_4_clicked()
{
    emit back();
}

void CommonScreen::on_pushButton_2_clicked()
{
    qDebug() <<"ok";
//   Ui::Application::
    emit next();
}

void CommonScreen::ChangeText()
{
 ui->label->setText(QString::number(LabelNumber));
}
