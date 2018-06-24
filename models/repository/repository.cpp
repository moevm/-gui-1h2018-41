#include "repository.h"

Repository::Repository(QObject *parent) : QObject(parent)
{

}

void Repository::setContent(QList<RandomItemList> lists)
{
    m_lists = lists;
}

QList<RandomItemList> Repository::getContent()
{
    return m_lists;
}

void Repository::clear()
{
    m_lists.clear();
}

QString Repository::getFilePath() const
{
    return m_filePath;
}

void Repository::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}
