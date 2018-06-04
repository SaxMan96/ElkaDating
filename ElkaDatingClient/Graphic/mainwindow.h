#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <signindialog.h>
#include <signupdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_signInButton_clicked();

    void on_signUpButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
