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
    //container->layout()->setSpacing(0);
    //container->layout()->setContentsMargins(0, 0, 0, 0);

    QLabel* title = new QLabel(m_listName, container);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    container->layout()->addWidget(title);

    QListWidget* list = new QListWidget(container);
    for(auto item : m_items)
    {
        list->addItem(item);
    }

    container->layout()->addWidget(list);

    this->layout()->addWidget(container);
}
