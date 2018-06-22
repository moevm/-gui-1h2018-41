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

struct ItemState
{
    QString title;
    bool selected;
    size_t count;

    bool operator != (const ItemState &state)
    {
        return (title != state.title) || (selected != state.selected) || (count != state.count);
    }

    bool operator == (const ItemState &state)
    {
        return (title == state.title) && (selected == state.selected) && (count == state.count);
    }
};

struct ListState
{
    QString listName;
    QList<ItemState> listItems;
};

class MyListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(ListState state, QWidget *parent = nullptr);

    ListState getCurrentListState();

private:
    ListState m_state;

    QLineEdit* m_titleWidget;
    QListWidget* m_listWidget;
    void updateWidgets();

signals:

public slots:

private slots:
    void addItem();
    void deleteItem();
    void onItemChanged();
    void onTitleChanged();
};

#endif // MYLISTWIDGET_H
