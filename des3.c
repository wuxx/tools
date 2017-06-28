#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
 
/* gcc des3.c -lssl -lcrypto */
void tEVP_Encrypt()
{
    unsigned char key[EVP_MAX_KEY_LENGTH]; 
    unsigned char iv[EVP_MAX_KEY_LENGTH];
    EVP_CIPHER_CTX ctx;
    unsigned char out[1024];
    unsigned char out1[1024];
    int outl;
    int outltmp;
    int outl1;
    int outltmp1;
    char *msg="Hello OpenSSL!";
    int rv;
    int rv1;
    int i;

    for(i=0;i<24;i++)
    {
        key[i]=i;
    }
    for(i=0;i<8;i++)
    {
        iv[i]=i;
    }

    EVP_CIPHER_CTX_init(&ctx);

    rv = EVP_EncryptInit_ex(&ctx,EVP_des_ede3_cbc(),NULL,key,iv);
    if(rv!=1)
    {
        printf("Err\n");
        return;
    }

    rv = EVP_EncryptUpdate(&ctx,out,&outl,msg,strlen(msg));
    if(rv!=1)
    {
        printf("Err\n");
        return;
    }

    rv = EVP_EncryptFinal_ex(&ctx,out+outl,&outltmp);
    if(rv!=1)
    {
        printf("Err\n");
        return;
    }
    outl = outl +outltmp;   
    printf("%s \n",msg);

    printf("%d \n",outl);
    for(i=0;i<outl;i++)
    {
        printf("0x%02x ",out[i]);
    }
    printf("\n");
    


    //解密过程
    rv1 = EVP_DecryptInit_ex(&ctx,EVP_des_ede3_cbc(),NULL,key,iv);
    if(rv1!=1)
    {
        printf("Err1\n");
        return;
    }

    rv1 = EVP_DecryptUpdate(&ctx,out1,&outl1,out,outl);
    if(rv1!=1)
    {
        printf("Err2\n");
        return;
    }
    rv1 = EVP_DecryptFinal_ex(&ctx,out1+outl1,&outltmp1);
    if(rv1!=1)
    {
        printf("Err3\n");
        return;
    }

        outl1 = outl1 +outltmp1;
        //打印输出明文
        printf("\n\n原文长度：%d\n原文数据：\n",outl1);
        for(i=0;i<outl1;i++)
        {
                printf("%c",out1[i]);
        }
        printf("\n");
}

int main()
{ 
    
    OpenSSL_add_all_algorithms();
    tEVP_Encrypt();
    return 0;
}

