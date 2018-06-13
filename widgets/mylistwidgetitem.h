#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QWidget>

#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QLayout>

class MyListWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidgetItem(QString item, size_t count, bool checked, QWidget *parent = nullptr);

    QString item() const;

signals:

public slots:
private:
    QString m_item;
    size_t m_count;
    bool m_checked;
};

#endif // MYLISTWIDGETITEM_H
