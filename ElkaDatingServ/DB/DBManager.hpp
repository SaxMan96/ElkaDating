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

#include "Event.hpp"
#include "Term.hpp"

const QString DATE_FORMAT = "yyyy.MM.dd.hh.mm";

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

private:
    DBManager();
    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

    static DBManager* pInstance_;
    mutable pthread_mutex_t dbMutex_;
    QSqlDatabase serverDB_;
    void addStudentTermPref(char *a);
};

#endif // DBMANAGER_HPP
