#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signInButton_clicked()
{
    SignInDialog signInDialog;
    signInDialog.setWindowTitle("Sign in");
    signInDialog.setModal(true);
    signInDialog.exec();
}
void MainWindow::on_signUpButton_clicked()
{
    SignUpDialog signUpDialog;
    signUpDialog.setWindowTitle("Sign up");
    signUpDialog.setModal(true);
    signUpDialog.exec();
}
