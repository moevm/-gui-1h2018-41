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

    QList< QPair<RandomResults, size_t> > createSelectedItems();
    QList< QPair<RandomResults, size_t> > mixListsItems(QList< QPair<RandomResults, size_t> > lists);
    QList< QPair<RandomResults, size_t> > randomItems(QList<QPair<RandomResults, size_t> > lists);
    QString toString(QList< QPair<RandomResults, size_t> > results);
};

#endif // RANDOMIZER_H
