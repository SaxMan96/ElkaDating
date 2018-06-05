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

#include "Event.hpp"
#include "Term.hpp"

const QString DATE_FORMAT = "yyyy.MM.dd.hh.mm";

enum DBoperationResult{
    //notUniqueLogin,
    //notPlayerWithSpecifiedLogin,

    addSuccess,
    deleteSuccess,
    cancelSuccess,//były decline
    acceptSuccess,

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



private:
    DBManager();
    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

    static DBManager* pInstance_;
    pthread_mutex_t dbMutex_;
    QSqlDatabase serverDB_;

    bool teacherHasTerm(unsigned int, Term,Term);
    QString constructDateTime(Term);
    bool userExists(unsigned int);
    bool eventExists(unsigned int);

};

#endif // DBMANAGER_HPP
