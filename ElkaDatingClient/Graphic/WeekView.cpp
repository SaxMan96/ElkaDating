#include "WeekView.h"
#include "ui_WeekView.h"

WeekView::WeekView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeekView)
{
    ui->setupUi(this);
//    ui->header->setAlignment(Qt::AlignCenter);
//    ui->dateHeader->setAlignment(Qt::AlignCenter);
    //button(QDialogButtonBox::Apply)->setText("Sign in");


}

WeekView::~WeekView()
{
    delete ui;
}

void WeekView::on_lecturers_itemClicked(QListWidgetItem *item)
{
    QString tmp = item->text();
    ui->userName->document()->setPlainText(tmp);
}
