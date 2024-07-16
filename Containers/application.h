#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <qfont.h>
namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_dial_valueChanged(int value);

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_activated(const QString &arg1);

    void on_timeEdit_userTimeChanged(const QTime &time);


    void on_dateEdit_userDateChanged(const QDate &date);

private:
    Ui::Application *ui;

};

#endif // APPLICATION_H
