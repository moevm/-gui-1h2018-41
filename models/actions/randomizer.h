#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QDebug>

#include <random>
#include <algorithm>

#include "models/types/randomitemlist.h"

struct RandomResults
{
    QString title;
    QStringList items;
};

class Randomizer
{
public:
    explicit Randomizer();


    void setLists(const QList<RandomItemList> &lists);

    QString start();

protected:
    QList<RandomItemList> m_lists;

    /*QStringList m_titles;
    QList< QList<QMap<QString, QString> > > m_lists;*/
    std::random_device rd;

    QList<RandomResults> createSelectedItems();
    QList<RandomResults> mixListsItems(QList<RandomResults> lists);
    QList<RandomResults> randomItems(QList<RandomResults> lists);
    QString toString(QList<RandomResults> results);
};

#endif // RANDOMIZER_H
