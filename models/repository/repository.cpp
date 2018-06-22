#include "repository.h"

Repository::Repository(QObject *parent) : QObject(parent)
{

}

void Repository::setContent(QString str)
{
    QtJson::JsonObject objectFromFile = QtJson::parse(str).toMap();

    qDebug() << "parsed object from file:" << objectFromFile;
    qDebug() << "";

    QtJson::JsonArray allLists = objectFromFile["lists"].toList();
    //qDebug() << allLists << allLists.size();
    //qDebug() << "";

    for(int i = 0; i < allLists.size(); i++)
    {
        QtJson::JsonObject list = allLists[i].toMap();
        //qDebug() << "#" << i << "item is" << list << list.size();

        QString listTitle =  list.begin().key();
        //qDebug() << "list title" << listTitle;
        //qDebug() << "";

        QtJson::JsonArray items = list[listTitle].toList();
        //qDebug() << "items" << items << items.size();
        //qDebug() << "";

        RandomItemList listTmp(listTitle);
        for(int j = 0; j < items.size(); j++)
        {
            QtJson::JsonArray item = items[j].toList();
            QString title = item.at(0).toString();
            bool selected = item.at(1).toInt();
            int count = item.at(2).toInt();
            listTmp.add(RandomItem(title, selected, count));
        }
        //m_lists.insert(listTmp);
        m_lists.append(listTmp);
    }
}

QList<RandomItemList> Repository::getContent()
{
    return m_lists;
}
