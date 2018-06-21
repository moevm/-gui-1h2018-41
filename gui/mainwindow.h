#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include "widgets/mylistwidget.h"

// убрать
#include "libs/jsonparser/json.h"


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

private:
    Ui::MainWindow *ui;

    QList<MyListWidget*> m_listsWidgets;

    void initWidgets();
};

#endif // MAINWINDOW_H
