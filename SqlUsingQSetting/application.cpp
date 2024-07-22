#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE
        QSettings Database("DatabaseUsingSetting.ini", QSettings::IniFormat);
        QString user1 = Database.value("user/User1Name").toString();
        QString pass1 = Database.value("user/User1Ps").toString();

        if (user1 == ""){
            Database.setValue("user/User1Name", "viren");
            Database.sync();
            Database.setValue("user/User1Ps", "passkey");
            Database.sync();
        }

}


Application::~Application()
{
    delete ui;
}


