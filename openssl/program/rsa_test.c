#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>

unsigned char publicKey[] = "-----BEGIN PUBLIC KEY-----\n"\
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA416900/64SMztl65mokW\n"\
"Wq4kwYQ0qwr7+rvM5PHyJZ88qQMe5EYMWkuyyb5+vKNlm5v6/Mo6SgJJOU+wbYTT\n"\
"D59pi4dTpg5s8aWMGl2ue/2dtQN1pEGTn+KKH0rDzKNrC0NiGLJskg3LnXWDCrkx\n"\
"cHHi1g+3t6kNeyObH1qT6dlmYMQpvSFM919RoavcvHg0FsCyRMwnoZbWiR69FkGj\n"\
"d6qYJlknpSCj1rcXUtQr+wbKhh/MqPI67zbDDa8hlpgoPzgW6SQOCyTGrRpmhoMv\n"\
"5k8WQ+idw7hTUOrHhfOG2j0C9/6De2Y1kDluYcC2k937zHMuAAOEcQD3IyC2pJxH\n"\
"LwIDAQAB\n"\
"-----END PUBLIC KEY-----\n";

unsigned char privateKey[] = "-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpAIBAAKCAQEA416900/64SMztl65mokWWq4kwYQ0qwr7+rvM5PHyJZ88qQMe\n"\
"5EYMWkuyyb5+vKNlm5v6/Mo6SgJJOU+wbYTTD59pi4dTpg5s8aWMGl2ue/2dtQN1\n"\
"pEGTn+KKH0rDzKNrC0NiGLJskg3LnXWDCrkxcHHi1g+3t6kNeyObH1qT6dlmYMQp\n"\
"vSFM919RoavcvHg0FsCyRMwnoZbWiR69FkGjd6qYJlknpSCj1rcXUtQr+wbKhh/M\n"\
"qPI67zbDDa8hlpgoPzgW6SQOCyTGrRpmhoMv5k8WQ+idw7hTUOrHhfOG2j0C9/6D\n"\
"e2Y1kDluYcC2k937zHMuAAOEcQD3IyC2pJxHLwIDAQABAoIBAG0kVlSwKMqXnkQl\n"\
"lkyjD5L50vT9pFaSkEBck882gLkkhfbPY63KHjXd7nW/NpEQkj6vEjz0SiSqkkGr\n"\
"ihIYV0RBjmWG0VV9yTf58pXZcF9eb6yre3YccGOoWAsLVY/OxhyC/PzD8S/u5VWx\n"\
"SfUEzsGeOXft1Y+Y27rHbbgQP75ZUJbTpSmFrxnO665utNgl/xo4EFvwdlBxwvUT\n"\
"mX1I8Yy2o2bcIOEaYee8HuDVnQwVE/m6Kjhp6d3UYR/bskF0VhVR0tk5EYSudpS5\n"\
"tbghmgqDY3T+IR+Z3+NiEMZ7LjwK0rWSNmsz5N2Unwcu4Bo2TZnPsm+0ui+Ho5NZ\n"\
"bEwRwEECgYEA8f7n4ELsmS6Mp3hhCtj7fuczVjomFSvvC0PJcsezF7JthLJp1OKM\n"\
"syYh2LeCFvlLeXkbDQ9FOPAky+85G/IDuixJ9hXn4D8mRLDrs3+ly2r7gtWL2E6z\n"\
"6zOEfcVjY6APoywPodgM2nju2PGzp3SyaMzI31AX47V9A7N+xCZ8n6ECgYEA8Icp\n"\
"Rtbk5FqIv0JYPp/EfL3kr/K3si9H9FvYZfWTuQrnID/NHXLs19hFDUkFdajDN7yH\n"\
"VSG16HRhJPCTHv+T1vZDI95DHT0p4P91oYYw27RVt2E7URmfxgEMcq4EkoXnsbTM\n"\
"c47GU1cT7USlXiUhurFfCGQ7Q1f0IGVxwmdatM8CgYEA8QVZ+rGNJpAHRPEPbhdo\n"\
"fR9WsSXfMiz8u7J7HFerlwl+LLDp2T7+tZtgEJHM/oay1jx5Zct0vV3ouDj+H0gu\n"\
"0Ck2TOPKez1KJxYy2ydigLR/5fI8g2b3qWU5K28CK4KKsJC8zQv62UmjUe2BamI/\n"\
"I0P7OPdzo7bp2VrYAhL3AqECgYBjvwmFERT3BfxzpGXIAqWPPYia1sMLJ8RlN7lz\n"\
"/vV15WmX3B2JuuExWcS5D7Et7ACZGpvc2BACCFFI6mN4lXCP0qxhMYkPlQ/K+OWl\n"\
"SGr2kcCCPdZFeaTijgjFfhjzUoiVD29B9NGWOiRPXwpdEnT8YRYR+s8AzHa3AJq+\n"\
"jfH1zQKBgQDFgRKczauNQ3ACVS2Rf3qwbtvPyLd60UMInRkI4Otb6J3Yod6Q6ffw\n"\
"bi39MgNkSvUXatILHU7rKHRM5R/uObRE+VqE17NjI6XG4BxxTfSdx1481l6CADdq\n"\
"4KfrVusw+65HHQ7U++hgNx0b8qnxtV9md4xhlsrFKjBYV8pqp58iDQ==\n"\
"-----END RSA PRIVATE KEY-----\n";

