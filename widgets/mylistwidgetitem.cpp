#include "mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(QString item, size_t count, bool checked, QWidget *parent) :
    QWidget(parent),
    m_item(item),
    m_count(count),
    m_checked(checked)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(5, 5, 5, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QHBoxLayout(container));
    container->layout()->setContentsMargins(0, 0, 0, 0);
    container->layout()->setAlignment(Qt::AlignLeft);

    QCheckBox* itemCheckBox = new QCheckBox(container);
    if(m_checked)
    {
        itemCheckBox->setChecked(true);
    }
    else
    {
        itemCheckBox->setChecked(false);
    }
    container->layout()->addWidget(itemCheckBox);

    QLineEdit* title = new QLineEdit(m_item, container);
    container->layout()->addWidget(title);

    QLineEdit* lineEdit = new QLineEdit(QString::number(m_count), container);
    lineEdit->setMaximumWidth(50);
    container->layout()->addWidget(lineEdit);

    this->layout()->addWidget(container);
}
