#ifndef SELECTLISTDIALOG_H
#define SELECTLISTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectListDialog;
}

class SelectListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectListDialog(QWidget *parent = 0);
    ~SelectListDialog();

signals:
    void selectList(QString listName);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SelectListDialog *ui;
};

#endif // SELECTLISTDIALOG_H
