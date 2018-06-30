#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QMessageBox>

#include <random>

#include "gui/widgets/mylistwidget.h"
#include "gui/widgets/mymdisubwindow.h"

#include "models/repository/repository.h"
#include "models/actions/randomizer.h"
#include "models/actions/savetofile.h"
#include "models/actions/openfile.h"

#include "gui/selectlistdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static QList<ListState> toGuiFormat(QList<RandomItemList> lists);
    static ListState toGuiFormat(RandomItemList list);
    static QList<RandomItemList> toModelFormat(QList<ListState> listsStates);
    static QString generateRandomLabelText();
    static QString generateHelloMessage();

private slots:
    void on_randomizePushButton_clicked();

    void on_actionSave_triggered();

    void on_actionAdd_List_triggered();

    void on_actionRemove_List_triggered();

    void removeList(QString listTitle);

    void on_actionMenu_triggered();

    void on_menuListWidget_itemDoubleClicked(QListWidgetItem *item);

    void onMyMdiSubWindowClosed(QString objectName);

    void on_findByTagLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Repository m_repo;

    void initWidgets();
    void openLibrary();
};

#endif // MAINWINDOW_H
