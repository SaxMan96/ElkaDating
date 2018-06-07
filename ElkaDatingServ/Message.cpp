#include "Message.hpp"

Message::Message(char* header){

    dataLength_ = *(short*)(header+14);
    delete [] msgBuf_;

    msgBuf_ = new char[MESSAGE_HEADER_SIZE + dataLength_];

    protocolName_[0] = header[0];
    protocolName_[1] = header[1];
    protocolName_[2] = header[2];
    protocolName_[3] = header[3];

    type_ = header[4];
    subType_ = header[5];

    packetID_ = *(int*)(header+6);

    sessionID_ = *(int*)(header+10);

    // przekopiowanie headera to bufora
    for(int i = 0; i<MESSAGE_HEADER_SIZE; ++i)
    {
        msgBuf_[i]=header[i];
    }
    //setMessageContent(type_);
    //TODO
}

Message::Message(int type, int subType, int packetID, int sessionID, char *data, int dataLength)
{
    type_ = type;
    subType_ = subType;
    packetID_ = packetID;
    sessionID_ = sessionID;

    dataLength_ = dataLength;

    msgBuf_ = new char[MESSAGE_HEADER_SIZE + dataLength_];

    //header name
    msgBuf_[0] = 'D';
    msgBuf_[1] = 'K';
    msgBuf_[2] = 'P';
    msgBuf_[3] = 'S';

    //type
    msgBuf_[4] = type_;

    //subType
    msgBuf_[5] = subType;

    //packetID
    msgBuf_[9] = (packetID_>>24) & 0xFF;
    msgBuf_[8] = (packetID_>>16) & 0xFF;
    msgBuf_[7] = (packetID_>>8) & 0xFF;
    msgBuf_[6] = packetID_ & 0xFF;

    //sessionID
    msgBuf_[13] = (sessionID_>>24) & 0xFF;
    msgBuf_[12] = (sessionID_>>16) & 0xFF;
    msgBuf_[11] = (sessionID_>>8) & 0xFF;
    msgBuf_[10] = sessionID_ & 0xFF;

    //dataLength
    msgBuf_[15] = (dataLength_>>8) & 0xFF;
    msgBuf_[14] = dataLength_ & 0xFF;

    if(dataLength>0 && data!=nullptr)
    {
        for(int i = 0; i<dataLength; ++i)
        {
            *(msgBuf_+MESSAGE_HEADER_SIZE+i) = *(data+i);
        }
    }
}


std::string Message::headerToString() const {
    std::string str;
    unsigned int tmp;
    for(int i = 0; i<4; ++i)
    {
        str+=protocolName_[i];
    }
    str+="\n";
    tmp = static_cast<unsigned int>(type_);
    str+="TYPE: " + std::to_string(tmp);
    str+="\n";
    tmp = static_cast<unsigned int>(subType_);
    str+="SUBTYPE: "+std::to_string(tmp);
    str+="\n";
    tmp =static_cast<unsigned int>(packetID_);
    str+="PACKET ID: "+std::to_string(tmp);
    str+="\n";
    tmp = static_cast<unsigned int>(sessionID_);
    str+="SESSION ID: "+std::to_string(tmp);
    str+="\n";
    tmp = static_cast<unsigned int>(dataLength_);
    str+="DATA LENGTH: "+std::to_string(tmp);
    str+="\n";
    return str;
}


int Message::getMsgDataLength() const {
    return dataLength_;
}

char* Message::getMsgDataBufor() const {
    return (msgBuf_+MESSAGE_HEADER_SIZE);
}

int Message::getMsgFullLength() const {
    return MESSAGE_HEADER_SIZE + dataLength_;
}

char* Message::getMsgFullBufor() const {
    return msgBuf_;
}

int Message::getMsgType() const
{
    return static_cast<int>(type_);
}

int Message::getMsgSubType() const
{
    return static_cast<int>(subType_);
}

MessageContent* Message::getContent() const{
    return content_;
}

