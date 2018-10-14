#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/************* MD5 start **********************************/

//verify on linux: echo -n 'xxx' | md5sum



// Constants are the integer part of the sines of integers (in radians) * 2^32.

const uint32_t k[64] = {

0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,

0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,

0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,

0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,

0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,

0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,

0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,

0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,

0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,

0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,

0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,

0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,

0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,

0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,

0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,

0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

 

// r specifies the per-round shift amounts

const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,

                      5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,

                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,

                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

 

// leftrotate function definition

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

 

void to_bytes(uint32_t val, uint8_t *bytes)

{

    bytes[0] = (uint8_t) val;

    bytes[1] = (uint8_t) (val >> 8);

    bytes[2] = (uint8_t) (val >> 16);

    bytes[3] = (uint8_t) (val >> 24);

}

 

uint32_t to_int32(const uint8_t *bytes)

{

    return (uint32_t) bytes[0]

        | ((uint32_t) bytes[1] << 8)

        | ((uint32_t) bytes[2] << 16)

        | ((uint32_t) bytes[3] << 24);

}

 

void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {

 

    // These vars will contain the hash

    uint32_t h0, h1, h2, h3;

 

    // Message (to prepare)

    uint8_t *msg = NULL;

 

    size_t new_len, offset;

    uint32_t w[16];

    uint32_t a, b, c, d, i, f, g, temp;

 

    // Initialize variables - simple count in nibbles:

    h0 = 0x67452301;

    h1 = 0xefcdab89;

    h2 = 0x98badcfe;

    h3 = 0x10325476;

 

    //Pre-processing:

    //append "1" bit to message    

    //append "0" bits until message length in bits ≡ 448 (mod 512)

    //append length mod (2^64) to message

 

    for (new_len = initial_len + 1; new_len % (512/8) != 448/8; new_len++)

        ;

 

    msg = (uint8_t*)malloc(new_len + 8);

    memcpy(msg, initial_msg, initial_len);

    msg[initial_len] = 0x80; // append the "1" bit; most significant bit is "first"

    for (offset = initial_len + 1; offset < new_len; offset++)

        msg[offset] = 0; // append "0" bits

 

    // append the len in bits at the end of the buffer.

    to_bytes(initial_len*8, msg + new_len);

    // initial_len>>29 == initial_len*8>>32, but avoids overflow.

    to_bytes(initial_len>>29, msg + new_len + 4);

 

    // Process the message in successive 512-bit chunks:

    //for each 512-bit chunk of message:

    for(offset=0; offset<new_len; offset += (512/8)) {

 

        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15

        for (i = 0; i < 16; i++)

            w[i] = to_int32(msg + offset + i*4);

 

        // Initialize hash value for this chunk:

        a = h0;

        b = h1;

        c = h2;

        d = h3;

 

        // Main loop:

        for(i = 0; i<64; i++) {

 

            if (i < 16) {

                f = (b & c) | ((~b) & d);

                g = i;

            } else if (i < 32) {

                f = (d & b) | ((~d) & c);

                g = (5*i + 1) % 16;

            } else if (i < 48) {

                f = b ^ c ^ d;

                g = (3*i + 5) % 16;          

            } else {

                f = c ^ (b | (~d));

                g = (7*i) % 16;

            }

 

            temp = d;

            d = c;

            c = b;

            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);

            a = temp;

 

        }

 

        // Add this chunk's hash to result so far:

        h0 += a;

        h1 += b;

        h2 += c;

        h3 += d;

 

    }

 

    // cleanup

    free(msg);

 

    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)

    to_bytes(h0, digest);

    to_bytes(h1, digest + 4);

    to_bytes(h2, digest + 8);

    to_bytes(h3, digest + 12);

}
/************* MD5 end **********************************/

/************* AES-128 START **********************************/
/*

 * Addition in GF(2^8)

 * http://en.wikipedia.org/wiki/Finite_field_arithmetic

 */

uint8_t gadd(uint8_t a, uint8_t b) {

	return a^b;

}



/*

 * Subtraction in GF(2^8)

 * http://en.wikipedia.org/wiki/Finite_field_arithmetic

 */

uint8_t gsub(uint8_t a, uint8_t b) {

	return a^b;

}



/*

 * Multiplication in GF(2^8)

 * http://en.wikipedia.org/wiki/Finite_field_arithmetic

 * Irreducible polynomial m(x) = x8 + x4 + x3 + x + 1

 */

uint8_t gmult(uint8_t a, uint8_t b) {



	uint8_t p = 0, i = 0, hbs = 0;



	for (i = 0; i < 8; i++) {

		if (b & 1) {

			p ^= a;

		}



		hbs = a & 0x80;

		a <<= 1;

		if (hbs) a ^= 0x1b; // 0000 0001 0001 1011	

		b >>= 1;

	}



	return (uint8_t)p;

}



