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

    // никогда не делать такие вещи в gui!!! пишу просто для примера

    // parse


    //QString example = "{[{\"list1\": [{\"title1\", \"1\", \"100\"}]}]}";
    QString example = "{\"lists\":["
                      "{\"list1\": [[\"title1\", 1, 900], [\"title2\", 1, 2], [\"title3\", 1, 5]]},"
                      "{\"list2\": [[\"title1\", 1, 100], [\"title2\", 0, 1], [\"title3\", 1, 9]]},"
                      "{\"list3\": [[\"title1\", 1, 12], [\"title2\", 1, 11], [\"title3\", 0, 1]]}"
                      "{\"list4\": [[\"title1\", 0, 44], [\"title3\", 0, 1]]}"
                      "]}";

     Repository repo;
     repo.setContent(example);
    /*QtJson::JsonObject objectFromFile = QtJson::parse(example).toMap();

    qDebug() << "parsed object from file:" << objectFromFile;
    qDebug() << "";

    // create
    QtJson::JsonObject object;
    object["Key1"] = 123;
    object["Key2"] = 456;
    object["Key3"] = "asd";

    QtJson::JsonArray array { "test1", "test2", 1, 2, 4};

    object["arrayExample"] = array;

    qDebug() << "created object:" << object.toStdMap();
    qDebug() << "";
    qDebug() << "created array:" << array.toVector();
    qDebug() << "";

    // serialize (need for save)
    QByteArray data = QtJson::serialize(object);
    qDebug() << "serialized object:" << data;*/

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
