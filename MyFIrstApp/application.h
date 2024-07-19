#ifndef APPLICATION_H
#define APPLICATION_H
#include <QWidget>
#include <sapcore.h>
#include "keypad.h"
#include "QMessageBox"


namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();


signals:
    void Capitalize(int cl_status);
    void Shift(int sh_status);

private slots:

    void on_lineEdit_selectionChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_2_selectionChanged();

private:
    Ui::Application *ui;
//    KeyPad *kp;
//    int kp_status;


    int cl_status;
    int sh_status;

public slots:
    void getKey(QString key,QString text);
    void LongBack();

};

#endif // APPLICATION_H
