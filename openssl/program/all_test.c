#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#define INPUT "testOpenssl"

/*
    to verity: echo -n "testOpenssl" | sha256sum
*/

int hash_main()
{  
    char digestType[][20] =
    {  
        "md4",  
        "md5",  
        "sha1",  
        "sha256",  
        "sha384",  
        "sha512",  
    };
  
    int size = sizeof(digestType) / sizeof(digestType[0]);  
    int i = 0;  
    for(i = 0; i < size; i++)  
    {     
        EVP_MD_CTX mdctx;  
        const EVP_MD *md = NULL;  
        unsigned char mdValue[EVP_MAX_MD_SIZE] = {0};  
        unsigned int mdLen = 0;  
  
        OpenSSL_add_all_digests();  
        md = EVP_get_digestbyname(digestType[i]);  
        if(!md) // 不支持的格式  
        {  
            printf("Unknown message digest %s\n", digestType[i]);  
            continue;  
        }  
  
        EVP_MD_CTX_init(&mdctx);  
        EVP_DigestInit_ex(&mdctx, md, NULL);  
        EVP_DigestUpdate(&mdctx, INPUT, strlen(INPUT));  
        EVP_DigestFinal_ex(&mdctx, mdValue, &mdLen);  
        EVP_MD_CTX_cleanup(&mdctx);  
  
        printf("%s is ",  digestType[i]);  
        int j = 0;  
        for(j = 0; j < mdLen; j++)  
        {  
            printf("%02X", mdValue[j]);  
        }  
  
        printf("\n");  
    }  
  
    return 0;  
}

#define AES_BITS 128
#define MSG_LEN 128

int aes_encrypt(char* in, char* key, char* out)//, int olen)可能会设置buf长度
{
	AES_KEY aes;
	if(!in || !key || !out) return 0;
	unsigned char iv[AES_BLOCK_SIZE];
	for(int i=0; i<AES_BLOCK_SIZE; ++i) {
		iv[i] = 0;
    }

	if(AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0) {
		return 0;
	}
	int len = strlen(in);

	AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, len, &aes, iv, AES_ENCRYPT);
	return 1;
}

int aes_decrypt(char* in, char* key, char* out)
{
	AES_KEY aes;
	unsigned char iv[AES_BLOCK_SIZE];

	if(!in || !key || !out) return 0;


	for(int i=0; i < AES_BLOCK_SIZE; i++) {
		iv[i] = 0;
    }

	if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0)
	{
		return 0;
	}
	int len=strlen(in);
	AES_cbc_encrypt((unsigned char*)in, (unsigned char*)out, len, &aes, iv, AES_DECRYPT);
	return 1;
}

int aes_main()
{
	char plaintext[MSG_LEN];
	char ciphertext[MSG_LEN];

	memset((char*)plaintext,  0, MSG_LEN);
	memset((char*)ciphertext, 0, MSG_LEN);

	strcpy((char*)plaintext, "123456789 123456789 123456789 12a");
	//strcpy((char*)plaintext, argv[1]);

	char key[AES_BLOCK_SIZE];
	int i;
	for(i = 0; i < 16; i++) {
		key[i] = 32 + i;
	}

	if(!aes_encrypt(plaintext, key, ciphertext)) {
		printf("encrypt error\n");
		return -1;
	}

	//printf("enc %d:",strlen((char*)ciphertext));

	for(i = 0; i < MSG_LEN; i++) {
		printf("%x",(unsigned char)ciphertext[i]);
	}

	memset((char*)plaintext, 0, MSG_LEN);

	if(!aes_decrypt(ciphertext, key, plaintext)) {
		printf("decrypt error\n");
		return -1;
	}

	printf("\n");
	printf("dec %d:",strlen((char*)plaintext));
	printf("%s\n",plaintext);

	for(i = 0; plaintext[i]; i += 1) {
		printf("%x", (unsigned char)plaintext[i]);
	}

	printf("\n");
	return 0;
}

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

int rsa_main(int argc, char **argv) 
{

    char *public_key = NULL;
    char *private_key = NULL;

    if (argc == 3) {
        /* ./program public_key_file private_key_file */
        printf("load key from file \n");
        {
            int prikey_fd, pubkey_fd;
            struct stat st;

            if ((pubkey_fd = open(argv[1], O_RDWR)) == -1) {
                perror("open");
                exit(-1);
            }

            if ((fstat(pubkey_fd, &st)) == -1) {
                perror("fstat");
                exit(-1);
            }

            if ((public_key = mmap(0, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, pubkey_fd, 0)) == MAP_FAILED) {
                perror("mmap");
                exit(-1);
            }

            if ((prikey_fd = open(argv[2], O_RDWR)) == -1) {
                perror("open");
                exit(-1);
            }

            if ((fstat(prikey_fd, &st)) == -1) {
                perror("fstat");
                exit(-1);
            }

            if ((private_key = mmap(0, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, prikey_fd, 0)) == MAP_FAILED) {
                perror("mmap");
                exit(-1);
            }

        }
    } else {
        public_key  = publicKey;
        private_key = privateKey;
    }
    unsigned char plaintext[2048/8] = "Hello world!";

    unsigned char ciphertext[4098] = {};

    RSA *rsa_pub = createRSA(public_key, 1);

    int encrypted_length = RSA_public_encrypt(strlen((char *)plaintext), plaintext, ciphertext, rsa_pub, RSA_PKCS1_PADDING);

    if (encrypted_length == -1) {
        printLastError("PUBLIC ENCRYPT FAILED");
        exit(0);
    }

    printf("encrypted_length: %d; rsa_size: %d;", encrypted_length, RSA_size(rsa_pub));

    FILE *out = fopen("out.bin", "w");

    fwrite(ciphertext, sizeof(*ciphertext),  RSA_size(rsa_pub), out);
    fclose(out);

    printf("ENCRYPTED MESSAGE WRITTEN TO FILE.\n");

    {
        unsigned char encrypted[4098] = {};
        unsigned char decrypted[4098] = {};
        RSA *rsa_pri = createRSA(public_key, 1);
        int encrypted_length = 256;

        printf("Reading back encrypted message and attempting decryption...\n");

        FILE *out = fopen("out.bin", "r");

        printf("%s-%d %d %d\n", __func__, __LINE__, sizeof(*encrypted), RSA_size(rsa_pri));

        fread(encrypted, sizeof(*encrypted), RSA_size(rsa_pri), out);

        int decrypted_length = private_decrypt(encrypted, encrypted_length, private_key, decrypted);

        printf("decrypted_length: %d;", decrypted_length);
        if(decrypted_length == -1) {
            printLastError("Private Decrypt failed ");
            exit(0);
        }

        printf("Decrypted Text =[%s]\n",decrypted);

        fclose(out);

    }

    return 0;
}

int main(int argc, char **argv) 
{
    hash_main();
    aes_main();
    rsa_main(argc, argv);
    return 0;
}

