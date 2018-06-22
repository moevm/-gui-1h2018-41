#include "mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(QString item, size_t count, bool checked, QWidget *parent) :
    QWidget(parent),
    m_title(item),
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
    container->setStyleSheet("background-color:#eee; border-radius:5px; padding:5px;");

    m_selectedCheckBox = new QCheckBox(container);
    if(m_checked)
    {
        m_selectedCheckBox->setChecked(true);
    }
    else
    {
        m_selectedCheckBox->setChecked(false);
    }
    QObject::connect(m_selectedCheckBox, SIGNAL(clicked(bool)), this, SLOT(onItemUpdated()));
    container->layout()->addWidget(m_selectedCheckBox);

    m_itemWidget = new QLineEdit(m_title, container);
    m_itemWidget->setStyleSheet("background-color:#fff; border:1px solid #dfdfdf; border-radius:5px; padding:5px;");
    QObject::connect(m_itemWidget, SIGNAL(editingFinished()), this, SLOT(onItemUpdated()));
    container->layout()->addWidget(m_itemWidget);

    m_countWidget = new QLineEdit(QString::number(m_count), container);
    m_countWidget->setMaximumWidth(50);
    m_countWidget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_countWidget->setStyleSheet("background-color:#fff; border:1px solid #dfdfdf; border-radius:5px; padding:5px;");
    QObject::connect(m_countWidget, SIGNAL(editingFinished()), this, SLOT(onItemUpdated()));
    container->layout()->addWidget(m_countWidget);

    this->layout()->addWidget(container);
}

QString MyListWidgetItem::title() const
{
    return m_title;
}

void MyListWidgetItem::onItemUpdated()
{
    m_title = m_itemWidget->text();
    m_count = m_countWidget->text().toUInt();
    m_checked = m_selectedCheckBox->isChecked();
    emit save();
}

bool MyListWidgetItem::checked() const
{
    return m_checked;
}

size_t MyListWidgetItem::count() const
{
    return m_count;
}
