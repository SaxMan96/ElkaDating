#include "MessageHandler.hpp"

MessageHandler::MessageHandler(Client * client)
{
    client_ = client;
}

void MessageHandler::handleMessage(Message* msg){

    msg_ = msg;
    MessageContent* content = msg_->getContent();

    if(msg_->getMsgType() == TERMS_STUDENT)
        termsStudent(content);
    else if(msg_->getMsgType() == TERMS_TEACHER)
        termsTeacher(content);
    else if(msg_->getMsgType() == SEND_MULITIPLE_MSG_TO_STUDENTS)
        sendMultipleMessagesHandle(static_cast<SendMultipleMessageContent*>(content));

}
void MessageHandler::termsStudent(MessageContent* content){
    if(msg_->getMsgSubType() == PREF_TERMS)
        addTermsStudent(static_cast<AddTermPrefMessageContent*>(content));
    else if(msg_->getMsgSubType() == CANCEL_TERMS)
        cancelTermsStudent(static_cast<EditTermPrefMessageContent*>(content));
}
void MessageHandler::termsTeacher(MessageContent* content){
    if(msg_->getMsgSubType() == NEW_TERMS)
       addTermsTeacher(static_cast<AddTermPrefMessageContent*>(content));
    else if(msg_->getMsgSubType() == DELETE_TERM)
        deleteTermsTeacher(static_cast<EditTermPrefMessageContent*>(content));
    else if(msg_->getMsgSubType() == ACCEPT_TERMS)
        acceptTermsTeacher(static_cast<EditTermPrefMessageContent*>(content));
    else if(msg_->getMsgSubType() == DECLINE_TERMS)
        declineTermsTeacher(static_cast<EditTermPrefMessageContent*>(content));
}

void MessageHandler::addTermsStudent(AddTermPrefMessageContent* content){

    unsigned int teacherID = content->getTeacherID();
    std::list<Event> events = content->getEventsList();

    unsigned int studentID = client_->getID();

    int termsCounter = 0;

     for(Event event: events){
        int result = DBManager::getInstance().addStudentTermPref(studentID,teacherID,event.startTerm(),event.endTerm());
        if(result == addSuccess)
            termsCounter++;
    }
    sendNotification(termsCounter,events.size(),
                     "Udało się dodać wszystkie wybranych preferencję",
                     "Udało się dodać część z wybranych preferencji",
                     "Nie udało się dodać żadnej z wybranych preferencji");
}
void MessageHandler::cancelTermsStudent(EditTermPrefMessageContent* content){
    //TODO zmień typ contenta
    unsigned int studentID = client_->getID();
    std::list<unsigned int> eventIDlist = content->getEventsIDList();

    int termsCounter = 0;

    for(unsigned int eventID: eventIDlist){
        int result = DBManager::getInstance().cancelStudentTermPref(eventID,studentID);
        if(result == cancelSuccess)
            termsCounter++;
    }
    sendNotification(termsCounter,eventIDlist.size(),
                     "Udało się usunąć wszystkie wybranych preferencję",
                     "Udało się usunąć część z wybranych preferencji",
                     "Nie udało się usunąć żadnej z wybranych preferencji");

}

void MessageHandler::addTermsTeacher(AddTermPrefMessageContent* content){

    unsigned int teacherID = client_->getID();
    std::list<Event> events = content->getEventsList();

    int termsCounter = 0;

    for(Event event: events){
        event.setTeacherID(teacherID);
        int result = DBManager::getInstance().addEvent(event);
        if(result == addSuccess)
            termsCounter++;
    }
    sendNotification(termsCounter,events.size(),
                     "Udało się dodać wszystkie wybrane terminy",
                     "Udało się dodać część z wybranych terminów",
                     "Nie udało się dodać żadnej z wybranych terminów");
}
void MessageHandler::deleteTermsTeacher(EditTermPrefMessageContent* content){

    unsigned int teacherID = client_->getID();
    std::list<unsigned int> eventIDList= content->getEventsIDList();

    int termsCounter = 0;

    for(unsigned int eventID: eventIDList){
        int result = DBManager::getInstance().deleteEvent(eventID,teacherID);
        if(result == deleteSuccess)
            termsCounter++;
     }
    sendNotification(termsCounter,eventIDList.size(),
                     "Udało się usunąć wszystkie wybrane terminy",
                     "Udało się usunąć część z wybranych terminów",
                     "Nie udało się usunąć żadnej z wybranych terminów");
}
void MessageHandler::acceptTermsTeacher(EditTermPrefMessageContent* content){

    unsigned int teacherID = client_->getID();
    std::list<unsigned int> eventIDList= content->getEventsIDList();

    int termsCounter = 0;

    for(unsigned int eventID: eventIDList){
        int result = DBManager::getInstance().acceptEvent(eventID, teacherID);
        if(result == acceptSuccess)
            termsCounter++;
    }
    sendNotification(termsCounter,eventIDList.size(),
                     "Udało się usunąć wszystkie wybrane terminy",
                     "Udało się usunąć część z wybranych terminów",
                     "Nie udało się usunąć żadnej z wybranych terminów");
}
void MessageHandler::declineTermsTeacher(EditTermPrefMessageContent* content){

    unsigned int teacherID = client_->getID();
    std::list<unsigned int> eventIDList= content->getEventsIDList();

    int termsCounter = 0;

    for(unsigned int eventID: eventIDList){
        int result = DBManager::getInstance().declineEvent(eventID, teacherID);
        if(result == cancelSuccess)
            termsCounter++;
    }
    sendNotification(termsCounter,eventIDList.size(),
                     "Udało się usunąć wszystkie wybrane terminy",
                     "Udało się usunąć część z wybranych terminów",
                     "Nie udało się usunąć żadnej z wybranych terminów");

}

void MessageHandler::sendMultipleMessagesHandle(SendMultipleMessageContent* content){
    std::list<unsigned int> studentIDList = content->getStudentsIDList();
    char* messageText = content->getMessageText();
    unsigned int teacherID = client_->getID();
    int type = content->getMessageType();
    int subType = content->getMessageSubType();

    Message* msg = new Message(type,subType,client_->getPacketID(),0,messageText,strlen(messageText));
    int addedTermsCounter = 0;
    for(unsigned int id: studentIDList){
        SingletonClientList::getInstance().pushMessage(id,msg);
        addedTermsCounter++;
    }
    sendNotification(addedTermsCounter,studentIDList.size(),
                     "Udało się dodać do kolejki wszystkie wiadomości",
                     "Udało się dodać do kolejki część wiadomości",
                     "Nie udało się dodać do kolejki żadnej wiadomości"
                     );
}
void MessageHandler::sendNotification(int addedTermsCounter, int size,std::string succesfull,std::string info,std::string failure){
    if(addedTermsCounter == size)
        client_->sendNotification(succesfull,NOTIFICATION,SUCCESFULL);
    else if(addedTermsCounter > 0)
        client_->sendNotification(info,NOTIFICATION,INFO);
    else if(addedTermsCounter == 0)
        client_->sendNotification(failure,NOTIFICATION,FAILURE);

}
