#include "SendMultipleMessageContent.hpp"

SendMultipleMessageContent::SendMultipleMessageContent()
{

}

std::list<unsigned int> SendMultipleMessageContent::getStudentsIDList()
{
    return studentsIDList_;
}

std::string SendMultipleMessageContent::getMessageText()
{
    return messageText_;
}

int SendMultipleMessageContent::getMessageType()
{
    return type_;
}

int SendMultipleMessageContent::getMessageSubType()
{
    return subType_;
}
