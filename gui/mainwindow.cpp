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
    toolbar->addAction(ui->actionOpen);
    toolbar->addAction(ui->actionSave);
    toolbar->addAction(ui->actionAdd_List);
    toolbar->addAction(ui->actionRemove_List);
    toolbar->addAction(ui->actionClear);
}

void MainWindow::clear()
{
    for(auto subWindow : ui->mdiArea->subWindowList())
    {
        subWindow->deleteLater();
    }
    m_repo.clear();
}

QList<ListState> MainWindow::toGuiFormat(QList<RandomItemList> lists)
{
    QList<ListState> listWidgetsStates;
    for(int i = 0; i < lists.size(); i++)
    {
        ListState listWidgetState;
        for(size_t j = 0; j < lists[i].size(); j++)
        {
            RandomItem item = lists[i].get(j);
            ItemState itemWidget;
            itemWidget.title = item.getTitle();
            itemWidget.count = item.getCount();
            itemWidget.selected = item.getSelected();

            listWidgetState.listName = lists[i].title();
            listWidgetState.needToFind = lists[i].getNeedToFind();
            listWidgetState.listItems.push_back(itemWidget);
        }
        listWidgetsStates.push_back(listWidgetState);
    }
    return listWidgetsStates;
}

QList<RandomItemList> MainWindow::toModelFormat(QList<ListState> listsStates)
{
    QList<RandomItemList> lists;
    for(auto listState : listsStates)
    {
        RandomItemList list(listState.listName);
        list.setNeedToFind(listState.needToFind);
        for(auto itemState : listState.listItems)
        {
            RandomItem item;
            item.setTitle(itemState.title);
            item.setCount(itemState.count);
            item.setSelected(itemState.selected);
            list.add(item);
        }
        lists.push_back(list);
    }
    return lists;
}

void MainWindow::on_actionOpen_triggered()
{
    clear();

    OpenFile open("");
    m_repo.setContent(open.start());
    m_repo.setFilePath(open.path());

    QList<ListState> lists = toGuiFormat(m_repo.getContent());
    for(auto list : lists)
    {
        QMdiSubWindow* w = new QMdiSubWindow(ui->mdiArea);
        MyListWidget* myList = new MyListWidget(list, w);
        w->setWidget(myList);
        w->show();
    }
}

void MainWindow::on_randomizePushButton_clicked()
{
    QList<ListState> listsStates;
    for(auto subWindow : ui->mdiArea->subWindowList())
    {
        MyListWidget* list =
                qobject_cast<MyListWidget*>(subWindow->widget());
        listsStates.push_back(list->getCurrentListState());
    }

    m_repo.setContent(toModelFormat(listsStates));

    QList<RandomItemList> lists = m_repo.getContent();

    /*for(int i = 0; i < lists.size(); i++)
    {
        for(int j = 0; j < lists[i].size(); j++)
        {
            RandomItem item = lists[i].get(j);
            qDebug() << item.getTitle() << item.getSelected() << item.getCount();
        }
    }*/

    Randomizer r;
    r.setLists(lists);
    QString results = r.start();
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(results);
}

void MainWindow::on_actionClear_triggered()
{
    clear();
    m_repo.clear();
}

void MainWindow::on_actionSave_triggered()
{
    QList<ListState> listsStates;
    for(auto subWindow : ui->mdiArea->subWindowList())
    {
        MyListWidget* list =
                qobject_cast<MyListWidget*>(subWindow->widget());
        listsStates.push_back(list->getCurrentListState());
    }

    m_repo.setContent(toModelFormat(listsStates));

    QList<RandomItemList> lists = m_repo.getContent();

    SaveToFile s(m_repo.getFilePath());
    s.setContent(lists);
    s.start();
}

void MainWindow::on_actionAdd_List_triggered()
{
    ListState list;
    QMdiSubWindow* w = new QMdiSubWindow(ui->mdiArea);
    MyListWidget* myList = new MyListWidget(list, w);
    w->setWidget(myList);
    w->show();
}

void MainWindow::on_actionRemove_List_triggered()
{
    SelectListDialog* selectList = new SelectListDialog(this);
    QObject::connect(selectList, SIGNAL(selectList(QString)), this, SLOT(removeList(QString)));
    selectList->exec();
    QObject::disconnect(selectList, SIGNAL(selectList(QString)), this, SLOT(removeList(QString)));
}

void MainWindow::removeList(QString listTitle)
{
    for(auto subWindow : ui->mdiArea->subWindowList())
    {
        MyListWidget* list =
                qobject_cast<MyListWidget*>(subWindow->widget());
        ListState state = list->getCurrentListState();
        if(state.listName == listTitle)
        {
            subWindow->deleteLater();
        }
    }
}
