#include "mylistwidgetitem.h"

MyListWidgetItem::MyListWidgetItem(QString item, size_t count, bool checked, QWidget *parent) :
    QWidget(parent),
    m_title(item),
    m_count(count),
    m_selected(checked)
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
    if(m_selected)
    {
        m_selectedCheckBox->setChecked(true);
    }
    else
    {
        m_selectedCheckBox->setChecked(false);
    }
    QObject::connect(m_selectedCheckBox, SIGNAL(clicked(bool)), this, SLOT(onItemUpdated()));
    container->layout()->addWidget(m_selectedCheckBox);

    m_titleWidget = new QLineEdit(m_title, container);
    m_titleWidget->setStyleSheet("background-color:#fff; border:1px solid #dfdfdf; border-radius:5px; padding:5px;");
    m_titleWidget->setPlaceholderText("Элемент для рандомизации");
    QObject::connect(m_titleWidget, SIGNAL(editingFinished()), this, SLOT(onItemUpdated()));
    container->layout()->addWidget(m_titleWidget);

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
    m_title = m_titleWidget->text();
    m_count = m_countWidget->text().toUInt();
    m_selected = m_selectedCheckBox->isChecked();
    emit save();
}

void MyListWidgetItem::setSelected(bool selected)
{
    m_selected = selected;
    m_selectedCheckBox->setChecked(m_selected);
    onItemUpdated();
}

bool MyListWidgetItem::checked() const
{
    return m_selected;
}

size_t MyListWidgetItem::count() const
{
    return m_count;
}
