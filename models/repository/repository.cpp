#include "repository.h"

Repository::Repository(QObject *parent) :
    QObject(parent),
    m_filePath(QStandardPaths::locate(QStandardPaths::DocumentsLocation, QString("lists.json")))
{

}

void Repository::setContent(QList<RandomItemList> lists)
{
    m_allLists.clear();
    for(auto list : lists)
    {
        m_allLists.insert(list.title(), list);
    }
}

void Repository::addLists(QList<RandomItemList> lists)
{
    for(auto list : lists)
    {
        m_allLists.insert(list.title(), list);
    }
}

void Repository::removeList(QString name)
{
    m_allLists.remove(name);
}

QList<RandomItemList> Repository::getContent()
{
    return contentToList();
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
    s.setContent(contentToList());
    s.start();
}

QList<RandomItemList> Repository::contentToList()
{
    QList<RandomItemList> content;
    for(auto list : m_allLists)
    {
        content.push_back(list);
    }
    return content;
}
