#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initWidgets();

    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    QStringList exampleList = {"123", "test", "asd"};

    QMdiSubWindow* w1 = new QMdiSubWindow(ui->mdiArea);
    MyListWidget* myList1 = new MyListWidget("List 1", exampleList, w1);
    w1->setWidget(myList1);
    QMdiSubWindow* w2 = new QMdiSubWindow(ui->mdiArea);
    MyListWidget* myList2 = new MyListWidget("List 2", exampleList, w2);
    w2->setWidget(myList2);

    QMdiSubWindow* w3 = new QMdiSubWindow(ui->mdiArea);
    MyListWidget* myList3 = new MyListWidget("List 3", exampleList, w3);
    w3->setWidget(myList3);

}
