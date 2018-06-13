#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    QMdiSubWindow* w1 = new QMdiSubWindow(ui->mdiArea);
    QListWidget* testList1 = new QListWidget(w1);
    testList1->addItem("123");
    testList1->addItem("test");
    testList1->addItem("smth");
    w1->setWidget(testList1);

    QMdiSubWindow* w2 = new QMdiSubWindow(ui->mdiArea);
    QListWidget* testList2 = new QListWidget(ui->mdiArea);
    testList2->addItem("123");
    testList2->addItem("test");
    testList2->addItem("smth");
    w2->setWidget(testList2);

    QMdiSubWindow* w3 = new QMdiSubWindow(ui->mdiArea);
    QListWidget* testList3 = new QListWidget(ui->mdiArea);
    testList3->addItem("123");
    testList3->addItem("test");
    testList3->addItem("smth");
    w3->setWidget(testList3);

}
