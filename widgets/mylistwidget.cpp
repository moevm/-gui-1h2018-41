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
                actionsFrame->layout()->addWidget(addButton);
                QPushButton* deleteButton = new QPushButton("-", actionsFrame);
                actionsFrame->layout()->addWidget(deleteButton);
            mainFrame->layout()->addWidget(actionsFrame);
            QFrame* listFrame = new QFrame(mainFrame);
            listFrame->setLayout(new QVBoxLayout(listFrame));
            listFrame->layout()->setContentsMargins(0, 0, 0, 0);
                QListWidget* list = new QListWidget(container);
                for(auto item : m_items)
                {
                    QListWidgetItem* listItem = new QListWidgetItem(list);
                    MyListWidgetItem* widget = new MyListWidgetItem(item, 1, false, list);
                    listItem->setSizeHint(widget->minimumSizeHint());
                    list->addItem(listItem);
                    list->setItemWidget(listItem, widget);
                }
                listFrame->layout()->addWidget(list);
            mainFrame->layout()->addWidget(listFrame);
        container->layout()->addWidget(mainFrame);
    this->layout()->addWidget(container);
}
