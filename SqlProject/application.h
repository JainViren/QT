#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <QtSql>

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    QSqlDatabase db;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Application *ui;

};

#endif // APPLICATION_H