RSA *createRSA(unsigned char *key, int public) {
    RSA *rsa = NULL;
    BIO *keybio;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio == NULL) {
        printf("FAILED TO CREATE KEY BIO\n");
        return 0;
    }
    if(public) {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    }
    else {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    }
    if(rsa == NULL) {
        printf("FAILED TO CREATE RSA\n");
    }
    return rsa;
}
void printLastError(char *msg) {
    char * err = malloc(130);
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    printf("%s ERROR: %s\n", msg, err);
    free(err);
}

int private_decrypt(unsigned char *enc_data, int data_len, unsigned char *key, unsigned char *decrypted) {
    RSA *rsa = createRSA(key, 0);
    int  result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, RSA_PKCS1_PADDING);
    return result;
}

int main(int argc, char **argv) {

    unsigned char plainText[2048/8] = "Hello world!";
#if 0
    unsigned char publicKey[] = "-----BEGIN PUBLIC KEY-----\n"\
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy8Dbv8prpJ/0kKhlGeJY\n"\
"ozo2t60EG8L0561g13R29LvMR5hyvGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+\n"\
"vw1HocOAZtWK0z3r26uA8kQYOKX9Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQAp\n"\
"fc9jB9nTzphOgM4JiEYvlV8FLhg9yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68\n"\
"i6T4nNq7NWC+UNVjQHxNQMQMzU6lWCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoV\n"\
"PpY72+eVthKzpMeyHkBn7ciumk5qgLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUy\n"\
"wQIDAQAB\n"\
"-----END PUBLIC KEY-----\n";
#endif


    unsigned char encrypted[4098] = {};
    RSA *rsa_pub = createRSA(publicKey, 1);
    int encrypted_length = RSA_public_encrypt(strlen((char *)plainText), plainText, encrypted, rsa_pub, RSA_PKCS1_PADDING);
    if (encrypted_length == -1) {
        printLastError("PUBLIC ENCRYPT FAILED");
        exit(0);
    }
    printf("encrypted_length: %d", encrypted_length);
    FILE *out = fopen("out.bin", "w");
    fwrite(encrypted, sizeof(*encrypted),  RSA_size(rsa_pub), out);
    fclose(out);
    printf("ENCRYPTED MESSAGE WRITTEN TO FILE.\n");

    {
        unsigned char encrypted[4098] = {};
        unsigned char decrypted[4098] = {};
        RSA *rsa = createRSA(publicKey, 1);
        int encrypted_length = 256;
        printf("Reading back encrypted message and attempting decryption...\n");
        FILE *out = fopen("out.bin", "r");
        fread(encrypted, sizeof(*encrypted), RSA_size(rsa), out);
        int decrypted_length = private_decrypt(encrypted, encrypted_length, privateKey, decrypted);
        if(decrypted_length == -1) {
            printLastError("Private Decrypt failed ");
            exit(0);
        }
        printf("Decrypted Text =[%s]\n",decrypted);
        fclose(out);

    }

    return 0;
}


#if 0
int main(int argc, char **argv) 
{

    unsigned char encrypted[4098] = {};
    unsigned char decrypted[4098] = {};
    RSA *rsa = createRSA(publicKey, 1);
    int encrypted_length = 256;
    printf("Reading back encrypted message and attempting decryption...\n");
    FILE *out = fopen("out.bin", "r");
    fread(encrypted, sizeof(*encrypted), RSA_size(rsa), out);
    int decrypted_length = private_decrypt(encrypted, encrypted_length, privateKey, decrypted);
    if(decrypted_length == -1) {
        printLastError("Private Decrypt failed ");
        exit(0);
    }
    printf("Decrypted Text =[%s]\n",decrypted);
    fclose(out);
    return 0;
}
#endif
