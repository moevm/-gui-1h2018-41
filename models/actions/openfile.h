#ifndef OPENFILE_H
#define OPENFILE_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

#include "libs/jsonparser/json.h"

#include "models/types/randomitemlist.h"

class OpenFile
{
public:
    OpenFile();

    QList<RandomItemList> start();
    static QList<RandomItemList> parse(QString data);
    QString path() const;

protected:
    QString m_path;
};

#endif // OPENFILE_H
