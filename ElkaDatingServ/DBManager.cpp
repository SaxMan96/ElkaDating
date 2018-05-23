#include "DBManager.hpp"

DBManager::DBManager()
{
    serverDB_ = QSqlDatabase::addDatabase("QSQLITE");
    serverDB_.setDatabaseName("server_database.db");

    if(!serverDB_.open())
    {
        throw DBManagerInitError();
    }
}

void DBManager::testDataBaseConnection()
{
    if(!serverDB_.open())
    {
        throw DBManagerInitError();
    }
}

void DBManager::addStudentTermPref(char* a)
{
    if(!serverDB_.open())
    {
        throw DBManagerInitError();
    }
}

//http://doc.qt.io/qt-5/qsqldatabase.html
