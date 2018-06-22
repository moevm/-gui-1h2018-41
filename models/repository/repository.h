#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QSet>
#include <QDebug>

#include "models/types/randomitemlist.h"
#include "libs/jsonparser/json.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository (QObject *parent = nullptr);

    void setContent(QString str);
    QList<RandomItemList> getContent();
    void clear();

signals:

public slots:

protected:
    QList<RandomItemList> m_lists;
};

#endif // REPOSITORY_H
