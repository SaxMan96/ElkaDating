#include "signindialog.h"
#include "ui_signindialog.h"
#include "QPushButton"

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),SLOT(on_apply_clicked()));
    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("Sign in");
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

void SignInDialog::on_apply_clicked()
{

    //TODO send data to server with login data

}
