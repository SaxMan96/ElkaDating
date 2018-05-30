#include "MessageHandler.hpp"

MessageHandler::MessageHandler(Client * client)
{
    client_ = client;
}

void MessageHandler::handleMessage(Message* msg){

    msg_ = msg;

    if(msg_->getMsgType() == TERMS_STUDENT){
        TermPrefMessageContent* content = static_cast<TermPrefMessageContent*>(msg->getContent());

        unsigned int teacherID = content->getID();
        std::vector<Term> terms = content->getTermsVector();
        Term term;
        //Czy tu jest dobrze pobrane ID studenta?
        unsigned int studentID = client_->getID();

        int addedTermsCounter = 0;
        for(int i =0;i<terms.size();i++){
            term = terms[i];
            if(msg_->getMsgSubType() == PREF_TERMS){
               //Zapytanie dodające preferencję na termin term studenta studentID
               //do listy terminów prowadzącego teacherID
            }
            else if(msg_->getMsgSubType() == CANCEL_TERMS){
                //Zapytanie usuwające preferencję na termin term studenta studentID
                //z listy terminów prowadzącego teacherID
            }
            //jeżeli dodanie, lub usunięcie terminu się uda addedTermsCounter++
        }
        if(msg_->getMsgSubType() == PREF_TERMS){
            if(addedTermsCounter == terms.size())
                client_->sendNotification("Udało się dodać wszystkie wybranych preferencję",NOTIFICATION,SUCCESFULL);
            else if(addedTermsCounter > 0)
                client_->sendNotification("Udało się dodać część z wybranych preferencji",NOTIFICATION,INFO);
            else if(addedTermsCounter == 0)
                client_->sendNotification("Nie udało się dodać żadnej z wybranych preferencji",NOTIFICATION,FAILURE);
        }
        else if(msg_->getMsgSubType() == CANCEL_TERMS){
            if(addedTermsCounter == terms.size())
                client_->sendNotification("Udało się usunąć wszystkie wybranych preferencję",NOTIFICATION,SUCCESFULL);
            else if(addedTermsCounter > 0)
                client_->sendNotification("Udało się usunąć część z wybranych preferencji",NOTIFICATION,INFO);
            else if(addedTermsCounter == 0)
                client_->sendNotification("Nie udało się usunąć żadnej z wybranych preferencji",NOTIFICATION,FAILURE);
        }
    }
    else if(msg_->getMsgType() == TERMS_TEACHER){
        //podobnie jak powyżej, tylko że ID prowadzącego tutaj będzie
        //oraz inna lista w bazie danych, bo to w końcu preferencje prowadzącego

    }
    else if(msg_->getMsgType() == SEND_MULITIPLE_MSG_TO_STUDENTS){
        SendMultipleMessageContent* content = static_cast<SendMultipleMessageContent*>(msg->getContent());

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
}

