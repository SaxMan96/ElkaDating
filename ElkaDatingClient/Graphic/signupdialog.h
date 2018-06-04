#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QAbstractButton>
#include <QDialog>
#include "string"

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    enum data{
        nameField,
        surnameField,
        emailField,
        passwordField
    };

    ~SignUpDialog();

private:
    int validateData(QString name, QString surname, QString  email, QString password, QString  password2);
    void showError();
    QString errorText;

private slots:
    void on_reset_clicked();
    void on_apply_clicked();

private:
    Ui::SignUpDialog *ui;
};

#endif // SIGNUPDIALOG_H
