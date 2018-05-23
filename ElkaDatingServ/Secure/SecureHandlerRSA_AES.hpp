#ifndef SECUREHANDLERRSA_AES_HPP
#define SECUREHANDLERRSA_AES_HPP

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "SecureHandler.hpp"

class SecureHandlerRSA_AES : public SecureHandler
{
public:
    SecureHandlerRSA_AES();
};

#endif // SECUREHANDLERRSA_AES_HPP
