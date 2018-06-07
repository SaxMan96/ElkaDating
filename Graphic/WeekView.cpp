#include "WeekView.h"
#include "ui_WeekView.h"
#include <QScrollBar>
#include <QDate>
#include "string"

WeekView::WeekView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeekView)
{
    ui->setupUi(this);
    ui->dateHeader->setAlignment(Qt::AlignCenter);

    connect(ui->dhour->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d1->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d1->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->dhour->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d1->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d2->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d2->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d1->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d2->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d3->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d3->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d2->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d3->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d4->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d4->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d3->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d4->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d5->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d5->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d4->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d5->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d6->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d6->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d5->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d6->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d7->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->d7->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->d6->verticalScrollBar(), SLOT(setValue(int)));

    QStringList listOfLecturers;
    std::unordered_map<std::string, int>::iterator it = lecturers.begin();
    QString tmp = "";
    // Iterate over the map using iterator
    while(it != lecturers.end())
    {
        tmp = "";
        tmp += it->second->first;
        tmp += " ";
        tmp += it->second->second;
        listOfLecturers += tmp;
        it++;
    }

//    listOfLecturers.push_front();
//    ui->lecturers->addItems()

//    ui->dhour->setBaseSize(30,30);
    //    ui->dhour->set
}

void WeekView::setLecturersMap(std::unordered_map<unsigned int, std::pair<std::__cxx11::string, std::__cxx11::string> > l)
{
    lecturers = l;
}

WeekView::~WeekView()
{
    delete ui;
}

void WeekView::on_lecturers_itemClicked(QListWidgetItem *item)
{
    int lecturerRowId = ui->lecturers->row(item);
//    ui->userName->document()->setPlainText(QString::number(lecturerId));
    unsigned int lecturerName;
    //lecturerName = rowsNumber.find(lecturerRowId);
    // TODO wyslij zapytanie do serwera o eventy prowadzacego
    // TODO wyslij zapytanie do serwera o eventy swoje u prowadzacego

    //sendRequest(userId, lecturersList.id(item->text());

    // TODO odbierz liste terminow prowadzacego
    // TODO odbierz liste terminow swoja
    // TODO zaznacz terminy

//    QString tmp = item->text();
//    ui->userName->document()->setPlainText(tmp);
//    ui->d1->item(1)->setBackgroundColor("red");
//    ui->d1->item(1)->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);

}
void WeekView::on_logoutButton_clicked()
{
    // TODO wyslij pakiet wylogowanie
    // TODO przejdz do MainWindow
}

void WeekView::on_forwardButton_clicked()
{
    // TODO oblicz nastepny tydzien
    // TODO wyslij zapytanie do serwera
    // TODO wyswietl eventy
    // TODO zmien date
}

void WeekView::on_backButton_clicked()
{
    // TODO oblicz poprzedni tydzien
    // TODO wyslij zapytanie do serwera
    // TODO wyswietl eventy
    // TODO zmien date
}

void WeekView::on_modeButton_clicked()
{
    // TODO wyswietl liste prowadzacych
    // TODO zmien stan
}

void WeekView::on_pushButton_clicked()
{
    // TODO znajdz ostatnia niedziele - przypisz date do d1 ... d7
    // TODO przetworzyc dane na liste eventow z godz poczatkowa i koncowa + data
    // TODO stwórz pakiet (wez id prowadzacego, wez moje id, data poczaatkowa, data konca, nazwa, description, teachermode), zakoduj i wyslij


//    QDate date;

//    /*    date.setDate(*/
//    //    date.setDate(2018,5,3);
//        int day = date.dayOfWeek();
//        QString weekDay = QDate::longDayName(day);
//        ui->userName->document()->setPlainText(weekDay);

    //    QList *events = ui->d1->selectedItems();

}
