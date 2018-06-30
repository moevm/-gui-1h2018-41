#include "mylistwidget.h"

MyListWidget::MyListWidget(ListState state, QWidget *parent) :
    QWidget(parent),
    m_state(state),
    m_edit(false)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    //this->layout()->setContentsMargins(0, 5, 0, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setContentsMargins(0, 0, 0, 0);

    QFrame* titleFrame = new QFrame(container);
    titleFrame->setLayout(new QHBoxLayout(titleFrame));
    titleFrame->layout()->setContentsMargins(0, 0, 0, 0);
        m_titleWidget = new QLineEdit(m_state.listName, titleFrame);
        m_titleWidget->setEnabled(false);
        //m_titleWidget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_titleWidget->setStyleSheet("border:1px solid #dfdfdf; border-radius: 5px; padding:5px;");
        m_titleWidget->setPlaceholderText("Введите название списка");
        QObject::connect(m_titleWidget, SIGNAL(returnPressed()), this, SLOT(onEditAndSavePressed()));
        titleFrame->layout()->addWidget(m_titleWidget);

        m_needToFindWidget = new QLineEdit(QString::number(1), titleFrame);
        m_needToFindWidget->setMaximumWidth(50);
        m_needToFindWidget->setEnabled(false);
        m_needToFindWidget->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_needToFindWidget->setStyleSheet("background-color:#fff; border:1px solid #dfdfdf; border-radius:5px; padding:5px;");
        QObject::connect(m_needToFindWidget, SIGNAL(returnPressed()), this, SLOT(onEditAndSavePressed()));
        titleFrame->layout()->addWidget(m_needToFindWidget);

        m_editAndSavePushButton = new QPushButton("Edit", titleFrame);
        QObject::connect(m_editAndSavePushButton, SIGNAL(clicked(bool)), this, SLOT(onEditAndSavePressed()));
        titleFrame->layout()->addWidget(m_editAndSavePushButton);
    container->layout()->addWidget(titleFrame);

    QFrame* tagsFrame = new QFrame(container);
    tagsFrame->setLayout(new QHBoxLayout(tagsFrame));
    tagsFrame->layout()->setContentsMargins(0, 0, 0, 0);
        m_tagsWidget = new QLineEdit(tagsFrame);
        m_tagsWidget->setEnabled(false);
        m_tagsWidget->setStyleSheet("border:1px solid #dfdfdf; border-radius: 5px; padding:5px;");
        m_tagsWidget->setPlaceholderText("Тэги");
        QObject::connect(m_tagsWidget, SIGNAL(returnPressed()), this, SLOT(onEditAndSavePressed()));
        tagsFrame->layout()->addWidget(m_tagsWidget);
    container->layout()->addWidget(tagsFrame);


        QFrame* mainFrame = new QFrame(container);
        mainFrame->setLayout(new QVBoxLayout(mainFrame));
        mainFrame->layout()->setContentsMargins(0, 0, 0, 0);

            QFrame* selectionFrame = new QFrame(mainFrame);
            selectionFrame->setLayout(new QHBoxLayout(selectionFrame));
            selectionFrame->layout()->setContentsMargins(0, 0, 0, 0);
            selectionFrame->layout()->setAlignment(Qt::AlignTop);
                QPushButton* selectAllButton = new QPushButton("Выбрать", selectionFrame);
                QObject::connect(selectAllButton, SIGNAL(clicked(bool)), this, SLOT(select()));
                selectionFrame->layout()->addWidget(selectAllButton);
                QPushButton* unSelectAllButton = new QPushButton("Снять", selectionFrame);
                QObject::connect(unSelectAllButton, SIGNAL(clicked(bool)), this, SLOT(unselect()));
                selectionFrame->layout()->addWidget(unSelectAllButton);
            mainFrame->layout()->addWidget(selectionFrame);

            QFrame* listFrame = new QFrame(mainFrame);
            listFrame->setLayout(new QVBoxLayout(listFrame));
            listFrame->layout()->setContentsMargins(0, 0, 0, 0);
                m_listWidget = new QListWidget(container);
                updateWidgets();
                m_listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
                listFrame->layout()->addWidget(m_listWidget);
            mainFrame->layout()->addWidget(listFrame);

            QFrame* actionsFrame = new QFrame(mainFrame);
            actionsFrame->setLayout(new QHBoxLayout(actionsFrame));
            actionsFrame->layout()->setContentsMargins(0, 0, 0, 0);
            actionsFrame->layout()->setAlignment(Qt::AlignTop);
                QPushButton* addButton = new QPushButton("+", actionsFrame);
                QObject::connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addItem()));
                actionsFrame->layout()->addWidget(addButton);
                QPushButton* deleteButton = new QPushButton("-", actionsFrame);
                QObject::connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteItem()));
                actionsFrame->layout()->addWidget(deleteButton);
            mainFrame->layout()->addWidget(actionsFrame);
        container->layout()->addWidget(mainFrame);
        this->layout()->addWidget(container);
}

