#include "MainView.h"


MainView::MainView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::on_signInButton_clicked()
{
    this->close();
    SignInDialog signInDialog;
    signInDialog.setWindowTitle("Sign in");
    signInDialog.setModal(true);
    signInDialog.setWindowState(Qt::WindowMaximized);
    signInDialog.exec();
}
void MainView::on_signUpButton_clicked()
{
    this->close();
    SignUpDialog signUpDialog;
    signUpDialog.setWindowTitle("Sign up");
    signUpDialog.setModal(true);
    signUpDialog.setWindowState(Qt::WindowMaximized);
    signUpDialog.exec();
}
