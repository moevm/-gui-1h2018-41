#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include "../types/randomitemlist.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository(QObject *parent = nullptr);

signals:

public slots:

private:
    //QSet<RandomItemList> set;
};

#endif // REPOSITORY_H
