#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <secondscreen.h>
#include <qdebug.h>

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    int ix;

private slots:
    void on_pushButton_clicked();



    void on_add_x_clicked();

    void on_sub_x_clicked();

private:
    Ui::Application *ui;

public slots:
    void Recieve();


signals:
    void ChangeData();

};

#endif // APPLICATION_H