ListState MyListWidget::getCurrentListState()
{
    return m_state;
}

void MyListWidget::updateWidgets()
{
    m_listWidget->clear();

    m_titleWidget->setText(m_state.listName);
    m_needToFindWidget->setText(QString::number(m_state.needToFind));

    QString tags = "";
    for(auto tag : m_state.tags)
    {
        tags += QStringLiteral("+") + tag;
    }
    m_tagsWidget->setText(tags);

    for(auto item : m_state.listItems)
    {
        QListWidgetItem* listItem = new QListWidgetItem(m_listWidget);
        MyListWidgetItem* widget = new MyListWidgetItem(item.title,
                                                        item.count,
                                                        item.selected,
                                                        m_listWidget);
        QObject::connect(widget, SIGNAL(save()), this, SLOT(onItemChanged()));
        listItem->setSizeHint(widget->minimumSizeHint());
        m_listWidget->addItem(listItem);
        m_listWidget->setItemWidget(listItem, widget);
    }
}

void MyListWidget::addItem()
{
    ItemState emptyItem;
    emptyItem.title = "";
    emptyItem.count = 1;
    emptyItem.selected = true;
    m_state.listItems.push_back(emptyItem);
    updateWidgets();
    m_listWidget->setCurrentRow(m_listWidget->count() - 1);
}

void MyListWidget::deleteItem()
{
    QList<QListWidgetItem*> selectedItems = m_listWidget->selectedItems();
    for(auto item : selectedItems)
    {
        MyListWidgetItem* itemWidget = qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(item));

        if(itemWidget != nullptr)
        {
            ItemState content;
            content.title = itemWidget->title();
            content.count = itemWidget->count();
            content.selected = itemWidget->checked();

            m_state.listItems.removeOne(content);
        }
    }
    updateWidgets();
}

void MyListWidget::onItemChanged()
{
    if(m_listWidget->count() == m_state.listItems.size())
    {
        for(int i = 0; i < m_listWidget->count(); i++)
        {
            MyListWidgetItem* itemWidget =
                    qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->item(i)));
            QObject::disconnect(itemWidget, SIGNAL(save()), this, SLOT(onItemChanged()));

            ItemState item;
            item.title = itemWidget->title();
            item.count = itemWidget->count();
            item.selected = itemWidget->checked();

            m_state.listItems[i] = item;
        }

        QModelIndex index = m_listWidget->currentIndex();
        updateWidgets();
        m_listWidget->setCurrentIndex(index);
    }
}

void MyListWidget::onTitleChanged()
{
    m_state.listName = m_titleWidget->text();
}

void MyListWidget::onNeedToFindChanged()
{
    m_state.needToFind = m_needToFindWidget->text().toUInt();
}

void MyListWidget::onTagsEditingFinished()
{
    m_state.tags = m_tagsWidget->text().split("+", QString::SkipEmptyParts);
}

void MyListWidget::onEditAndSavePressed()
{
    if(m_edit)
    {
        m_titleWidget->setEnabled(false);
        m_needToFindWidget->setEnabled(false);
        m_tagsWidget->setEnabled(false);
        m_editAndSavePushButton->setText("Edit");

        m_state.needToFind = m_needToFindWidget->text().toUInt();
        m_state.listName = m_titleWidget->text();
        m_state.tags = m_tagsWidget->text().split("+", QString::SkipEmptyParts);
    }
    else
    {
        m_titleWidget->setEnabled(true);
        m_needToFindWidget->setEnabled(true);
        m_tagsWidget->setEnabled(true);
        m_editAndSavePushButton->setText("Save");
    }
    m_edit = !m_edit;
}

void MyListWidget::select()
{
    QList<QListWidgetItem*> selectedItems = m_listWidget->selectedItems();
    for(auto selectedItem : selectedItems)
    {
        MyListWidgetItem* itemWidget =
                qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(selectedItem));
        itemWidget->setSelected(true);
    }
}

void MyListWidget::unselect()
{
    QList<QListWidgetItem*> selectedItems = m_listWidget->selectedItems();
    for(auto selectedItem : selectedItems)
    {
        MyListWidgetItem* itemWidget =
                qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(selectedItem));
        itemWidget->setSelected(false);
    }
}

void MyListWidget::selectItem(QModelIndex index)
{
    int row = index.row();
    MyListWidgetItem* itemWidget =
            qobject_cast<MyListWidgetItem*>(m_listWidget->itemWidget(m_listWidget->item(row)));
    itemWidget->setSelected(!itemWidget->selected());
}
