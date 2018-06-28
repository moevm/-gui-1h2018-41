#ifndef MYMDISUBWINDOW_H
#define MYMDISUBWINDOW_H

#include <QMdiSubWindow>
#include <QCloseEvent>

class MyMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    MyMdiSubWindow(QWidget *parent = nullptr);

protected:
    void closeEvent( QCloseEvent * closeEvent );
signals:
    void closed( const QString );
};

#endif // MYMDISUBWINDOW_H
