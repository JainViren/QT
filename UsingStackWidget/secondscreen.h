#ifndef SECONDSCREEN_H
#define SECONDSCREEN_H

#include <QWidget>

namespace Ui {
class SecondScreen;
}

class SecondScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SecondScreen(QWidget *parent = nullptr);
    ~SecondScreen();
    static SecondScreen * SecondScreen_instance;
    static SecondScreen * SecondScreen_current_instance();

    int test44;
public slots:
    void ChangeData();
signals:
    void SendingSignals();
    void test_1();

private slots:
    void on_pushButton_released();



    void on_pushButton_clicked();

private:
    Ui::SecondScreen *ui;


};

#endif // SECONDSCREEN_H
