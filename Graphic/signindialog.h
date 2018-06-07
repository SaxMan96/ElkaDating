#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H
#include "../ElkaDatingServ/MessageContentParser.hpp"
#include "ui_signindialog.h"
#include "QPushButton"
#include "WeekView.h"
#include "MainView.h"
#include "Client.hpp"
#include "Dialog.h"
#include <QDialog>

namespace Ui {
class SignInDialog;
}

class SignInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignInDialog(QWidget *parent = 0);
    ~SignInDialog();

private slots:
    void on_apply_clicked();
    void on_close_clicked();

private:
    Ui::SignInDialog *ui;
    int validateData(QString name, QString password);
    void showError(QString errorText);
};

#endif // SIGNINDIALOG_H
