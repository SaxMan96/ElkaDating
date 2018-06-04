#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "QPushButton"

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),SLOT(on_reset_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),SLOT(on_apply_clicked()));
    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("Sign Up");

}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

int SignUpDialog::validateData(QString name, QString surname, QString  email, QString password, QString  password2)
{
    errorText = "ERROR, invalid: ";
    int flag = 1;
    if ( !name.length() ){
        flag = 0;
        errorText += "\tname\n\t";
    }
    if ( !surname.length() ){
        flag = 0;
        errorText += "\tsurname\n\t";
    }
    std::string emailString = email.toUtf8().constData();

    if ( emailString.find("@elka.pw.edu.pl") == std::string::npos) {
        flag = 0;
        errorText += "\temail\n\t";
    }
    if ( !password.length() && password.compare(password2) )
    {
        flag = 0;
        errorText += "\tpassword";
    }

    if (!flag)
        showError();

    return flag;
}

void SignUpDialog::showError()
{
    ui->plainTextEdit->document()->setPlainText(errorText);
}

void SignUpDialog::on_reset_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
}

void SignUpDialog::on_apply_clicked()
{
    QString name = ui->lineEdit->text();
    QString surname = ui->lineEdit_2->text();
    QString email = ui->lineEdit_3->text();
    QString password = ui->lineEdit_4->text();
    QString password2 = ui->lineEdit_5->text();

    //TODO valid password and email (from @elka.pw.edu.pl)
    if (validateData(name, surname, email, password, password2))
    {
        //TODO send sign up package
    }
}
