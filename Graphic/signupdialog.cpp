#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "QPushButton"
#include "MainView.h"
#include "Client.hpp"
#include "Dialog.h"
#include <QDialog>

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),SLOT(on_reset_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),SLOT(on_apply_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()),SLOT(on_cancel_clicked()));

    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("Sign Up");

}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

int SignUpDialog::validateData(QString name, QString surname, QString  email, QString password, QString  password2)
{
    QString errorText = "ERROR, invalid: ";
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
    std::string passwordString = password.toUtf8().constData();
    std::string password2String = password2.toUtf8().constData();

    if ( !password.length() || passwordString != password2String )
    {
        flag = 0;
        errorText += "\tpassword";
    }

    if (flag)
        errorText = "";
    showError(errorText);

    return flag;
}

void SignUpDialog::showError(QString errorText)
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

    if (validateData(name, surname, email, password, password2))
    {
        Message msg;
        Client::getInstance().sendMessage(msg.getSignUpPackage(name, surname, password, email));
        Message *recMsg = Client::getInstance().getMessageFromQueue();
        if (recMsg->getMsgType() == REGISTRATION)
        {
            Dialog dialog;

            dialog.setModal(true);
            QString title = "";
            bool succeded = false;
            switch (recMsg->getMsgSubType())
            {
                case SUCCESFULL:
                    succeded = true;
                    title = "SUCCESFULL REGISTRATION";
                    break;
                case WRONG_PASS:
                    title = "WRONG PASSWORD";
                    break;
                case WRONG_USERNAME:
                    title = "WRONG USERNAME";
                    break;
                case EMPTY_FIELDS:
                    title = "EMPTY FIELDS";
                    break;
                case FAILURE:
                    title = "REGISTRATION FAILED";
                    break;
            }

            dialog.setWindowTitle(title);
            dialog.changeText(recMsg->getMsgDataBufor());
            dialog.exec();

            if (succeded)
            {
                this->close();
                SignInDialog signInDialog;
                signInDialog.setWindowTitle("Sign in");
                signInDialog.setModal(true);
                signInDialog.setWindowState(Qt::WindowMaximized);
                signInDialog.exec();
            }
        }
    }
}

void SignUpDialog::on_cancel_clicked()
{
    this->close();
    MainView mainView;
    mainView.setWindowTitle("Main view");
    mainView.setModal(true);
    mainView.setWindowState(Qt::WindowMaximized);
    mainView.exec();

}

