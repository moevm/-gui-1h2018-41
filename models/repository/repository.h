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

    void setContent(QList<RandomItemList> lists);
    QList<RandomItemList> getContent();
    void clear();

    QString getFilePath() const;
    void setFilePath(const QString &filePath);

signals:

public slots:

protected:
    QList<RandomItemList> m_lists;
    QString m_filePath = "";
};

#endif // REPOSITORY_H
