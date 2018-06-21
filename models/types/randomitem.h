#ifndef RANDOMITEM_H
#define RANDOMITEM_H

#include <QString>

class RandomItem
{
public:
    explicit RandomItem(QString title = "", bool selected = true, size_t count = 1);

    QString getTitle() const;
    void setTitle(const QString &title);

    bool getSelected() const;
    void setSelected(bool selected);

    size_t getCount() const;
    void setCount(const size_t &count);

protected:
    QString m_title;
    bool m_selected;
    size_t m_count;
};

#endif // RANDOMITEM_H
