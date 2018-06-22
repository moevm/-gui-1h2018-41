#include "randomizer.h"

Randomizer::Randomizer()
{

}

void Randomizer::setLists(const QList<RandomItemList> &lists)
{
    m_lists = lists;
}

QString Randomizer::start()
{
    QList<RandomResults> results = createSelectedItems();
    results = mixListsItems(results);
    results = randomItems(results);
    QString output = toString(results);
    return output;
}

QList<RandomResults> Randomizer::createSelectedItems()
{
    QList<RandomResults> selectedItems;
    for(auto list : m_lists)
    {
        RandomResults filledList;
        filledList.title = list.title();
        for(size_t i = 0; i < list.size(); i++)
        {
            RandomItem item = list.get(i);
            if(item.getSelected())
            {
                size_t count = item.getCount();

                for(size_t i = 0; i < count; i++)
                {
                    filledList.items.push_back(item.getTitle());
                }
            }

        }
        selectedItems.push_back(filledList);
    }
    return selectedItems;
}

QList<RandomResults> Randomizer::mixListsItems(QList<RandomResults> lists)
{
    QList<RandomResults> mixedLists;
    for(auto list : lists)
    {
        RandomResults mixedList;
        mixedList.title = list.title;

        QStringList mixedItems = list.items;
        std::mt19937 g(rd());
        std::shuffle(mixedItems.begin(), mixedItems.end(), g);

        mixedList.items = mixedItems;

        mixedLists.push_back(mixedList);
    }
    return mixedLists;
}

QList<RandomResults> Randomizer::randomItems(QList<RandomResults> lists)
{
    QList<RandomResults> allRandomListsItems;
    for(auto list : lists)
    {
        QStringList allListItems = list.items;
        if(allListItems.size() > 0)
        {
            RandomResults listRandomResult;
            listRandomResult.title = list.title;

            std::mt19937 g(rd());
            std::uniform_int_distribution<int> randomItemIndex(0, allListItems.size() - 1);
            for(int i = 0; i < 2; i++)
            {
                int index = randomItemIndex(g);
                listRandomResult.items.push_back(allListItems[index]);
            }
            allRandomListsItems.push_back(listRandomResult);
        }
    }
    return allRandomListsItems;
}

QString Randomizer::toString(QList<RandomResults> results)
{
    QString output = "";
    for(auto result : results)
    {
        output += QStringLiteral("From list ") + result.title + QStringLiteral(" selected\n");
        for(auto item : result.items)
        {
            output += QStringLiteral("     ") + item + QStringLiteral("\n");
        }
        output += QStringLiteral("\n");
    }
    return output;
}
