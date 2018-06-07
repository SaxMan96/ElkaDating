#ifndef WEEKVIEW_H
#define WEEKVIEW_H

#include <QDialog>
#include <QListWidgetItem>
#include <unordered_map>
#include <vector>

namespace Ui {
class WeekView;
}

class WeekView : public QDialog
{
    Q_OBJECT

public:
    explicit WeekView(QWidget *parent = 0);
    void setLecturersMap(std::unordered_map<unsigned int ,std::pair<std::string, std::string>> l);
    ~WeekView();

private slots:
    void on_lecturers_itemClicked(QListWidgetItem *item);
    void on_logoutButton_clicked();
    void on_forwardButton_clicked();
    void on_backButton_clicked();
    void on_modeButton_clicked();
    void on_pushButton_clicked();

private:
    unsigned int userID;
    std::unordered_map<unsigned int ,std::pair<std::string, std::string>> lecturers;
    std::unordered_map<int ,unsigned int> rowsNumber;
    Ui::WeekView *ui;
};

#endif // WEEKVIEW_H
