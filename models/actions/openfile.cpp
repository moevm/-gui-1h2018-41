#include "openfile.h"

OpenFile::OpenFile(QString path) :
    m_path(path)
{

}

QList<RandomItemList> OpenFile::start()
{
    QList<RandomItemList> content;

    /*QFile test(m_path);
    if(!test.exists())
    {
        m_path = QFileDialog::getOpenFileName(0, "Open File", "", "*.json");
    }*/

    //qDebug() << m_path;

    QFile file(m_path);
    if (file.open(QIODevice::ReadWrite))
    {
        QString data = file.readAll();
        file.close();
        content = parse(data);
    }
    return content;
}

QList<RandomItemList> OpenFile::parse(QString data)
{
    QList<RandomItemList> resultLists;

    QtJson::JsonObject objectFromFile = QtJson::parse(data).toMap();

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
        resultLists.append(listTmp);
    }
    return resultLists;
}

QString OpenFile::path() const
{
    return m_path;
}
