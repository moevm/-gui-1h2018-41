#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    initWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    QStringList exampleList = {"123", "test", "asd"};

    for(int i = 0; i < 5; i++)
    {
        QMdiSubWindow* w = new QMdiSubWindow(ui->mdiArea);
        MyListWidget* myList = new MyListWidget(QStringLiteral("List") + QString::number(i), exampleList, w);
        w->setWidget(myList);
        w->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
    for(auto subWindow : ui->mdiArea->subWindowList())
    {
        MyListWidget* list =
                qobject_cast<MyListWidget*>(subWindow->widget());
        qDebug() << list->getCurrentListState();
    }


}
