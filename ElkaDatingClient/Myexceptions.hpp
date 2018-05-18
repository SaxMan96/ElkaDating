#ifndef MYEXCEPTIONS_HPP
#define MYEXCEPTIONS_HPP

#include <exception>

class MyException: public std::exception
{

public:
    virtual const char * what() const throw();
};


class CannotOpenFile: public MyException
{

public:
    const char * what() const throw();
};

class DecryptError : public MyException
{
public:
    const char * what() const throw();
};

class EncryptError : public MyException
{
public:
    const char * what() const throw();
};

class CannotOpenPrivatePem : public MyException
{
public:
    const char * what() const throw();
};

class CannotOpenPublicPem : public MyException
{
public:
    const char * what() const throw();
};

// --------------------------------------------------------

class ServerException : public MyException
{
public:
    virtual const char * what() const throw();
};

class ServerBindError : public ServerException
{

public:
    const char * what() const throw();
};

class ServerAcceptError : public ServerException
{

public:
    const char * what() const throw();
};

class ServerListenError : public ServerException
{

public:
    const char * what() const throw();
};

// --------------------------------------------------------

class ClientException : public MyException
{
public:
    virtual const char * what() const throw();
};

class ClientInitSemError : public ClientException
{
public:
    const char * what() const throw();
};

class ClientCloseError : public ClientException
{
public:
    const char * what () const throw();
};



#endif // MYEXCEPTIONS_HPP
