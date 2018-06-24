#include "repository.h"

Repository::Repository(QObject *parent) : QObject(parent)
{

}

void Repository::setContent(QString str)
{
    QtJson::JsonObject objectFromFile = QtJson::parse(str).toMap();

    QtJson::JsonArray allLists = objectFromFile["lists"].toList();

    for(int i = 0; i < allLists.size(); i++)
    {
        QtJson::JsonObject list = allLists[i].toMap();

        QString listTitle = list.begin().key();

        QtJson::JsonObject listParams = list[listTitle].toMap();

        size_t needToFind = listParams["find"].toUInt();

        QtJson::JsonArray items = listParams["items"].toList();

        RandomItemList listTmp(listTitle);
        listTmp.setNeedToFind(needToFind);
        for(int j = 0; j < items.size(); j++)
        {
            QtJson::JsonObject item = items[j].toMap();
            QString title = item["title"].toString();
            bool selected = item["selected"].toBool();
            int count = item["count"].toUInt();
            listTmp.add(RandomItem(title, selected, count));
        }
        m_lists.append(listTmp);
    }
}

void Repository::setContent(QList<RandomItemList> lists)
{
    m_lists = lists;
}

QList<RandomItemList> Repository::getContent()
{
    return m_lists;
}

void Repository::clear()
{
    m_lists.clear();
}
