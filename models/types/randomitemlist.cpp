#include "randomitemlist.h"

RandomItemList::RandomItemList(QString title) :
    m_title(title)
{

}

QString RandomItemList::title() const
{
    return m_title;
}

void RandomItemList::setTitle(const QString &title)
{
    m_title = title;
}

void RandomItemList::add(RandomItem item)
{
    m_items.insert(m_items.size(), item);

}

void RandomItemList::remove(size_t index)
{
    m_items.removeAt(index);
}

RandomItem RandomItemList::get(size_t index)
{
    RandomItem item;
    if(index < (size_t) m_items.size())
    {
        item = m_items[index];
    }
    else
    {
        throw std::out_of_range("index is out of range");
    }
    return item;
}

void RandomItemList::update(size_t index, RandomItem value)
{
    if(index < (size_t) m_items.size())
    {
        m_items[index] = value;
    }
    else
    {
        throw std::out_of_range("index is out of range");
    }
}

size_t RandomItemList::size()
{
    return m_items.size();
}

size_t RandomItemList::getNeedToFind() const
{
    return m_needToFind;
}

void RandomItemList::setNeedToFind(const size_t &needToFind)
{
    m_needToFind = needToFind;
}
