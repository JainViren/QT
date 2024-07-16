#include "application.h"
#include "ui_application.h"
#include "qdebug.h"
#include "qtreewidget.h"


Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    // ADD USER CODE HERE
    Application::iPageCount = 0;
    Application::iCurrentPage = 0;
    ui->NextScreen0->hide();
     ui->stackedWidget->setCurrentIndex(0);




}


Application::~Application()
{
    delete ui;
}

void Application::on_AddScreen0_clicked()
{
ui->listWidget->verticalScrollBar();
ui->listWidget->horizontalScrollBar();
    ui->NextScreen0->show();


    Application::iPageCount+=1;
   cs= new(CommonScreen);
   cs->LabelNumber=iPageCount;
    ui->stackedWidget->insertWidget(iPageCount,cs);
    ui->listWidget->addItem(QString::number(iPageCount));
    ui->tableWidget->setColumnCount(iPageCount+1);
    ui->tableWidget->setRowCount(iPageCount+1);
    ui->tableWidget->setItem(0,iPageCount,new QTableWidgetItem(QString::number(iPageCount)));


    connect(this,SIGNAL(ChangeText()),cs,SLOT(ChangeText()));
    connect(cs,SIGNAL(back()),this,SLOT(Home()));
    connect(cs,SIGNAL(next()),this,SLOT(Next()));
    emit ChangeText();

}

void Application::on_NextScreen0_clicked()
{
//    Application::iCurrentPage+=1;
//   ui->stackedWidget->setCurrentIndex(1);
}

void Application::on_NextScreen0_released()
{
     Application::iCurrentPage+=1;
    ui->stackedWidget->setCurrentIndex(1);
}

void Application::Home()
{
    Application::iCurrentPage=0;
    ui->stackedWidget->setCurrentIndex(0);

}

void Application::on_pushButton_clicked()
{
    Application::iCurrentPage=0;
   ui->stackedWidget->setCurrentIndex(0);
}

void Application::Next()
{
    Application::iCurrentPage+=1;
    ui->stackedWidget->setCurrentIndex(iCurrentPage);

}


void Application::on_listWidget_clicked(const QModelIndex &index)
{


    ui->stackedWidget->setCurrentIndex(index.row()+1);
}




void Application::on_calendarWidget_clicked(const QDate &date)
{
    ui->label0->setText(date.toString("dd/MM/yyyy"));
}






void Application::on_radioButton_clicked()
{
    if (ui->checkBox->isChecked() && ui->checkBox_2->isChecked())
    {
        ui->stackedWidget->setCurrentIndex(12);
        if (ui->buttonGroup_2->checkedId() == -1)
        {
            qDebug()<<"NO option selected";
        }

    }
}



void Application::on_toolButton_clicked()
{

    ui->treeWidget->setColumnCount(1);
//    ui->treeWidget->setHeaderLabel("Header");
    ui->treeWidget->setHeaderLabel("");

    QTreeWidgetItem *root=new QTreeWidgetItem;
    root->setText(0,"10");
    ui->treeWidget->addTopLevelItem(root);

    QTreeWidgetItem *c1=new QTreeWidgetItem;
    c1->setText(0,"100");
    root->addChild(c1);

    QTreeWidgetItem *c2=new QTreeWidgetItem;
    c2->setText(0,"1000");
    c1->addChild(c2);


}

void Application::on_buttonBox_rejected()
{
    qDebug()<<"Rejected clicked";
}

void Application::on_buttonBox_accepted()
{
    qDebug()<<"Accepted clicked";
}

void Application::on_commandLinkButton_clicked()
{
     qDebug()<<"Command 1 clicked";
}

void Application::on_toolButton_triggered(QAction *arg1)
{

}



void Application::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{

}

void Application::on_treeWidget_clicked(const QModelIndex &index)
{
//    qDebug()<<index.column();
}

void Application::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

    qDebug()<<item->text(column);
//    QString msg;
//    msg="THis is information that you have pressed <br>";
//    msg+=item->text(column);
    QMessageBox::information(this,"Title",("THis is information that you have pressed <br>"+item->text(column)),"ok","matlab?");
int reply=QMessageBox::warning(this,"title","danger","but1","but2","but3");
qDebug()<<reply;
}

