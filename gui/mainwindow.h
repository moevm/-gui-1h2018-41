#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QFileDialog>

#include "widgets/mylistwidget.h"
#include "models/repository/repository.h"
#include "models/actions/randomizer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_openPushButton_clicked();

    void on_actionOpen_triggered();

    void on_randomizePushButton_clicked();

private:
    Ui::MainWindow *ui;

    QList<MyListWidget*> m_listsWidgets;

    Repository repo;

    void initWidgets();
};

#endif // MAINWINDOW_H
