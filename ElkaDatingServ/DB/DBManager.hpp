#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include "Exceptions/MyExceptions.hpp"
#include <pthread.h>
#include <QMutex>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTime>
#include <QSqlRecord>
#include <QtWidgets>
#include "Term.hpp"
#include "Event.hpp"
#include "Message.hpp"
#include <unordered_map>
#include <string>
#include <utility>

const QString DATE_FORMAT = "yyyy.MM.dd.hh.mm";

enum DBoperationResult{
    //notUniqueLogin,
    //notPlayerWithSpecifiedLogin,

    // modify Events
    addSuccess,
    deleteSuccess,
    cancelSuccess,//były decline
    acceptSuccess,

    // register User
    existUserName,
    passNotQualify,
    emptyFields,
    registerSuccess,

    //login User
    wrongLogin,
    wrongPassword,
    loginSuccess,

    dateBaseError
};

class DBManager
{
public:
    static DBManager& getInstance(){
        QMutex mutex;
        if(!pInstance_)
        {
            mutex.lock();
            if(!pInstance_)
            {
                pInstance_ = new DBManager();
            }
            mutex.unlock();
        }

        return *pInstance_;
    }

    void testDataBaseConnection();
    int addStudentTermPref(unsigned int, unsigned int, Term, Term);
    int cancelStudentTermPref(unsigned int,unsigned int);
    int addEvent(Event);
    int deleteEvent(unsigned int,unsigned int);
    int acceptEvent(unsigned int,unsigned int);
    int declineEvent(unsigned int,unsigned int);
    int registerNewUser(std::string,std::string,std::string,std::string,bool);
    int loginExistingUser(std::string,std::string);

    std::unordered_map<unsigned int, std::pair<std::string, std::string>> getTeacherMap();

private:
    DBManager();
    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

    static DBManager* pInstance_;
    pthread_mutex_t dbMutex_;
    QSqlDatabase serverDB_;

    QString constructDateTime(Term);
    bool teacherHasTerm(unsigned int, Term,Term);
    bool userExists(unsigned int);
    bool eventExists(unsigned int);

    bool checkExistUserName(std::string userName);
    bool checkPasswordQualify(std::string password);
    bool checkPasswordCorrect(std::string password, std::string userName);
};

#endif // DBMANAGER_HPP
