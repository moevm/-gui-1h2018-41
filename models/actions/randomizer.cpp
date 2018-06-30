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
    /*for(auto item : m_lists)
    {
        qDebug() << "list" << item.title();

        for(int i = 0; i < item.size(); i++)
        {
            RandomItem tmp = item.get(i);
            qDebug() << tmp.getTitle() << tmp.getSelected() << tmp.getCount();
        }
    }*/

    QList< QPair<RandomResults, size_t> > results = createSelectedItems();
    /*qDebug() << "filled";
    for(auto res : results)
    {
        qDebug() << "list" << res.first.title << res.second;
        qDebug() << res.first.items;
        qDebug() << "";
    }*/


    results = mixListsItems(results);
    /*qDebug() << "mixed";
    for(auto res : results)
    {
        qDebug() << "list" << res.first.title << res.second;
        qDebug() << res.first.items;
        qDebug() << "";
    }*/

    results = randomItems(results);
    /*qDebug() << "randomized";
    for(auto res : results)
    {
        qDebug() << "list" << res.first.title << res.second;
        qDebug() << res.first.items;
        qDebug() << "";
    }*/

    QString output = toString(results);
    //qDebug() << "converted" << output;
    return output;
}

QList< QPair<RandomResults, size_t> > Randomizer::createSelectedItems()
{
    QList< QPair<RandomResults, size_t> > selectedItems;
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
        selectedItems.push_back(QPair<RandomResults, size_t>(filledList, list.getNeedToFind()));
    }
    return selectedItems;
}

QList<QPair<RandomResults, size_t> > Randomizer::mixListsItems(QList< QPair<RandomResults, size_t> > lists)
{
    QList< QPair<RandomResults, size_t> > mixedLists;
    for(auto list : lists)
    {
        RandomResults mixedList;
        mixedList.title = list.first.title;

        QStringList mixedItems = list.first.items;
        std::shuffle(mixedItems.begin(), mixedItems.end(), rng);

        mixedList.items = mixedItems;

        mixedLists.push_back(QPair<RandomResults, size_t>(mixedList, list.second));
    }
    return mixedLists;
}

QList< QPair<RandomResults, size_t> > Randomizer::randomItems(QList< QPair<RandomResults, size_t> > lists)
{
    QList< QPair<RandomResults, size_t> > allRandomListsItems;
    for(auto list : lists)
    {
        QStringList allListItems = list.first.items;
        if(allListItems.size() > 0)
        {
            RandomResults listRandomResult;
            listRandomResult.title = list.first.title;

            std::uniform_int_distribution<int> randomItemIndex(0, allListItems.size() - 1);
            for(size_t i = 0; i < list.second; i++)
            {
                int index = randomItemIndex(rng);
                listRandomResult.items.push_back(allListItems[index]);
            }
            allRandomListsItems.push_back(QPair<RandomResults, size_t>(listRandomResult, list.second));
        }
    }
    return allRandomListsItems;
}

QString Randomizer::toString(QList<QPair<RandomResults, size_t> > results)
{
    QString output = "";
    for(auto result : results)
    {
        output += QStringLiteral("From list ") + result.first.title + QStringLiteral(" selected\n");
        for(auto item : result.first.items)
        {
            output += QStringLiteral("* ") + item + QStringLiteral("\n");
        }
        output += QStringLiteral("\n");
    }
    return output;
}
