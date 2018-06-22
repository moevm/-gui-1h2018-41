#include "randomizer.h"

Randomizer::Randomizer(QObject *parent) : QObject(parent)
{

}

void Randomizer::setLists(const QList<QList<QMap<QString, QString> > > &lists)
{
    m_lists = lists;
}

void Randomizer::start()
{
    qDebug() << "initial lists" << m_lists;
    qDebug() << "";
    QList<QStringList> selectedItems = createSelectedItems();
    qDebug() << "only selected items" << selectedItems;
    qDebug() << "";
    selectedItems = mixListsItems(selectedItems);
    qDebug() << "mixed items" << selectedItems;
}

QList<QStringList> Randomizer::createSelectedItems()
{
    QList< QStringList > selecteItems;
    for(auto list : m_lists)
    {
        QStringList listItems;
        for(auto item : list)
        {
            if(item["checked"].toInt() == true)
            {
                size_t count = item["count"].toUInt();

                for(size_t i = 0; i < count; i++)
                {
                    listItems.push_back(item["title"]);
                }
            }
        }
        selecteItems.push_back(listItems);
    }
    return selecteItems;
}

QList<QStringList> Randomizer::mixListsItems(QList< QStringList > lists)
{
    std::random_device rd;

    QList<QStringList> mixedLists;
    for(auto list : lists)
    {
        QStringList mixedItems = list;
        std::mt19937 g(rd());
        std::shuffle(mixedItems.begin(), mixedItems.end(), g);
        mixedLists.push_back(mixedItems);
    }
    return mixedLists;
}
