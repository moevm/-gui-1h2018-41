#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

struct ItemState
{
    QString title;
    bool selected;
    size_t count;
};

struct ListState
{
    QString listName;
    QList<ItemState> listItems;
};

#endif // STRUCTS_H
