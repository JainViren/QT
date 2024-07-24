#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <keypad.h>
#include "qdebug.h"
#include "can_handler3.h"
#include "QPainter"

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    void drawCircle(QPainter *paint);


private:
    Ui::Application *ui;
    CAN_Handler3 *can;

public slots:
    void KeyPadButton(QString,int);
private slots:
    void on_pushButton_clicked();
    void on_lineEdit_selectionChanged();
    void on_plainTextEdit_selectionChanged();
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
};

#endif // APPLICATION_H
