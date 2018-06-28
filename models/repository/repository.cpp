#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_filePath(QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString("lists.json")))
{

}

void Repository::setContent(QList<RandomItemList> lists)
{
    m_allLists = lists;
}

void Repository::addLists(QList<RandomItemList> lists)
{
    QList<RandomItemList> uniqueLists;
    QList<RandomItemList> replaceLists;

    for(size_t i = 0; i < (size_t) lists.size(); i++)
    {
        bool isFind = false;
        for(size_t j = 0; j < (size_t) m_allLists.size(); j++)
        {
            if(m_allLists[j].title() == lists[i].title())
            {
                isFind = true;
                break;
            }
        }
        if(!isFind)
        {
            uniqueLists.push_back(lists[i]);
        }
        else
        {
            replaceLists.push_back(lists[i]);
        }
    }

    for(auto list : uniqueLists)
    {
        if(!list.title().isEmpty())
        {
            m_allLists.push_back(list);
        }
    }

    for(auto list : replaceLists)
    {
        removeList(list.title());
        m_allLists.push_back(list);
    }
}

void Repository::removeList(QString name)
{
    int index = -1;
    for(int i = 0; i < m_allLists.size(); i++)
    {
        if(m_allLists[i].title() == name)
        {
            index = i;
            break;
        }
    }

    if(index >= 0 && index < m_allLists.size())
    {
        m_allLists.removeAt(index);
    }
}

QList<RandomItemList> Repository::getContent()
{
    return m_allLists;
}

void Repository::clear()
{
    m_allLists.clear();
}

QString Repository::getFilePath() const
{
    return m_filePath;
}

void Repository::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

RandomItemList Repository::findList(QString listName)
{
    RandomItemList currentList;

    for(auto list : m_allLists)
    {
        if(list.title() == listName)
        {
            currentList = list;
        }
    }
    return currentList;
}

void Repository::save()
{
    SaveToFile s(m_filePath);
    s.setContent(m_allLists);
    s.start();
}
