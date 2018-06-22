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
    auto toolbar = ui->mainToolBar;
    removeToolBar(toolbar);
}

void MainWindow::on_openPushButton_clicked()
{
    on_actionOpen_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(0, "Open File", "", "*.json");
    QFile file(path);
    if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
    {
        QString content = file.readAll();
        file.close();
        repo.setContent(content);
    }

    QList<RandomItemList> list = repo.getContent();

    QList< QList<QMap<QString, QString> > > lists;
    for(int i = 0; i < list.size(); i++)
    {
        QList< QMap<QString, QString> > listItems;
        for(size_t j = 0; j < list[i].size(); j++)
        {
            RandomItem item = list[i].get(j);

            QMap<QString, QString> itemMap;
            itemMap.insert("title", item.getTitle());
            itemMap.insert("count", QString::number(item.getCount()));
            itemMap.insert("selected", QString::number(item.getSelected()));

            listItems.push_back(itemMap);
        }
        lists.push_back(listItems);
    }


    for(int i = 0; i < lists.size(); i++)
    {
        QMdiSubWindow* w = new QMdiSubWindow(ui->mdiArea);
        MyListWidget* myList = new MyListWidget(QStringLiteral("List") + QString::number(i), lists[i], w);
        w->setWidget(myList);
        w->show();
    }
}

void MainWindow::on_randomizePushButton_clicked()
{
    QList<QList<QMap<QString, QString> > > listsStates;
    for(auto subWindow : ui->mdiArea->subWindowList())
    {
        MyListWidget* list =
                qobject_cast<MyListWidget*>(subWindow->widget());
        listsStates.push_back(list->getCurrentListState());
    }
    Randomizer r;
    r.setLists(listsStates);
    QStringList items = r.start();
    ui->listWidget->clear();
    ui->listWidget->addItems(items);
}
