#include "randomitem.h"

RandomItem::RandomItem(QString title, bool selected, size_t count) :
    m_title(title),
    m_selected(selected),
    m_count(count)
{

}

QString RandomItem::getTitle() const
{
    return m_title;
}

void RandomItem::setTitle(const QString &title)
{
    m_title = title;
}

bool RandomItem::getSelected() const
{
    return m_selected;
}

void RandomItem::setSelected(bool selected)
{
    m_selected = selected;
}

size_t RandomItem::getCount() const
{
    return m_count;
}

void RandomItem::setCount(const size_t &count)
{
    m_count = count;
}
