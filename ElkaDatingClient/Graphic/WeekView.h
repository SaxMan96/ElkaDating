#ifndef WEEKVIEW_H
#define WEEKVIEW_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class WeekView;
}

class WeekView : public QDialog
{
    Q_OBJECT

public:
    explicit WeekView(QWidget *parent = 0);
    ~WeekView();

private slots:
    void on_lecturers_itemClicked(QListWidgetItem *item);

private:
    Ui::WeekView *ui;
};

#endif // WEEKVIEW_H
