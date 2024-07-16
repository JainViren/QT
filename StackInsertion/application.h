#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <sapcore.h>
#include <commonscreen.h>
#include <QTreeWidgetItem>
#include <QMessageBox>

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

    void on_radioButton_clicked();

    void on_toolButton_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_commandLinkButton_clicked();

    void on_toolButton_triggered(QAction *arg1);



    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_treeWidget_clicked(const QModelIndex &index);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::Application *ui;

};

#endif // APPLICATION_H
