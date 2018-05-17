#include "Messagehandler.hpp"




void MessageHandler::handleMessage(Message *m)
{
    msg_ = m;

    if(msg_->getMsgType() == HAND_SHAKE){

    }
    else if(msg_->getMsgType() == NOTIFICATION){

    }
    else if(msg_->getMsgType() == CONFIRMATION){

    }
    else if(msg_->getMsgType() == LOGIN){

    }

}
