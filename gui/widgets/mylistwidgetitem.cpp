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

    m_selectedCheckBox = new QCheckBox(container);
    if(m_checked)
    {
        m_selectedCheckBox->setChecked(true);
    }
    else
    {
        m_selectedCheckBox->setChecked(false);
    }
    container->layout()->addWidget(m_selectedCheckBox);

    m_itemWidget = new QLineEdit(m_item, container);
    QObject::connect(m_itemWidget, SIGNAL(editingFinished()), this, SLOT(onItemUpdated()));
    container->layout()->addWidget(m_itemWidget);

    m_counWidget = new QLineEdit(QString::number(m_count), container);
    m_counWidget->setMaximumWidth(50);
    container->layout()->addWidget(m_counWidget);

    this->layout()->addWidget(container);
}

QString MyListWidgetItem::item() const
{
    return m_item;
}

void MyListWidgetItem::onItemUpdated()
{
    m_item = m_itemWidget->text();
    m_count = m_counWidget->text().toUInt();
    m_checked = m_selectedCheckBox->isChecked();
    emit save();
}
