#include "datingmain.h"
#include "ui_datingmain.h"

datingMain::datingMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::datingMain)
{
    ui->setupUi(this);
}

datingMain::~datingMain()
{
    delete ui;
}
