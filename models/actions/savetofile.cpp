#include "savetofile.h"

SaveToFile::SaveToFile(QString path) :
    m_filePath(path)
{

}

void SaveToFile::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}

void SaveToFile::setContent(const QList<RandomItemList> &content)
{
    m_content = content;
}

void SaveToFile::start()
{
    QByteArray fileContent = contentToByteArray();

    QFile test(m_filePath);
    if(!test.exists())
    {
        m_filePath = QFileDialog::getSaveFileName(nullptr, "Save", "", "*.json");
    }
    QFile file(m_filePath);

    file.reset();
    file.open(QIODevice::ReadWrite);
    file.write(fileContent);
    //QTextStream in(&file);
    //in << str;
    file.close();
}

QByteArray SaveToFile::contentToByteArray()
{
    QtJson::JsonObject rootObject;

    QtJson::JsonArray lists;

    for(auto list : m_content)
    {
        QtJson::JsonObject listObject;
        QtJson::JsonObject listContentObject;
        listContentObject["find"] = QVariant::fromValue(list.getNeedToFind());
        QtJson::JsonArray items;

        for(size_t i = 0; i < list.size(); i++)
        {
            QtJson::JsonObject item;
            RandomItem currentItem = list.get(i);
            item["title"] = currentItem.getTitle();
            item["selected"] = currentItem.getSelected();
            item["count"] = QVariant::fromValue(currentItem.getCount());

            items.append(item);
        }
        listContentObject["items"] =items;
        listObject[list.title()] = listContentObject;
        lists.append(listObject);
    }

    rootObject["lists"] = lists;
    return QtJson::serialize(rootObject);
}
