#ifndef RANDOMITEMLIST_H
#define RANDOMITEMLIST_H

#include <QObject>

#include "models/types/randomitem.h"

class RandomItemList
{
public:
    explicit RandomItemList(QString title = "");

    QString title() const;
    void setTitle(const QString &title);
    void add(RandomItem item);
    void remove(size_t index);
    RandomItem get(size_t index);
    void update(size_t index, RandomItem value);
    size_t size();

    size_t getNeedToFind() const;
    void setNeedToFind(const size_t &needToFind);

    QStringList getTags() const;
    void setTags(const QStringList &tags);

private:
    QString m_title;
    QList<RandomItem> m_items;
    size_t m_needToFind;
    QStringList m_tags;
};

#endif // RANDOMITEMLIST_H
