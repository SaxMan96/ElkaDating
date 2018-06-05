#ifndef SIGNINDIALOG_H
#define SIGNINDIALOG_H

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
