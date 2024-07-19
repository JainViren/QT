#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <QFile>
#include "QThread"
#include "qdebug.h"


namespace Ui {
class Application;

}

class T1 : public QThread
{
    Q_OBJECT

public:
    void run()  {
        // Implement thread logic here

        // Example: Thread 1 work
        for (int i = 0; i < 2; ++i) {
            qDebug() << "Thread 1 working iteration" << i;
            QThread::msleep(1000); // Simulate work
        }
        qDebug() << "Thread 1 finished";
    }
};

class T2 : public QThread
{
    Q_OBJECT

public:
    void run()  {
        // Implement thread logic here

        // Example: Thread 2 work
        for (int i = 0; i < 100; ++i) {
            qDebug() << "Thread 2 working iteration" << i;
            QThread::msleep(1500); // Simulate work
        }
        qDebug() << "Thread 2 finished";
    }
};




class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
//    QThread thread1;
//    QThread thread2;


public slots:
    void thread1working();
    void thread2working();
signals:
    void StartThread1();
    void StartThread2();

private slots:
    void on_pushButton_clicked();



//    void thread2working();

//    void on_pushButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Application *ui;
    T1 thread1;
    T2 thread2;

};



#endif // APPLICATION_H