/*

 * Addition of 4 byte words

 * m(x) = x4+1

 */

void coef_add(uint8_t a[], uint8_t b[], uint8_t d[]) {



	d[0] = a[0]^b[0];

	d[1] = a[1]^b[1];

	d[2] = a[2]^b[2];

	d[3] = a[3]^b[3];

}



/*

 * Multiplication of 4 byte words

 * m(x) = x4+1

 */

void coef_mult(uint8_t *a, uint8_t *b, uint8_t *d) {



	d[0] = gmult(a[0],b[0])^gmult(a[3],b[1])^gmult(a[2],b[2])^gmult(a[1],b[3]);

	d[1] = gmult(a[1],b[0])^gmult(a[0],b[1])^gmult(a[3],b[2])^gmult(a[2],b[3]);

	d[2] = gmult(a[2],b[0])^gmult(a[1],b[1])^gmult(a[0],b[2])^gmult(a[3],b[3]);

	d[3] = gmult(a[3],b[0])^gmult(a[2],b[1])^gmult(a[1],b[2])^gmult(a[0],b[3]);

}



/*

 * The cipher Key.	

 */

int K;



/*

 * Number of columns (32-bit words) comprising the State. For this 

 * standard, Nb = 4.

 */

int Nb = 4;



/*

 * Number of 32-bit words comprising the Cipher Key. For this 

 * standard, Nk = 4, 6, or 8.

 */

int Nk = 4;



/*

 * Number of rounds, which is a function of  Nk  and  Nb (which is 

 * fixed). For this standard, Nr = 10, 12, or 14.

 */

int Nr = 10;



/*

 * S-box transformation table

 */

static uint8_t s_box[256] = {

	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f

	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0

	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1

	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2

	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3

	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4

	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5

	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6

	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7

	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8

	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9

	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // a

	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // b

	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // c

	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // d

	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // e

	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};// f



/*

 * Inverse S-box transformation table

 */

static uint8_t inv_s_box[256] = {

	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f

	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, // 0

	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1

	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2

	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3

	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4

	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5

	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6

	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7

	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8

	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9

	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // a

	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // b

	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // c

	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // d

	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // e

	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d};// f





/*

 * Generates the round constant Rcon[i]

 */

uint8_t R[] = {0x02, 0x00, 0x00, 0x00};

 

uint8_t * Rcon(uint8_t i) {

	

	if (i == 1) {

		R[0] = 0x01; // x^(1-1) = x^0 = 1

	} else if (i > 1) {

		R[0] = 0x02;

		i--;

		while (i-1 > 0) {

			R[0] = gmult(R[0], 0x02);

			i--;

		}

	}

	

	return R;

}



/*

 * Transformation in the Cipher and Inverse Cipher in which a Round 

 * Key is added to the State using an XOR operation. The length of a 

 * Round Key equals the size of the State (i.e., for Nb = 4, the Round 

 * Key length equals 128 bits/16 bytes).

 */

void add_round_key(uint8_t *state, uint8_t *w, uint8_t r) {

	

	uint8_t c;

	

	for (c = 0; c < Nb; c++) {

		state[Nb*0+c] = state[Nb*0+c]^w[4*Nb*r+4*c+0];   //debug, so it works for Nb !=4 

		state[Nb*1+c] = state[Nb*1+c]^w[4*Nb*r+4*c+1];

		state[Nb*2+c] = state[Nb*2+c]^w[4*Nb*r+4*c+2];

		state[Nb*3+c] = state[Nb*3+c]^w[4*Nb*r+4*c+3];	

	}

}



/*

 * Transformation in the Cipher that takes all of the columns of the 

 * State and mixes their data (independently of one another) to 

 * produce new columns.

 */

void mix_columns(uint8_t *state) {



	uint8_t a[] = {0x02, 0x01, 0x01, 0x03}; // a(x) = {02} + {01}x + {01}x2 + {03}x3

	uint8_t i, j, col[4], res[4];



	for (j = 0; j < Nb; j++) {

		for (i = 0; i < 4; i++) {

			col[i] = state[Nb*i+j];

		}



		coef_mult(a, col, res);



		for (i = 0; i < 4; i++) {

			state[Nb*i+j] = res[i];

		}

	}

}



/*

 * Transformation in the Inverse Cipher that is the inverse of 

 * MixColumns().

 */

