#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QCheckBox>
#include <QDebug>

#include "gui/widgets/mylistwidgetitem.h"

class MyListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QString name, QList< QMap<QString, QString> > items, QWidget *parent = nullptr);

    QList<QMap<QString, QString> > getCurrentListState();

private:
    QString m_listName;
    QList< QMap<QString, QString> > m_list;

    QListWidget* m_listWidget;
    void updateList();

signals:

public slots:

private slots:
    void addItem();
    void deleteItem();
    void onItemChanged();
};

#endif // MYLISTWIDGET_H
