#ifndef DATINGMAIN_H
#define DATINGMAIN_H

#include <QMainWindow>

namespace Ui {
class datingMain;
}

class datingMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit datingMain(QWidget *parent = 0);
    ~datingMain();

private:
    Ui::datingMain *ui;
};

#endif // DATINGMAIN_H
