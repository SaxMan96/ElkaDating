#include "Dialog.h"
#include "ui_Dialog.h"
#include "QTextEdit"
#include "QPlainTextEdit"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::changeText(std::__cxx11::string tmp)
{
    ui->plainTextEdit->document()->setPlainText(QString::fromStdString(tmp));
}

