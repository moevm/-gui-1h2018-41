#ifndef SAVETOFILE_H
#define SAVETOFILE_H

#include <QString>
#include <QFile>
#include <QFileDialog>

#include "models/types/randomitemlist.h"
#include "libs/jsonparser/json.h"

class SaveToFile
{
public:
    SaveToFile(QString path = "");

    void setFilePath(const QString &filePath);

    void setContent(const QList<RandomItemList> &content);

    void start();

protected:
    QString m_filePath;
    QList<RandomItemList> m_content;

    QByteArray contentToByteArray();
};

#endif // SAVETOFILE_H
