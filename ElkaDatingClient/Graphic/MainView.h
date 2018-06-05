#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QDialog>
#include "ui_MainView.h"
#include <signindialog.h>
#include <signupdialog.h>

namespace Ui {
class MainView;
}

class MainView : public QDialog
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void on_signUpButton_clicked();
    void on_signInButton_clicked();
private:
    Ui::MainView *ui;

};

#endif // MAINVIEW_H
