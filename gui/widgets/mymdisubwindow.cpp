#include "mymdisubwindow.h"

MyMdiSubWindow::MyMdiSubWindow(QWidget *parent) :
    QMdiSubWindow(parent)
{

}

void MyMdiSubWindow::closeEvent(QCloseEvent *closeEvent)
{
    emit closed(this->objectName());
    closeEvent->accept();
}
