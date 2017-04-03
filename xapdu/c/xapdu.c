#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "nfc.h"

typedef unsigned char u8;
typedef   signed char s8;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned int u32;
typedef   signed int s32;

const nfc_modulation nm = {
	.nmt = NMT_ISO14443A,
	.nbr = NBR_106,
};

int card_transmit(nfc_device *pnd, u8 * capdu, u32 capdulen, u8 * rapdu, u32 * rapdulen)
{
	int res;
	u32  szpos;
	printf("=> ");
	for (szpos = 0; szpos < capdulen; szpos++) {
		printf("%02x ", capdu[szpos]);
	}
	printf("\n");
	if ((res = nfc_initiator_transceive_bytes(pnd, capdu, capdulen, rapdu, *rapdulen, 500)) < 0) {
		return -1;
	} else {
		*rapdulen = (u32) res;
		printf("<= ");
		for (szpos = 0; szpos < *rapdulen; szpos++) {
			printf("%02x ", rapdu[szpos]);
		}
		printf("\n");
		return 0;
	}
}

#define APDU_MAX	(264)
u8 capdu[APDU_MAX];
u32 capdulen = 0;
u8 rapdu[APDU_MAX];
u32 rapdulen;

u8 is_hex(u8 c)
{
	if ((c >= '0' && c <= '9') || 
	    (c >= 'a' && c <= 'f') || 
	    (c >= 'A' && c <= 'F')) {
		return 1;
	} else {
		return 0;
	}
}

u8 ch2num(u8 c)
{
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'a' && c <= 'f')  {
		return c - 'a' + 10;
	} else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	} else {
		assert(0);
	}

}

enum status {
	HIGH4 = 0,
	LOW4,
};

u8 get_byte(u8 *sapdu, u32 *offset)
{
	u8 status = HIGH4;
	u32 off = *offset;
	u8 bvalue = 0;

	while (1) {
		if (sapdu[off] == '\0') {
			printf("illegal input index %d [%s]\n", off, sapdu);
			exit(EXIT_FAILURE);
		} else if (sapdu[off] == ' ') {
			off++;
		} else {
			if (!is_hex(sapdu[off])) {
				printf("illegal input char %c [%s]\n", sapdu[off], sapdu);
				exit(EXIT_FAILURE);
			}

			if (status == HIGH4) {
				bvalue = (ch2num(sapdu[off]) << 4);
				off++;
				status = LOW4;
			} else if (status == LOW4) {
				bvalue = bvalue | (ch2num(sapdu[off]) << 0);
				off++;
				break;
			}

		}
	}

	*offset = off;
	return bvalue;
}

void parse_apdu(char *sapdu, u8 *bapdu, u32 *size)
{
	int i = 0;
	u32 offset = 0;
	while(1) {
		if (sapdu[offset] == '\0') {
			break;
		}
		
		bapdu[i++] = get_byte(sapdu, &offset);
		/* printf("get %x offset %d\n", bapdu[i-1], offset); */

		if (i >= APDU_MAX) {
			printf("apdu too long (must <= %d)\n", APDU_MAX);
			exit(EXIT_FAILURE);
		}
	}

	*size = i;

	for(i = 0; i < *size; i++) {
		printf("0x%02x ", bapdu[i]);
	}
	printf("\n");
	
}

