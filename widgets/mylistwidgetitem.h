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
    void save();

public slots:
    void onItemUpdated();

private:
    QString m_item;
    size_t m_count;
    bool m_checked;

    QLineEdit* m_itemWidget;
    QLineEdit* m_counWidget;
    QCheckBox* m_selectedCheckBox;
};

#endif // MYLISTWIDGETITEM_H
