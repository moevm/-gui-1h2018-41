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

    //QSet<RandomItemList> m_lists() const;
    void setContent(QString str);
    //void setContent(QList<QMap<QString,QString>> list);

signals:

public slots:

protected:
    QList<RandomItemList> m_lists;
};

#endif // REPOSITORY_H
