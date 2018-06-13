#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>
#include <QDebug>

#include "widgets/mylistwidgetitem.h"

class MyListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QString name, QStringList items, QWidget *parent = nullptr);

private:
    QString m_listName;
    QStringList m_items;

    QListWidget* m_listWidget;
    void updateList();

signals:

public slots:

private slots:
    void addItem();
    void deleteItem();
};

#endif // MYLISTWIDGET_H
