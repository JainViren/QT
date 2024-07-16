#include "secondscreen.h"
#include "ui_secondscreen.h"


SecondScreen * SecondScreen::SecondScreen_instance=0;
SecondScreen * SecondScreen::SecondScreen_current_instance()
{
    if (!SecondScreen::SecondScreen_instance)
    {
        SecondScreen::SecondScreen_instance = new SecondScreen;
    }
    return SecondScreen::SecondScreen_instance;
}

SecondScreen::SecondScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondScreen)
{
    ui->setupUi(this);

}

SecondScreen::~SecondScreen()
{
    delete ui;
}

void SecondScreen::on_pushButton_clicked()
{
    ui->label->setText("wohoo");
    emit SendingSignals();

}

void SecondScreen::on_pushButton_released()
{

    emit test_1();
}

void SecondScreen::ChangeData()
{
    ui->label->setText(QString::number(test44));
}
