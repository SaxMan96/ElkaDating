#include "MessageHandler.hpp"

MessageHandler::MessageHandler(Client * client)
{
    client_ = client;
}

void MessageHandler::handleMessage(Message* msg){

    msg_ = msg;
    MessageContent* content = msg_->getContent();

    if(msg_->getMsgType() == TERMS_STUDENT)
        termsStudentMessageHandle(static_cast<TermPrefMessageContent*>(content));
    else if(msg_->getMsgType() == TERMS_TEACHER)
        termsTeacherMessageHandle(static_cast<TermPrefMessageContent*>(content));
    else if(msg_->getMsgType() == SEND_MULITIPLE_MSG_TO_STUDENTS)
        sendMultipleMessagesHandle(static_cast<SendMultipleMessageContent*>(content));

}
void MessageHandler::termsStudentMessageHandle(TermPrefMessageContent* content){
    unsigned int teacherID = content->getID();
    std::list<Term> terms = content->getTermsList();
    Term term;
    //Czy tu jest dobrze pobrane ID studenta?
    unsigned int studentID = client_->getID();

    int addedTermsCounter = 0;

    //TODO: jeżeli dodanie, lub usunięcie terminu się uda addedTermsCounter++

    if(msg_->getMsgSubType() == PREF_TERMS){
        for(Term term: terms){
               //TODO: Zapytanie dodające preferencję na termin term studenta studentID
               //do listy terminów prowadzącego teacherID
            addedTermsCounter++;
            }
        sendNotification(addedTermsCounter,terms.size(),
                         "Udało się dodać wszystkie wybranych preferencję",
                         "Udało się dodać część z wybranych preferencji",
                         "Nie udało się dodać żadnej z wybranych preferencji");
    }
    else if(msg_->getMsgSubType() == CANCEL_TERMS){
        for(Term term: terms){
            //TODO: Zapytanie usuwające preferencję na termin term studenta studentID
            //z listy terminów prowadzącego teacherID
            addedTermsCounter++;
            }
        sendNotification(addedTermsCounter,terms.size(),
                         "Udało się usunąć wszystkie wybranych preferencję",
                         "Udało się usunąć część z wybranych preferencji",
                         "Nie udało się usunąć żadnej z wybranych preferencji");
    }
}
void MessageHandler::termsTeacherMessageHandle(TermPrefMessageContent* content){
    //podobnie jak powyżej, tylko że ID prowadzącego tutaj będzie
    //oraz inna lista w bazie danych, bo to w końcu preferencje prowadzącego

    unsigned int teacherID = client_->getID();
    std::list<Term> terms = content->getTermsList();
    Term term;

    int addedTermsCounter = 0;

        //TODO: jeżeli dodanie, lub usunięcie terminu się uda addedTermsCounter++

    if(msg_->getMsgSubType() == NEW_TERMS){
        for(Term term: terms){
               //TODO: Zapytanie dodające termin term prowadzącego teacherID
               //do listy terminów prowadzącego teacherID
                addedTermsCounter++;
            }
        sendNotification(addedTermsCounter,terms.size(),
                         "Udało się dodać wszystkie wybrane terminy",
                         "Udało się dodać część z wybranych terminów",
                         "Nie udało się dodać żadnej z wybranych terminów");
    }
    else if(msg_->getMsgSubType() == DELETE_TERM){
       for(Term term: terms){
                //TODO: Zapytanie usuwające termin term prowadzącego teacherID
                //z listy terminów prowadzącego teacherID
                addedTermsCounter++;
            }
       sendNotification(addedTermsCounter,terms.size(),
                        "Udało się usunąć wszystkie wybrane terminy",
                        "Udało się usunąć część z wybranych terminów",
                        "Nie udało się usunąć żadnej z wybranych terminów");
    }
    else if(msg_->getMsgSubType() == ACCEPT_TERMS){
        for(Term term: terms){
                //TODO: Zapytanie akceptujące termin term prowadząćego teacherID
                //z listy terminów prowadzącego teacherID
                addedTermsCounter++;
            }
        sendNotification(addedTermsCounter,terms.size(),
                         "Udało się usunąć wszystkie wybrane terminy",
                         "Udało się usunąć część z wybranych terminów",
                         "Nie udało się usunąć żadnej z wybranych terminów");
    }
    else if(msg_->getMsgSubType() == DECLINE_TERMS){
       for(Term term: terms){
                //TODO: Zapytanie anulujące termin term prowadzącego techerID
                //z listy terminów prowadzącego teacherID
                addedTermsCounter++;
            }
        sendNotification(addedTermsCounter,terms.size(),
                         "Udało się usunąć wszystkie wybrane terminy",
                         "Udało się usunąć część z wybranych terminów",
                         "Nie udało się usunąć żadnej z wybranych terminów");
    }
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
    if(addedTermsCounter == studentIDList.size())
        client_->sendNotification("Udało się dodać do kolejki wszystkie wiadomości",NOTIFICATION,SUCCESFULL);
    else if(addedTermsCounter > 0)
        client_->sendNotification("Udało się dodać do kolejki część wiadomości",NOTIFICATION,INFO);
    else if(addedTermsCounter == 0)
        client_->sendNotification("Nie udało się dodać do kolejki żadnej wiadomości",NOTIFICATION,FAILURE);

}
void MessageHandler::sendNotification(int addedTermsCounter, int size,std::string succesfull,std::string info,std::string failure){
    if(addedTermsCounter == size)
        client_->sendNotification(succesfull,NOTIFICATION,SUCCESFULL);
    else if(addedTermsCounter > 0)
        client_->sendNotification(info,NOTIFICATION,INFO);
    else if(addedTermsCounter == 0)
        client_->sendNotification(failure,NOTIFICATION,FAILURE);

}
