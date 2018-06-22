#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>
#include <QDebug>

#include <random>
#include <algorithm>

#include "models/types/randomitemlist.h"

class Randomizer : public QObject
{
    Q_OBJECT
public:
    explicit Randomizer(QObject *parent = nullptr);

    void setLists(const QList<QList<QMap<QString, QString> > > &lists);

    void start();

protected:
    QList< QList<QMap<QString, QString> > > m_lists;

    //QList< QStringList > m_selecteItems;

    QList<QStringList> createSelectedItems();
    QList<QStringList> mixListsItems(QList<QStringList> lists);

signals:
    void randomized(QStringList items);

public slots:
};

#endif // RANDOMIZER_H
