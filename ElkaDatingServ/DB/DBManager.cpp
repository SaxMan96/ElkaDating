#include "DB/DBManager.hpp"

DBManager::DBManager()
{
    serverDB_ = QSqlDatabase::addDatabase("QSQLITE");
    serverDB_.setDatabaseName("server_database.db");

    if(!serverDB_.open())
    {
        throw DBManagerInitError();
    }
}

int DBManager::addStudentTermPref(unsigned int studentID, unsigned int teacherID, Term startTerm, Term endTerm)
{
    pthread_mutex_lock(&dbMutex_);

    if( ! userExists(studentID))
        //TODO return DBoperationResult::notUniqueLogin;
    if( ! userExists(teacherID))
        //TODO return DBoperationResult::notUniqueLogin;
    if( ! teacherHasTerm(teacherID, startTerm, endTerm)){}
        //TODO

    QSqlQuery query;
    query.prepare(
        "INSERT INTO Event("
        "   userID,   lecturerID,   name,   description,   startTime,   endTime) "
        "values ("
        " (:userID),(:lecturerID),(:name),(:description),(:startTime),(:endTime))");
    query.bindValue(":userID",studentID);
    query.bindValue(":lecturerID",teacherID);
    query.bindValue(":name",QString::fromStdString(""));
    query.bindValue(":description",QString::fromStdString(""));
    query.bindValue(":startTime",constructDateTime(startTerm));
    query.bindValue(":endTime",constructDateTime(endTerm));

    int result;

    if(query.exec())
        result = ::addSuccess;
    else
        result = DBoperationResult::dateBaseError;

    pthread_mutex_unlock(&dbMutex_);
    return result ;
}

int DBManager::cancelStudentTermPref(unsigned int eventID, unsigned int studentID)
{
    pthread_mutex_lock(&dbMutex_);

    if( ! eventExists(eventID)){}
        //TODO return DBoperationResult::notUniqueLogin;

    QSqlQuery query;
    query.prepare(
                "DELETE FROM Event WHERE ("
                "ID = (:id) AND"
                "userID = (:studentID)"
                ");");
    query.bindValue(":ID",eventID);
    query.bindValue(":userID",studentID);

    int result;
    if(query.exec())
        result = ::addSuccess;
    else
        result = DBoperationResult::dateBaseError;

    pthread_mutex_unlock(&dbMutex_);

    return result ;
}

int DBManager::addEvent(Event event)
{
    pthread_mutex_lock(&dbMutex_);

    QSqlQuery query;
    query.prepare(
        "INSERT INTO Event("
        "   userID,   lecturerID,   name,   description,   startTime,   endTime, teacherEvent, accepted) "
        "values ("
        " (:userID),(:lecturerID),(:name),(:description),(:startTime),(:endTime),(:teacherEvent),(:accepted))");
    query.bindValue(":userID",event.studentID());
    query.bindValue(":lecturerID",event.teacherID());
    query.bindValue(":name",QString::fromStdString(event.name()));
    query.bindValue(":description",QString::fromStdString(event.description()));
    query.bindValue(":startTime",constructDateTime(event.startTerm()));
    query.bindValue(":endTime",constructDateTime(event.endTerm()));
    query.bindValue(":teacherEvent",event.teacherID());
    query.bindValue(":accepted",event.accepted());


    int result;

    if(query.exec())
        result = ::addSuccess;
    else
        result = DBoperationResult::dateBaseError;

    pthread_mutex_unlock(&dbMutex_);
    return result ;
}

int DBManager::deleteEvent(unsigned int eventID, unsigned int userID)
{
    pthread_mutex_lock(&dbMutex_);

    QSqlQuery query;
    query.prepare(
        "DELETE FROM Event WHERE ("
        "ID = (:eventID) AND"
        "userID = (:userID)"
        ");");
    query.bindValue(":eventID",eventID);
    query.bindValue(":userID",userID);

    int result;

    if(query.exec())
        result = deleteSuccess;
    else
        result = DBoperationResult::dateBaseError;

    pthread_mutex_unlock(&dbMutex_);
    return result ;
}

int DBManager::acceptEvent(unsigned int eventID, unsigned int teacherID)
{
    pthread_mutex_lock(&dbMutex_);

    QSqlQuery query;
    query.prepare("UPDATE Event"
                  "SET accept = t"
                  "WHERE ("
                  "eventID = (:eventID) AND"
                  "lecturerID = teacherID"
                  "); ");
    query.bindValue(":eventID",eventID);
    query.bindValue(":teacherID",teacherID);

    int result;

    if(query.exec())
        result = acceptSuccess;
    else
        result = DBoperationResult::dateBaseError;

    pthread_mutex_unlock(&dbMutex_);
    return result ;
}

int DBManager::declineEvent(unsigned int eventID, unsigned int teacherID)
{
    pthread_mutex_lock(&dbMutex_);

    QSqlQuery query;
    query.prepare("UPDATE Event"
                  "SET accept = f"
                  "WHERE ("
                  "eventID = (:eventID) AND"
                  "lecturerID = teacherID"
                  "); ");
    query.bindValue(":eventID",eventID);
    query.bindValue(":teacherID",teacherID);

    int result;

    if(query.exec())
        result = cancelSuccess;
    else
        result = DBoperationResult::dateBaseError;

    pthread_mutex_unlock(&dbMutex_);
    return result ;
}

QString DBManager::constructDateTime(Term term){
    QDateTime startTime;
    QDate* date = new QDate(term.year_, term.mon_, term.day_);
    QTime* time = new QTime(term.hour_, term.min_,0,0);
    startTime.setDate(*date);
    startTime.setTime(*time);
    QString dateString(startTime.toString(DATE_FORMAT));
    return dateString;
}

bool DBManager::eventExists(unsigned int eventID){
    bool exists = false;
    QSqlQuery query;
    query.prepare("SELECT ID FROM Event WHERE ID = (:id)");
    query.bindValue(":id", eventID);
    if(query.exec())
        if(query.next())
            exists = true;
    return exit;
}

bool DBManager::userExists(unsigned int userID)
{
    bool exists = false;
    QSqlQuery query;
    query.prepare("SELECT ID FROM User WHERE ID = (:id)");
    query.bindValue(":id", userID);
    if(query.exec())
        if(query.next())
            exists = true;
    return exit;
}

bool DBManager::teacherHasTerm(unsigned int teacherID, Term startTerm, Term endTerm)
{
    bool exists = false;
    QSqlQuery query;
    query.prepare("SELECT ID FROM Event WHERE ("
                  "userID = (:teacherID)     AND"
                  "startTime <= (:startTime) AND"
                  "startTime <= (:endTime)   AND"
                  "endTime   >= (:startTime) AND"
                  "endTime   >= (:endTime)"
                  ")");
    query.bindValue(":teacherID", teacherID);
    query.bindValue(":startTime", constructDateTime(startTerm));
    query.bindValue(":endTime", constructDateTime(endTerm));

    if(query.exec())

        if(query.next())
            exists = true;
    return exit;
}

void DBManager::testDataBaseConnection()
{
    if(!serverDB_.open())
    {
        throw DBManagerInitError();
    }
}
