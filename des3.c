#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
 

void tEVP_Encrypt()
{
    unsigned char key[EVP_MAX_KEY_LENGTH];  //密钥
    unsigned char iv[EVP_MAX_KEY_LENGTH];//初始化向量
    EVP_CIPHER_CTX ctx;//EVP算法上下文
    unsigned char out[1024];//输出密文缓冲区
    unsigned char out1[1024];//输出明文缓冲区
    int outl;//密文长度
    int outltmp;
    int outl1;//明文长度
    int outltmp1;
    char *msg="Hello OpenSSL!";//待加密的数据
    int rv;
    int rv1;
    int i;
    //加密过程
    //设置key和iv（可以采用随机数和可以是用户输入）
    for(i=0;i<24;i++)
    {
        key[i]=i;
    }
    for(i=0;i<8;i++)
    {
        iv[i]=i;
    }
    //初始化密码算法结构体
    EVP_CIPHER_CTX_init(&ctx);
    //设置算法和密钥
    rv = EVP_EncryptInit_ex(&ctx,EVP_des_ede3_cbc(),NULL,key,iv);
    if(rv!=1)
    {
        printf("Err\n");
        return;
    }
    //数据加密
    rv = EVP_EncryptUpdate(&ctx,out,&outl,msg,strlen(msg));
    if(rv!=1)
    {
        printf("Err\n");
        return;
    }
    //结束数据加密，把剩余数据输出。
    rv = EVP_EncryptFinal_ex(&ctx,out+outl,&outltmp);
    if(rv!=1)
    {
        printf("Err\n");
        return;
    }
    outl = outl +outltmp;   
    printf("原文为:%s\n",msg);
    //打印输出密文
    printf("密文长度：%d\n密文数据：\n",outl);
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

