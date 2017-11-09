#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>  

#define INPUT "testOpenssl"

/*
    to verity: echo -n "testOpenssl" | sha256sum
*/

int main()  
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
