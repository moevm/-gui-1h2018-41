#ifndef RANDOMITEMLIST_H
#define RANDOMITEMLIST_H

#include <QObject>

#include "models/types/randomitem.h"

class RandomItemList
{
public:
    explicit RandomItemList(QString title);

    QString title() const;
    void setTitle(const QString &title);
    void add(RandomItem item);
    void remove(size_t index);
    RandomItem get(size_t index);
    void update(size_t index, RandomItem value);
    size_t size();

private:
    QString m_title;
    QList<RandomItem> m_items;
};

#endif // RANDOMITEMLIST_H
