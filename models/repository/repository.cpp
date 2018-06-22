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

        QString listTitle =  list.begin().key();

        QtJson::JsonArray items = list[listTitle].toList();

        RandomItemList listTmp(listTitle);
        for(int j = 0; j < items.size(); j++)
        {
            QtJson::JsonArray item = items[j].toList();
            QString title = item.at(0).toString();
            bool selected = item.at(1).toInt();
            int count = item.at(2).toInt();
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
