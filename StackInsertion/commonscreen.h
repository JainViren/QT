#ifndef COMMONSCREEN_H
#define COMMONSCREEN_H

#include <QWidget>

namespace Ui {
class CommonScreen;
}

class CommonScreen : public QWidget
{
    Q_OBJECT

public:
    explicit CommonScreen(QWidget *parent = nullptr);
    ~CommonScreen();

    int LabelNumber;
public slots:
    void ChangeText();
signals:
    void back();
    void next();
private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CommonScreen *ui;
};

#endif // COMMONSCREEN_H
