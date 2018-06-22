#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QDebug>

#include <random>
#include <algorithm>

#include "models/types/randomitemlist.h"

class Randomizer
{
public:
    explicit Randomizer();

    void setLists(const QList<QList<QMap<QString, QString> > > &lists);

    QStringList start();

protected:
    QList< QList<QMap<QString, QString> > > m_lists;
    std::random_device rd;

    QList<QStringList> createSelectedItems();
    QList<QStringList> mixListsItems(QList<QStringList> lists);
    QStringList randomItems(QList<QStringList> lists);
};

#endif // RANDOMIZER_H
