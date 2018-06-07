#include "Dialog.h"
#include "ui_Dialog.h"
#include "QTextEdit"
#include "QPlainTextEdit"
#include "QPushButton"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->btnOK, SIGNAL(on_btnOK_clicked()), this, SLOT(close()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeText(std::__cxx11::string tmp)
{
    ui->plainTextEdit->document()->setPlainText(QString::fromStdString(tmp));
}

void Dialog::on_btnOK_clicked()
{
    close();
}

