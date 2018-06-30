#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    initWidgets();
    openLibrary();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    auto toolbar = ui->mainToolBar;
    toolbar->addAction(ui->actionMenu);
    //toolbar->addAction(ui->actionOpen);
    toolbar->addAction(ui->actionSave);
    toolbar->addAction(ui->actionAdd_List);
    toolbar->addAction(ui->actionRemove_List);
    //toolbar->addAction(ui->actionClear);

    ui->randomizePushButton->setText(generateRandomLabelText());

    QMessageBox(QMessageBox::Information, "", generateHelloMessage()).exec();
}

void MainWindow::openLibrary()
{
    OpenFile open;
    m_repo.setContent(open.start());
    m_repo.setFilePath(open.path());

    QList<ListState> lists = toGuiFormat(m_repo.getContent());

    QStringList titles;
    for(auto list : lists)
    {
        titles.push_back(list.listName);
    }

    ui->menuListWidget->clear();
    ui->menuListWidget->addItems(titles);
}

QList<ListState> MainWindow::toGuiFormat(QList<RandomItemList> lists)
{
    QList<ListState> listWidgetsStates;
    for(int i = 0; i < lists.size(); i++)
    {
        ListState listWidgetState;
        listWidgetState.listName = lists[i].title();
        listWidgetState.needToFind = lists[i].getNeedToFind();
        listWidgetState.tags = lists[i].getTags();

        for(size_t j = 0; j < lists[i].size(); j++)
        {
            RandomItem item = lists[i].get(j);
            ItemState itemWidget;
            itemWidget.title = item.getTitle();
            itemWidget.count = item.getCount();
            itemWidget.selected = item.getSelected();
            listWidgetState.listItems.push_back(itemWidget);
        }
        listWidgetsStates.push_back(listWidgetState);
    }
    return listWidgetsStates;
}

ListState MainWindow::toGuiFormat(RandomItemList list)
{
    ListState listWidgetState;
    listWidgetState.listName = list.title();
    listWidgetState.needToFind = list.getNeedToFind();
    listWidgetState.tags = list.getTags();
    for(size_t j = 0; j < list.size(); j++)
    {
        RandomItem item = list.get(j);
        ItemState itemWidget;
        itemWidget.title = item.getTitle();
        itemWidget.count = item.getCount();
        itemWidget.selected = item.getSelected();

        listWidgetState.listItems.push_back(itemWidget);
    }
    return listWidgetState;
}

QList<RandomItemList> MainWindow::toModelFormat(QList<ListState> listsStates)
{
    QList<RandomItemList> lists;
    for(auto listState : listsStates)
    {
        RandomItemList list(listState.listName);
        list.setNeedToFind(listState.needToFind);
        list.setTags(listState.tags);
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

QString MainWindow::generateRandomLabelText()
{
    QStringList list =
    {
        "Узнать будущее",
        "Сейчас все порешаем",
        "Снять с себя ответственность",
        "Да, это бесплатно",
        "Решайся!",
        "Еще разок, чтобы наверняка",
        "Быть или не быть?"
    };

    int maxIndex = list.size() - 1;
    int minIndex = 0;

    std::uniform_int_distribution<int> randomIndex(minIndex, maxIndex);

    int index = randomIndex(rng);
    return list[index];
}

QString MainWindow::generateHelloMessage()
{
    QStringList list =
    {
        "Доброе утро, Ваше нерешительное великолепие!",
        "Чудесный день! А Вы еще чудесней!",
        "Добрый вечер! Сегодня больше не нужно ничего решать: я сделаю все за Вас!",
        "Здравствуйте! Вы великолепны!",
        "Прекрасный выбор! Добрый день!",
        "Доброе утро! Сегодня Вы точно не ошибетесь",
        "Доброго времени суток! Сегодня вам точно повезет :3"
    };

    int maxIndex = list.size() - 1;
    int minIndex = 0;

    std::uniform_int_distribution<int> randomIndex(minIndex, maxIndex);

    int index = randomIndex(rng);
    return list[index];
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

    QList<RandomItemList> lists = toModelFormat(listsStates);

    /*qDebug() << "---";
    for(int i = 0; i < lists.size(); i++)
    {
        for(size_t j = 0; j < lists[i].size(); j++)
        {
            RandomItem item = lists[i].get(j);
            qDebug() << item.getTitle() << item.getSelected() << item.getCount();
        }
    }
    qDebug() << "---";*/

    Randomizer r;
    r.setLists(lists);
    QString results = r.start();
    //qDebug() << results;
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(results);

    ui->randomizePushButton->setText(generateRandomLabelText());
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

    m_repo.addLists(toModelFormat(listsStates));
    m_repo.save();

    openLibrary();
}

void MainWindow::on_actionAdd_List_triggered()
{
    ListState list;
    MyMdiSubWindow* w = new MyMdiSubWindow(ui->mdiArea);
    QString objectName = QStringLiteral("MyMdiSubWindow") + QString::number(ui->mdiArea->subWindowList().size());
    w->setObjectName(objectName);
    QObject::connect(w, SIGNAL(closed(QString)), this, SLOT(onMyMdiSubWindowClosed(QString)));

    MyListWidget* myList = new MyListWidget(list, w);
    w->setWidget(myList);
    w->adjustSize();
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

    m_repo.removeList(listTitle);
    m_repo.save();
    openLibrary();
}

void MainWindow::on_actionMenu_triggered()
{
    if(ui->menuDockWidget->isVisible())
    {
        ui->menuDockWidget->hide();
    }
    else
    {
        ui->menuDockWidget->show();
    }
}

void MainWindow::on_menuListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString listTitle = item->text();

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

    ListState list = toGuiFormat(m_repo.findList(listTitle));
    MyMdiSubWindow* w = new MyMdiSubWindow(ui->mdiArea);
    QString objectName = QStringLiteral("MyMdiSubWindow") + QString::number(ui->mdiArea->subWindowList().size());
    w->setObjectName(objectName);
    QObject::connect(w, SIGNAL(closed(QString)), this, SLOT(onMyMdiSubWindowClosed(QString)));

    MyListWidget* myList = new MyListWidget(list, w);

    w->setWidget(myList);
    w->adjustSize();
    w->show();
}

void MainWindow::onMyMdiSubWindowClosed(QString objectName)
{
    QList<QMdiSubWindow*> allWindows = ui->mdiArea->subWindowList();
    for(auto w : allWindows)
    {
        if(w->objectName() == objectName)
        {
            w->deleteLater();
        }
    }
}

void MainWindow::on_findByTagLineEdit_textChanged(const QString &arg1)
{
    QStringList tags = arg1.split("+", QString::SkipEmptyParts);

    ui->menuListWidget->clear();
    QList<ListState> lists = toGuiFormat(m_repo.getContent());

    QStringList titles;
    for(auto list : lists)
    {
        bool suitable = true;
        for(auto tag : tags)
        {
            QStringList listTags = list.tags;
            if(!listTags.contains(tag))
            {
                suitable = false;
            }
        }
        if(suitable)
        {
            titles.push_back(list.listName);
        }
    }

    ui->menuListWidget->clear();
    ui->menuListWidget->addItems(titles);
}