int main(int argc, char *argv[])
{
	u32 i;
	u32 apdu_num = argc - 1;
	nfc_device *pnd;
	nfc_target nt;
	nfc_context *context;

	if (argc == 1) {
		printf("usage: %s apdu1 apdu2...\n", argv[0]);
		exit(EXIT_FAILURE);
	}


	nfc_init(&context);
	if (context == NULL) {
		printf("Unable to init libnfc (malloc)\n");
		exit(EXIT_FAILURE);
	}
	const char *acLibnfcVersion = nfc_version();
	(void)argc;
	printf("%s uses libnfc %s\n", argv[0], acLibnfcVersion);

	pnd = nfc_open(context, NULL);

	if (pnd == NULL) {
		printf("ERROR: %s", "Unable to open NFC device.");
		exit(EXIT_FAILURE);
	}
	if (nfc_initiator_init(pnd) < 0) {
		nfc_perror(pnd, "nfc_initiator_init");
		exit(EXIT_FAILURE);
	}

	printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));

	// nfc_set_property_bool(pnd, NP_AUTO_ISO14443_4, true);
	printf("Polling for target...\n");
	while (nfc_initiator_select_passive_target(pnd, nm, NULL, 0, &nt) <= 0);
	printf("Target detected!\n");

#if 1
	for(i = 0; i < apdu_num; i++) {
		parse_apdu(argv[1 + i], capdu, &capdulen);

		rapdulen = APDU_MAX;
		if (card_transmit(pnd, capdu, capdulen, rapdu, &rapdulen) < 0)
			exit(EXIT_FAILURE);
		if (rapdulen < 2 || rapdu[rapdulen-2] != 0x90 || rapdu[rapdulen-1] != 0x00)
			exit(EXIT_FAILURE);
	}
#endif
#if 0
	// Select application
	memcpy(capdu, "\x00\xA4\x04\x00\x00", 5);
	capdulen=5;
	rapdulen=sizeof(rapdu);
	if (CardTransmit(pnd, capdu, capdulen, rapdu, &rapdulen) < 0)
		exit(EXIT_FAILURE);
	if (rapdulen < 2 || rapdu[rapdulen-2] != 0x90 || rapdu[rapdulen-1] != 0x00)
		exit(EXIT_FAILURE);
	printf("Application selected!\n");
#endif
#if 0
	u8 capdu[264];
	u32 capdulen;
	u8 rapdu[264];
	u32 rapdulen;
	// Select application
	memcpy(capdu, "\x00\xA4\x04\x00\x07\xd2\x76\x00\x00\x85\x01\x00", 12);
	capdulen=12;
	rapdulen=sizeof(rapdu);
	if (CardTransmit(pnd, capdu, capdulen, rapdu, &rapdulen) < 0)
		exit(EXIT_FAILURE);
	if (rapdulen < 2 || rapdu[rapdulen-2] != 0x90 || rapdu[rapdulen-1] != 0x00)
		exit(EXIT_FAILURE);
	printf("Application selected!\n");

	// Select Capability Container
	memcpy(capdu, "\x00\xa4\x00\x0c\x02\xe1\x03", 7);  
	capdulen=7;
	rapdulen=sizeof(rapdu);
	if (CardTransmit(pnd, capdu, capdulen, rapdu, &rapdulen) < 0)
		exit(EXIT_FAILURE);
	if (rapdulen < 2 || rapdu[rapdulen-2] != 0x90 || rapdu[rapdulen-1] != 0x00) {
		capdu[3]='\x00'; // Maybe an older Tag4 ?
		if (CardTransmit(pnd, capdu, capdulen, rapdu, &rapdulen) < 0)
			exit(EXIT_FAILURE);
	}
	printf("Capability Container selected!\n");

	// Read Capability Container
	memcpy(capdu, "\x00\xb0\x00\x00\x0f", 5);  
	capdulen=5;
	rapdulen=sizeof(rapdu);
	if (CardTransmit(pnd, capdu, capdulen, rapdu, &rapdulen) < 0)
		exit(EXIT_FAILURE);
	if (rapdulen < 2 || rapdu[rapdulen-2] != 0x90 || rapdu[rapdulen-1] != 0x00)
		exit(EXIT_FAILURE);
	printf("Capability Container header:\n");
	u32  szPos;
	for (szPos = 0; szPos < rapdulen-2; szPos++) {
		printf("%02x ", rapdu[szPos]);
	}
	printf("\n");
#endif
	nfc_close(pnd);
	nfc_exit(context);
	exit(EXIT_SUCCESS);
}
