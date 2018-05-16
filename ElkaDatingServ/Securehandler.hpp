#ifndef SECUREHANDLER_HPP
#define SECUREHANDLER_HPP

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

class SecureHandler
{

private:

    RSA *rsaPublicKey_;
    RSA *rsaPrivateKey_;


public:
    SecureHandler(std::string privateKeyFileName, std::string publicKeyFileName);
};

#endif // SECUREHANDLER_HPP


