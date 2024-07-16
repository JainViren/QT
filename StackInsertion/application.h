#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <commonscreen.h>

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    int iPageCount;
    int iCurrentPage;
    CommonScreen *cs;

public slots:
    void Home();
    void Next();

signals:
    void ChangeText();
private slots:
    void on_AddScreen0_clicked();

    void on_NextScreen0_clicked();

    void on_NextScreen0_released();

    void on_pushButton_clicked();



    void on_listWidget_clicked(const QModelIndex &index);



    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::Application *ui;

};

#endif // APPLICATION_H
