#include "signindialog.h"
#include "ui_signindialog.h"
#include "QPushButton"
#include "WeekView.h"
#include "MainView.h"


SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),SLOT(on_apply_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Close), SIGNAL(clicked()),SLOT(on_close_clicked()));

    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("Sign in");


}

SignInDialog::~SignInDialog()
{
    delete ui;
}

int SignInDialog::validateData(QString name, QString password){
    QString errorText = "ERROR, invalid: ";
    int flag = 1;
    if ( !name.length() ){
        flag = 0;
        errorText += "\tname\n\t";
    }
    if ( !password.length() )
    {
        flag = 0;
        errorText += "\tpassword";
    }

    if (flag)
        errorText = "";
    showError(errorText);



    return flag;
}

void SignInDialog::showError(QString errorText)
{
    ui->plainTextEdit->document()->setPlainText(errorText);
}

void SignInDialog::on_apply_clicked()
{
    QString name = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if (validateData(name, password))
    {
        // TODO send data to server with login data
        // TODO odbierz z serwera status uzytkownika
        //jesli prowadzacy
            // TODO odbierz z serwera eventy
            // zmien "send" ukryj prowadzacych i wyswietla kalendarz
        this->close();
        WeekView weekView;
        weekView.setWindowTitle("Week view");
        weekView.setModal(true);
        weekView.setWindowState(Qt::WindowMaximized);
        weekView.exec();
    }
}

void SignInDialog::on_close_clicked()
{
    this->close();
    MainView mainView;
    mainView.setWindowTitle("Main view");
    mainView.setModal(true);
    mainView.setWindowState(Qt::WindowMaximized);
    mainView.exec();
}
