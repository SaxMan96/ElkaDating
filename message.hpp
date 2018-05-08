#ifndef MESSAGE_HPP
#define MESSAGE_HPP


struct Message{
private:
    char* bufor_;

public:
    Message(char* bufor){
        bufor_=bufor;
    }

    char* getBufor() const {
        return bufor_;
    }
};

#endif // MESSAGE_HPP
