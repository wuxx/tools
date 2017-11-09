#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>

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

int main(int argc,char *argv[])
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
