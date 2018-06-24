#include "selectlistdialog.h"
#include "ui_selectlistdialog.h"

SelectListDialog::SelectListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectListDialog)
{
    ui->setupUi(this);
}

SelectListDialog::~SelectListDialog()
{
    delete ui;
}

void SelectListDialog::on_buttonBox_accepted()
{
    emit selectList(ui->listNameLineEdit->text());
}
