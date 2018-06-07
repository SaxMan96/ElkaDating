#include "signindialog.h"
#include "Message.hpp"

SignInDialog::SignInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignInDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),SLOT(on_apply_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Close), SIGNAL(clicked()),SLOT(on_close_clicked()));

    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("Sign in");
}

SignInDialog::~SignInDialog()
{
    delete ui;
}

int SignInDialog::validateData(QString email, QString password){
    QString errorText = "ERROR, invalid: ";
    int flag = 1;
    std::string emailString = email.toUtf8().constData();

    if ( emailString.find("@elka.pw.edu.pl") == std::string::npos) {
        flag = 0;
        errorText += "\temail\n\t";
    }
    if ( !password.length() )
    {
        flag = 0;
        errorText += "\tpassword";
    }

    if (flag)
        errorText = "";
    showError(errorText);



    return flag;
}

void SignInDialog::showError(QString errorText)
{
    ui->plainTextEdit->document()->setPlainText(errorText);
}

void SignInDialog::on_apply_clicked()
{
    QString email = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if (validateData(email, password))
    {
        Message msg;
        Client::getInstance().sendMessage(msg.getSignInMessage(email.toUtf8().constData(),password.toUtf8().constData()));
        Message *recMsg = Client::getInstance().getMessageFromQueue();
        if (recMsg->getMsgType() == LOGIN)
        {
            Dialog dialog;

            dialog.setModal(true);
            QString title = "";
            bool succeded = false;
            switch (recMsg->getMsgSubType())
            {
                case SUCCESFULL:
                    succeded = true;
                    title = "SUCCESFULL LOG IN";
                    break;
                case WRONG_PASS:
                    title = "WRONG PASSWORD";
                    break;
                case WRONG_USERNAME:
                    title = "WRONG USERNAME";
                    break;
            }

            dialog.setWindowTitle(title);
            dialog.changeText(recMsg->getMsgDataBufor());
            dialog.exec();

            if (succeded)
            {
                // TODO odbierz liste prowadzacych
                // TODO odbierz z serwera status uzytkownika
                // TODO odbierz z serwera eventy
                //jesli prowadzacy
                    // zmien "send" ukryj prowadzacych i wyswietla kalendarz
                recMsg = Client::getInstance().getMessageFromQueue();
                MessageContentParser::getInstance().parseMessageContent(recMsg);
                TeacherMapMessageContent *TMMC = static_cast <TeacherMapMessageContent*> (recMsg->getContent());
                std::unordered_map<unsigned int ,std::pair<std::string, std::string>> lecturers = TMMC->getTeacherMap();

                this->close();
                WeekView weekView;
                weekView.setLecturersMap(lecturers);
                weekView.setWindowTitle("Week view");
                weekView.setModal(true);
                weekView.setWindowState(Qt::WindowMaximized);
                weekView.exec();
            }
        }


    }
}

void SignInDialog::on_close_clicked()
{
    this->close();
    MainView mainView;
    mainView.setWindowTitle("Main view");
    mainView.setModal(true);
    mainView.setWindowState(Qt::WindowMaximized);
    mainView.exec();
}
