#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    ~SignUpDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_reset_clicked();

private:
    Ui::SignUpDialog *ui;
};

#endif // SIGNUPDIALOG_H
