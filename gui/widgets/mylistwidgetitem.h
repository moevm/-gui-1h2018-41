#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QWidget>

#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QLayout>
#include <QDebug>

class MyListWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit MyListWidgetItem(QString title, size_t count, bool checked, QWidget *parent = nullptr);

    QString title() const;

    size_t count() const;

    bool checked() const;

    void setSelected(bool selected);

signals:
    void save();

public slots:
    void onItemUpdated();

private:
    QString m_title;
    size_t m_count;
    bool m_selected;

    QLineEdit* m_titleWidget;
    QLineEdit* m_countWidget;
    QCheckBox* m_selectedCheckBox;
};

#endif // MYLISTWIDGETITEM_H
