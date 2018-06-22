#include "mylistwidget.h"

MyListWidget::MyListWidget(QString name, QList<QMap<QString, QString> > items, QWidget *parent) :
    QWidget(parent),
    m_listName(name),
    m_list(items)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    //this->layout()->setContentsMargins(0, 5, 0, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setContentsMargins(0, 0, 0, 0);

    QLineEdit* title = new QLineEdit(m_listName, container);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    container->layout()->addWidget(title);
        QFrame* mainFrame = new QFrame(container);
        mainFrame->setLayout(new QHBoxLayout(mainFrame));
        mainFrame->layout()->setContentsMargins(0, 0, 0, 0);
            QFrame* actionsFrame = new QFrame(mainFrame);
            actionsFrame->setLayout(new QVBoxLayout(actionsFrame));
            actionsFrame->layout()->setContentsMargins(0, 0, 0, 0);
            actionsFrame->layout()->setAlignment(Qt::AlignTop);
                QPushButton* addButton = new QPushButton("+", actionsFrame);
                QObject::connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addItem()));
                actionsFrame->layout()->addWidget(addButton);
                QPushButton* deleteButton = new QPushButton("-", actionsFrame);
                QObject::connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));
                actionsFrame->layout()->addWidget(deleteButton);
            mainFrame->layout()->addWidget(actionsFrame);
            QFrame* listFrame = new QFrame(mainFrame);
            listFrame->setLayout(new QVBoxLayout(listFrame));
            listFrame->layout()->setContentsMargins(0, 0, 0, 0);
                m_listWidget = new QListWidget(container);
                updateList();
                listFrame->layout()->addWidget(m_listWidget);
            mainFrame->layout()->addWidget(listFrame);
        container->layout()->addWidget(mainFrame);
        this->layout()->addWidget(container);
}

QList< QMap<QString, QString> > MyListWidget::getCurrentListState()
{
    QList< QMap<QString, QString> > items;
    for(int i = 0; i < m_listWidget->count(); i++)
    {
        QMap<QString, QString> itemMap;
        MyListWidgetItem* itemWidget =
                qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->item(i)));
        itemMap.insert(QString("title"), itemWidget->title());
        itemMap.insert(QString("count"), QString::number(itemWidget->count()));
        itemMap.insert(QString("checked"), QString::number(itemWidget->checked()));

        items.push_back(itemMap);
    }
    return items;
}

void MyListWidget::updateList()
{
    m_listWidget->clear();

    for(auto item : m_list)
    {
        QListWidgetItem* listItem = new QListWidgetItem(m_listWidget);
        MyListWidgetItem* widget = new MyListWidgetItem(item["title"],
                item["count"].toUInt(),
                item["selected"].toInt(),
                m_listWidget);
        connect(widget, SIGNAL(save()), this, SLOT(onItemChanged()));
        listItem->setSizeHint(widget->minimumSizeHint());
        m_listWidget->addItem(listItem);
        m_listWidget->setItemWidget(listItem, widget);
    }

    /*for(int i = 0; i < m_items.size(); i++)
    {
        QListWidgetItem* listItem = new QListWidgetItem(m_listWidget);
        RandomItem item = m_items.get(i);
        MyListWidgetItem* widget = new MyListWidgetItem(item.getTitle(), item.getCount(), item.getSelected(), m_listWidget);
        connect(widget, SIGNAL(save()), this, SLOT(onItemChanged()));
        listItem->setSizeHint(widget->minimumSizeHint());
        m_listWidget->addItem(listItem);
        m_listWidget->setItemWidget(listItem, widget);
    }*/
}

void MyListWidget::addItem()
{
    QMap<QString, QString> emptyItem;
    emptyItem.insert("title", "");
    emptyItem.insert("count", "1");
    emptyItem.insert("selected", "0");

    m_list.push_back(emptyItem);
    updateList();
}

void MyListWidget::deleteItem()
{
    MyListWidgetItem* item = qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->currentItem()));

    QMap<QString, QString> itemContent;
    itemContent.insert("title", item->title());
    itemContent.insert("count", QString::number(item->count()));
    itemContent.insert("selected", QString::number(item->checked()));

    m_list.removeOne(itemContent);
    updateList();
}

void MyListWidget::onItemChanged()
{
    if(m_listWidget->count() == m_list.size())
    {
        for(int i = 0; i < m_listWidget->count(); i++)
        {
            MyListWidgetItem* itemWidget =
                    qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->item(i)));
            disconnect(itemWidget, SIGNAL(save()), this, SLOT(onItemChanged()));

            QMap<QString, QString> item;
            item.insert("title", itemWidget->title());
            item.insert("count", QString::number(itemWidget->count()));
            item.insert("selected", QString::number(itemWidget->checked()));

            m_list[i] = item;
        }
        //updateList();
    }
}
