#include "SecureHandler.hpp"


SecureHandler::SecureHandler(Package* package)
{
    data_ = package->getPackage();
    dataLength_ = package->getPackageLength();

    encrypt();
}

char *SecureHandler::getData()
{
    return  data_;
}

int SecureHandler::getDataLength() const
{
    return dataLength_;
}

int SecureHandler::public_encrypt(unsigned char * data,int data_len,RSA *rsa, unsigned char *encrypted)
{
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}

int SecureHandler::private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted)
{
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}

int SecureHandler::encrypt(){

    unsigned char plainText[2048/8];

    FILE * fp = fopen("/home/karol/GitRepos/ElkaDating/ElkaDatingClient/publicServer_key.pem", "rb");

    if(fp == NULL)
    {
        std::cout<<"Private ERROR!\n";
        return 0;
    }

    RSA *rsaPubKey = RSA_new();

    rsaPubKey = PEM_read_RSA_PUBKEY(fp, &rsaPubKey, NULL, NULL);

    fclose(fp);

//    unsigned char data[] = "Blues";
//    fp = fopen("private_key.pem", "rb");

//    if(fp == NULL)
//    {
//        std::cout<<"Private ERROR!\n";
//        return 0;
//    }

//    RSA *rsaPrivateKey = RSA_new();

//    rsaPrivateKey = PEM_read_RSAPrivateKey(fp, &rsaPrivateKey, NULL, NULL);

//    fclose(fp);

//    unsigned char  encrypted[4098];
//    unsigned char decrypted[4098];

    int encrypted_length = public_encrypt((unsigned char*)data_, dataLength_, rsaPubKey,plainText);
    if(encrypted_length == -1)
    {
        printf("Public Encrypt failed \n");
        exit(0);
    }


    printf("Encrypted length =%d\n",encrypted_length);

    for(int i =0; i<encrypted_length; ++i)
    {
        printf("%d\n", *(data_+i));
    }

//    int decrypted_length = private_decrypt(encrypted,encrypted_length,rsaPrivateKey, decrypted);
//    if(decrypted_length == -1)
//    {
//        printf("Private Decrypt failed\n");
//        exit(0);
//    }
//    printf("Decrypted Text =%s\n",decrypted);
//    printf("Decrypted Length =%d\n",decrypted_length);
    dataLength_=encrypted_length;
    int i = 0;
    data_ = new char[256];
    for (char e : plainText)
        data_[i++] = e;
    std::cout<<"tuu \ndataLength_: "<<dataLength_<<"\n\n";
    for (char e : plainText)
        std::cout<<e;
//    data_ = plainText;
}

/*
//    unsigned char plainText[2048/8] = "We are on a mission from God!\0";

//// --------------------------------------------------------

//    FILE * fp = fopen("publicServer_key.pem", "rb");

//    if(fp == NULL)
//    {
//        std::cout<<"Private ERROR!\n";
//        return 0;
//    }

//    RSA *rsaPubKey = RSA_new();

//    rsaPubKey = PEM_read_RSA_PUBKEY(fp, &rsaPubKey, NULL, NULL);

//    fclose(fp);

//    unsigned char data[] = "Blues";
//    fp = fopen("private_key.pem", "rb");

//    if(fp == NULL)
//    {
//        std::cout<<"Private ERROR!\n";
//        return 0;
//    }

//    RSA *rsaPrivateKey = RSA_new();

//    rsaPrivateKey = PEM_read_RSAPrivateKey(fp, &rsaPrivateKey, NULL, NULL);

//    fclose(fp);

//    unsigned char  encrypted[4098];
//    unsigned char decrypted[4098];

//    int encrypted_length= public_encrypt(plainText,6,rsaPubKey,encrypted);
//    if(encrypted_length == -1)
//    {
//        printf("Public Encrypt failed \n");
//        exit(0);
//    }

//    printf("Encrypted length =%d\n",encrypted_length);

//    for(int i =0; i<encrypted_length; ++i)
//    {
//        printf("%d\n", *(encrypted+i));
//    }

//    int decrypted_length = private_decrypt(encrypted,encrypted_length,rsaPrivateKey, decrypted);
//    if(decrypted_length == -1)
//    {
//        printf("Private Decrypt failed\n");
//        exit(0);
//    }
//    printf("Decrypted Text =%s\n",decrypted);
//    printf("Decrypted Length =%d\n",decrypted_length);
*/