void inv_mix_columns(uint8_t *state) {



	uint8_t a[] = {0x0e, 0x09, 0x0d, 0x0b}; // a(x) = {0e} + {09}x + {0d}x2 + {0b}x3

	uint8_t i, j, col[4], res[4];



	for (j = 0; j < Nb; j++) {

		for (i = 0; i < 4; i++) {

			col[i] = state[Nb*i+j];

		}



		coef_mult(a, col, res);



		for (i = 0; i < 4; i++) {

			state[Nb*i+j] = res[i];

		}

	}

}



/*

 * Transformation in the Cipher that processes the State by cyclically 

 * shifting the last three rows of the State by different offsets. 

 */

void shift_rows(uint8_t *state) {



	uint8_t i, k, s, tmp;



	for (i = 1; i < 4; i++) {

		// shift(1,4)=1; shift(2,4)=2; shift(3,4)=3

		// shift(r, 4) = r;

		s = 0;

		while (s < i) {

			tmp = state[Nb*i+0];

			

			for (k = 1; k < Nb; k++) {

				state[Nb*i+k-1] = state[Nb*i+k];

			}



			state[Nb*i+Nb-1] = tmp;

			s++;

		}

	}

}



/*

 * Transformation in the Inverse Cipher that is the inverse of 

 * ShiftRows().

 */

void inv_shift_rows(uint8_t *state) {



	uint8_t i, k, s, tmp;



	for (i = 1; i < 4; i++) {

		s = 0;

		while (s < i) {

			tmp = state[Nb*i+Nb-1];

			

			for (k = Nb-1; k > 0; k--) {

				state[Nb*i+k] = state[Nb*i+k-1];

			}



			state[Nb*i+0] = tmp;

			s++;

		}

	}

}


/*

 * Transformation in the Cipher that processes the State using a non­

 * linear byte substitution table (S-box) that operates on each of the 

 * State bytes independently. 

 */

void sub_bytes(uint8_t *state) {



	uint8_t i, j;

	uint8_t row, col;



	for (i = 0; i < 4; i++) {

		for (j = 0; j < Nb; j++) {

			row = (state[Nb*i+j] & 0xf0) >> 4;

			col = state[Nb*i+j] & 0x0f;

			state[Nb*i+j] = s_box[16*row+col];

		}

	}

}


/*

 * Transformation in the Inverse Cipher that is the inverse of 

 * SubBytes().

 */

void inv_sub_bytes(uint8_t *state) {



	uint8_t i, j;

	uint8_t row, col;



	for (i = 0; i < 4; i++) {

		for (j = 0; j < Nb; j++) {

			row = (state[Nb*i+j] & 0xf0) >> 4;

			col = state[Nb*i+j] & 0x0f;

			state[Nb*i+j] = inv_s_box[16*row+col];

		}

	}

}



/*

 * Function used in the Key Expansion routine that takes a four-byte 

 * input word and applies an S-box to each of the four bytes to 

 * produce an output word.

 */

void sub_word(uint8_t *w) {



	uint8_t i;



	for (i = 0; i < 4; i++) {

		w[i] = s_box[16*((w[i] & 0xf0) >> 4) + (w[i] & 0x0f)];

	}

}



/*

 * Function used in the Key Expansion routine that takes a four-byte 

 * word and performs a cyclic permutation. 

 */

void rot_word(uint8_t *w) {



	uint8_t tmp;

	uint8_t i;



	tmp = w[0];



	for (i = 0; i < 3; i++) {

		w[i] = w[i+1];

	}



	w[3] = tmp;

}



/*

 * Key Expansion

 */

void key_expansion(uint8_t *key, uint8_t *w) {



	uint8_t tmp[4];

	uint8_t i, j;

	uint8_t len = Nb*(Nr+1);



	for (i = 0; i < Nk; i++) {

		w[4*i+0] = key[4*i+0];

		w[4*i+1] = key[4*i+1];

		w[4*i+2] = key[4*i+2];

		w[4*i+3] = key[4*i+3];

	}



	for (i = Nk; i < len; i++) {

		tmp[0] = w[4*(i-1)+0];

		tmp[1] = w[4*(i-1)+1];

		tmp[2] = w[4*(i-1)+2];

		tmp[3] = w[4*(i-1)+3];



		if (i%Nk == 0) {



			rot_word(tmp);

			sub_word(tmp);

			coef_add(tmp, Rcon(i/Nk), tmp);



		} else if (Nk > 6 && i%Nk == 4) {



			sub_word(tmp);



		}



		w[4*i+0] = w[4*(i-Nk)+0]^tmp[0];

		w[4*i+1] = w[4*(i-Nk)+1]^tmp[1];

		w[4*i+2] = w[4*(i-Nk)+2]^tmp[2];

		w[4*i+3] = w[4*(i-Nk)+3]^tmp[3];

	}

}



