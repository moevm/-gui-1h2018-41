#include "randomizer.h"

Randomizer::Randomizer()
{

}

void Randomizer::setLists(const QList<QList<QMap<QString, QString> > > &lists)
{
    m_lists = lists;
}

QStringList Randomizer::start()
{
    QList<QStringList> selectedItems = createSelectedItems();
    selectedItems = mixListsItems(selectedItems);
    QStringList items = randomItems(selectedItems);
    return items;
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

QStringList Randomizer::randomItems(QList<QStringList> lists)
{
    QStringList randomItems;
    for(auto list : lists)
    {
        if(list.size() > 0)
        {
            std::mt19937 g(rd());
            std::uniform_int_distribution<int> randomItemIndex(0, list.size() - 1);
            int artistIndex = randomItemIndex(g);
            randomItems.push_back(list[artistIndex]);
        }
    }
    return randomItems;
}