void Message::setContent(MessageContent *content)
{
    content_ = content;
}

Message::~Message()
{
    delete []msgBuf_;
}

Message *getSignUpPackage(std::string name, std::string surname, std::string password, std::string email){
    std::string str = "Name: "+name+"\nSurname: "+surname+"\nEmail: "+email+"\nPassword: "+password;
    return new Message(REGISTRATION,0,0,0,(char*)str.c_str(),str.length());
}

Message *getSignInMessage(std::string email, std::string password){
    std::string str = "Email: "+email+"\nPassword: "+password;
    return new Message(LOGIN,0,0,0,(char*)str.c_str(),str.length());
}


Message* getAddTermsStudentMessage(unsigned int teacherID,unsigned int studentID,std::list<Event> events){
    std::string str = "TeacherID: "+std::to_string(teacherID)+"\nStudentID: "+std::to_string(studentID);
    str += "\nEventsList: "+ events.size();
    for(Event event: events){
        event.setStudentID(studentID);
        event.setStudentID(teacherID);
        str += event.toString();
    }
    return new Message(TERMS_STUDENT,PREF_TERMS,0,0,(char*)str.c_str(),str.length());
}
Message* getCancelTermsStudentMessage(unsigned int studentID,std::list<unsigned int> eventIDlist){
    std::string str = "StudentID: "+studentID;
    str += "\nEventIDList: "+ eventIDlist.size();
    for(unsigned int eventID: eventIDlist){
        str += "ID: "+eventID;
    }
    return new Message(TERMS_STUDENT,CANCEL_TERMS,0,0,(char*)str.c_str(),str.length());

}


Message* getAddTermsTeacherMessage(unsigned int teacherID,unsigned int studentID,std::list<Event> events){
    std::string str = "TeacherID: "+std::to_string(teacherID)+"\nStudentID: "+std::to_string(studentID);
    str += "\nEventsList: "+ events.size();
    for(Event event: events){
        event.setStudentID(studentID);
        event.setStudentID(teacherID);
        str += event.toString();
    }
    return new Message(TERMS_TEACHER,NEW_TERMS,0,0,(char*)str.c_str(),str.length());
}
Message* getDeleteTermsTeacherMessage(unsigned int teacherID,std::list<unsigned int> eventIDlist){
    std::string str = "TeacherID: "+teacherID;
    str += "\nEventIDList: "+ eventIDlist.size();
    for(unsigned int eventID: eventIDlist){
        str += "ID: "+eventID;
    }
    return new Message(TERMS_STUDENT,DELETE_TERM,0,0,(char*)str.c_str(),str.length());

}
Message* getAcceptTermsTeacherMessage(unsigned int teacherID,std::list<unsigned int> eventIDlist){
    std::string str = "TeacherID: "+teacherID;
    str += "\nEventIDList: "+ eventIDlist.size();
    for(unsigned int eventID: eventIDlist){
        str += "ID: "+eventID;
    }
    return new Message(TERMS_STUDENT,ACCEPT_TERMS,0,0,(char*)str.c_str(),str.length());

}
Message* getDeclineTermsTeacherMessage(unsigned int teacherID,std::list<unsigned int> eventIDlist){
    std::string str = "TeacherID: "+teacherID;
    str += "\nEventIDList: "+ eventIDlist.size();
    for(unsigned int eventID: eventIDlist){
        str += "ID: "+eventID;
    }
    return new Message(TERMS_STUDENT,DECLINE_TERMS,0,0,(char*)str.c_str(),str.length());

}

Message* getTeachersListMessage(unsigned int teacherID){
    //ID imie nazwisko
    std::unordered_map<unsigned int, std::pair<std::string, std::string>> lecturers = DBManager::getInstance().getTeacherMap();

}

Message* getUserEvents(){
    //
}
Message* getStudentEventsWithTeacherMessage(){
    // spotkania studentów u teachera lista Eventów
}
