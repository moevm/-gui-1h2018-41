#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>

class MyListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QString name, QStringList items, QWidget *parent = nullptr);

signals:

public slots:
private:
    QString m_listName;
    QStringList m_items;
};

#endif // MYLISTWIDGET_H
