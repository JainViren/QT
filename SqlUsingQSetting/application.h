#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include "QSettings"

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


private:
    Ui::Application *ui;

};

#endif // APPLICATION_H