void __aes_encryt(uint8_t *in, uint8_t *out, uint8_t *w) {



	uint8_t state[4*Nb];

	uint8_t r, i, j;



	for (i = 0; i < 4; i++) {

		for (j = 0; j < Nb; j++) {

			state[Nb*i+j] = in[i+4*j];

		}

	}



	add_round_key(state, w, 0);



	for (r = 1; r < Nr; r++) {

		sub_bytes(state);

		shift_rows(state);

		mix_columns(state);

		add_round_key(state, w, r);

	}



	sub_bytes(state);

	shift_rows(state);

	add_round_key(state, w, Nr);



	for (i = 0; i < 4; i++) {

		for (j = 0; j < Nb; j++) {

			out[i+4*j] = state[Nb*i+j];

		}

	}

}



void __aes_decrypt(uint8_t *in, uint8_t *out, uint8_t *w) {



	uint8_t state[4*Nb];

	uint8_t r, i, j;



	for (i = 0; i < 4; i++) {

		for (j = 0; j < Nb; j++) {

			state[Nb*i+j] = in[i+4*j];

		}

	}



	add_round_key(state, w, Nr);



	for (r = Nr-1; r >= 1; r--) {

		inv_shift_rows(state);

		inv_sub_bytes(state);

		add_round_key(state, w, r);

		inv_mix_columns(state);

	}



	inv_shift_rows(state);

	inv_sub_bytes(state);

	add_round_key(state, w, 0);



	for (i = 0; i < 4; i++) {

		for (j = 0; j < Nb; j++) {

			out[i+4*j] = state[Nb*i+j];

		}

	}

}



int aes_encrypt(uint8_t *in, uint8_t *out, uint8_t *key)

{

	uint8_t w[1024] = {0};

	key_expansion(key, w);

    __aes_encryt(in, out, w);

    return 0;

}



int aes_decrypt(uint8_t *in, uint8_t *out, uint8_t *key)

{

	uint8_t w[176] = {0};

	key_expansion(key, w);

    __aes_decrypt(in, out, w);

    return 0;

}

/************* AES-128 END **********************************/

unsigned char md5sum[16];
unsigned char in[16];
unsigned char out[16];

int id_build(unsigned char *indata, unsigned int inlen, unsigned char *out)
{
    int i;
    unsigned char dec[16];


	/* 128 bits */
	uint8_t key[] = {   /* FIXME: derive the key */
		0x2b, 0x7e, 0x15, 0x16,
		0x28, 0xae, 0xd2, 0xa6,
		0xab, 0xf7, 0x15, 0x88,
		0x09, 0xcf, 0x4f, 0x3c };

	printf("indata:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", indata[4*i+0], indata[4*i+1], indata[4*i+2], indata[4*i+3]);
	}

	printf("\n");
    /* 1 md5 */
    md5(indata, inlen, md5sum);

	printf("md5sum:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", md5sum[4*i+0], md5sum[4*i+1], md5sum[4*i+2], md5sum[4*i+3]);
	}
	printf("\n");

    /* 2 aes encrypt */
	aes_encrypt(md5sum, out, key);

	printf("encrypt:\n");

	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", out[4*i+0], out[4*i+1], out[4*i+2], out[4*i+3]);
	}

	printf("\n");

	aes_decrypt(out, dec, key);
	printf("decrypt:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", dec[4*i+0], dec[4*i+1], dec[4*i+2], dec[4*i+3]);
	}

	printf("\n\n");
    return 0;
}

int id_verify(unsigned char *indata, unsigned int inlen, unsigned char *out)
{
    uint32_t i;
    uint8_t _out[16];

    id_build(indata, inlen, _out);

	printf("_out:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", _out[4*i+0], _out[4*i+1], _out[4*i+2], _out[4*i+3]);
	}
	printf("\n");

	printf("out:\n");
	for (i = 0; i < 4; i++) {
		printf("%02x %02x %02x %02x ", out[4*i+0], out[4*i+1], out[4*i+2], out[4*i+3]);
	}
	printf("\n");

    for(i = 0; i < sizeof(_out); i++) {
        if (_out[i] != out[i]) {
            printf("verify fail!\n");
            return -1;
        }
    }

    printf("verify succ!\n");
    return 0;

}

int main()
{
	uint8_t indata[] = {
		0x00, 0x01, 0x02, 0x03,
		0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b,
		0x0c, 0x0d, 0x0e, 0x0f 
    };

    id_build(indata, sizeof(indata), out);

    id_verify(indata, sizeof(indata), out);

    return 0;
}
