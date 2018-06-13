#include "mylistwidget.h"

MyListWidget::MyListWidget(QString name, QStringList items, QWidget *parent) :
    QWidget(parent),
    m_listName(name),
    m_items(items)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    //this->layout()->setContentsMargins(0, 5, 0, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setContentsMargins(0, 0, 0, 0);

    QLabel* title = new QLabel(m_listName, container);
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

void MyListWidget::updateList()
{
    m_listWidget->clear();
    for(auto item : m_items)
    {
        QListWidgetItem* listItem = new QListWidgetItem(m_listWidget);
        MyListWidgetItem* widget = new MyListWidgetItem(item, 1, false, m_listWidget);
        connect(widget, SIGNAL(save()), this, SLOT(onItemChanged()));
        listItem->setSizeHint(widget->minimumSizeHint());
        m_listWidget->addItem(listItem);
        m_listWidget->setItemWidget(listItem, widget);
    }
}

void MyListWidget::addItem()
{
    m_items.append("");
    updateList();
}

void MyListWidget::deleteItem()
{
    MyListWidgetItem* item = qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->currentItem()));
    m_items.removeOne(item->item());
    updateList();
}

void MyListWidget::onItemChanged()
{
    if(m_listWidget->count() == m_items.size())
    {
        for(int i = 0; i < m_listWidget->count(); i++)
        {
            MyListWidgetItem* itemWidget =
                    qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->item(i)));
            disconnect(itemWidget, SIGNAL(save()), this, SLOT(onItemChanged()));
            m_items[i] = itemWidget->item();
        }
        //updateList();
    }
}
