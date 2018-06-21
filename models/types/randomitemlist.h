#ifndef RANDOMITEMLIST_H
#define RANDOMITEMLIST_H

#include <QObject>

#include "randomitem.h"

class RandomItemList : public QObject
{
    Q_OBJECT
public:
    explicit RandomItemList(QString title, QList<RandomItem> items, QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &title);

signals:

public slots:
    void add(RandomItem item);
    void remove(size_t index);
    RandomItem get(size_t index);
    void update(size_t index, RandomItem value);

private:
    QString m_title;
    QList<RandomItem> m_items;
};

#endif // RANDOMITEMLIST_H
