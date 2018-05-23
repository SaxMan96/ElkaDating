#include "MessageHandlerDKPS.hpp"

MessageHandlerDKPS::MessageHandlerDKPS(){

}

void MessageHandlerDKPS::handleMessage(Message* msg){

    msg_ = msg;

    else if(msg_->getMsgType() == TERM_PREF_STUDENT){
        //jeżeli student jest zalogowany
        int sessionID = msg->getContent().getSessionIO();
        int teacherID = msg->getContent().getTeacherIO();
        int addedTermsCounter = 0;

        std::vector<Term> terms = msg->getContent().getTerms();

        for(int i =0;i<terms.size();i++){
           ;
            //Dodaj temu studentowi (sessionID) do tego prowadzącego (teacherID)
            //ten termin (term) do preferencji w bazie danych

            //jeżeli dodanie terminu się uda addedTermsCounter++
        }
        //jak się skończy to wyśli powiadomienie, że się udało
        //jeżeli addedTermsCounter != terms.size() to napisz co się popsuło.
    }
    else if(msg_->getMsgType() == TERM_PREF_TEACHER){
        //podobnie jak powyżej, tylko że ID prowadzącego tutaj będzie
        //oraz inna lista w bazie danych, bo to w końcu preferencje prowadzącego

    }
    else if(msg_->getMsgType() == ACCEPT_TERMS){


    }
    else if(msg_->getMsgType() == CANCEL_TERMS){

    }
    else if(msg_->getMsgType() == ADD_NEW_TERM){

    }
    else if(msg_->getMsgType() == SEND_MSG_TO_STUDENTS){

    }
    else if(msg_->getMsgType() == CONFIRM_TERM_STUDENT){

    }
    else if(msg_->getMsgType() == CLIENT_DISCONNECT){

    }
}
