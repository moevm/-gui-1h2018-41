#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "widgets/mylistwidget.h"
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
    static QList<RandomItemList> toModelFormat(QList<ListState> listsStates);

private slots:

    void on_actionOpen_triggered();

    void on_randomizePushButton_clicked();

    void on_actionClear_triggered();

    void on_actionSave_triggered();

    void on_actionAdd_List_triggered();

    void on_actionRemove_List_triggered();

    void removeList(QString listTitle);

private:
    Ui::MainWindow *ui;

    Repository m_repo;

    void initWidgets();
    void clear();
};

#endif // MAINWINDOW_H
