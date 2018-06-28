#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QStandardPaths>
#include <QDebug>

#include "models/types/randomitemlist.h"
#include "libs/jsonparser/json.h"

#include "models/actions/savetofile.h"

class Repository : public QObject
{
    Q_OBJECT
public:
    explicit Repository (QObject *parent = nullptr);

    void setContent(QList<RandomItemList> lists);
    void addLists(QList<RandomItemList> lists);
    void removeList(QString name);

    QList<RandomItemList> getContent();

    void clear();

    QString getFilePath() const;
    void setFilePath(const QString &filePath);

    RandomItemList findList(QString listName);

    void save();

signals:

public slots:

protected:
    QString m_filePath;
    QList<RandomItemList> m_allLists;
};

#endif // REPOSITORY_H
