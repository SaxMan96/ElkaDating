#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "QPushButton"

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),SLOT(on_reset_clicked()));


}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

void SignUpDialog::on_buttonBox_clicked(QAbstractButton *button)
{

//    if (ui->buttonBox->button(QDialogButtonBox::Apply))
//    {
//        ui->lineEdit->setText("");
//        ui->lineEdit_2->setText("");
//        ui->lineEdit_3->setText("");
//        ui->lineEdit_4->setText("");
//        ui->lineEdit_5->setText("");
//        ui->lineEdit_6->setText("");
//    }
}

void SignUpDialog::on_reset_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
}
