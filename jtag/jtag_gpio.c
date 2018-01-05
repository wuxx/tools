#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned int u32;
typedef   signed int s32;

typedef unsigned short u16;
typedef   signed short s16;

typedef unsigned char u8;
typedef   signed char s8;

#define GPIO_DIR      "/sys/class/gpio"

#define GPIO_EXPORT   "/sys/class/gpio/export"

#define GPIO_DIR      "/sys/class/gpio"

#define GPIO_EXPORT   "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"

/* BCM GPIO NUM */
#if 0
#define TCK     (26)
#define TMS     (19)
#define TDI     (13)
#define TDO     (6)
#else
/* wPi GPIO NUM */
//#define TCK     (25)
//#define TMS     (24)
//#define TDI     (23)
//#define TDO     (22)
#define TCK     (14)
#define TMS     (6)
#define TDI     (12)
#define TDO     (13)
#endif

enum TAP_STATE_E {
    TAP_DREXIT2 = 0x0,
    TAP_DREXIT1 = 0x1,
    TAP_DRSHIFT = 0x2,
    TAP_DRPAUSE = 0x3,
    TAP_IRSELECT = 0x4,
    TAP_DRUPDATE = 0x5,
    TAP_DRCAPTURE = 0x6,
    TAP_DRSELECT = 0x7,
    TAP_IREXIT2 = 0x8,
    TAP_IREXIT1 = 0x9,
    TAP_IRSHIFT = 0xa,
    TAP_IRPAUSE = 0xb,
    TAP_IDLE = 0xc,
    TAP_IRUPDATE = 0xd,
    TAP_IRCAPTURE = 0xe,
    TAP_RESET = 0x0f,
};

u32 idcode[4];

u8 get_bit(void *map, u32 bit_max, u32 bit_index)
{
    u8  bit;
    u32 word_index, word_offset;
    u32 *pmap;

    bit_index = bit_index % bit_max;

    pmap = map;
    word_index  = bit_index / 32;
    word_offset = bit_index % 32;

    bit = pmap[word_index] & (0x1 << word_offset);

    return bit;
}

u8 set_bit(void *map, u32 bit_max, u32 bit_index, u8 bit)
{
    u32 word_index, word_offset;
    u32 *pmap;
    u32 bit_mask;

    bit_index = bit_index % bit_max;

    pmap = map;
    word_index  = bit_index / 32;
    word_offset = bit_index % 32;

    if (bit == 0) {
        bit_mask = ~(0x1 << word_offset);
        pmap[word_index] = (pmap[word_index]) & bit_mask;
    } else {    /* b == 1 */
        bit_mask = (0x1 << word_offset);
        pmap[word_index] = (pmap[word_index]) | bit_mask;
    }

    bit = pmap[word_index] & (0x1 << word_offset);
    return 0;
}

int gpio_get(int gpio_num)
{
    int i;
    FILE *fp;
    char cmd[512];
    char out[512];

    snprintf(cmd, sizeof(cmd), "gpio read %d", gpio_num);

    fp = popen(cmd, "r");
    fread(out, sizeof(char), sizeof(out), fp);
    /* printf("gpio %d read [%s] \n", gpio_num, out); */

#if 0
    for(int i = 0; i < strlen(out); i++) {
        printf("[%d]: 0x%02x\n", i, out[i]);
    }
#endif

    if (strcmp(out, "0\n") == 0) {
        pclose(fp);
        return 0;
    } else if (strcmp(out, "1\n") == 0) {
        pclose(fp);
        return 1;
    } else {
        printf("error: gpio %d read return [%s]\n", gpio_num, out);

        for(i = 0; i < 10; i++) {
            printf("[%d]: 0x%02x\n", i, out[i]);
        }

        exit(-1);
    }
}

void gpio_set(int gpio_num, int value)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "gpio write %d %d", gpio_num, value);
    system(cmd);
    if (gpio_get(gpio_num) != value) {
        printf("error: gpio set fail \n");
        exit(-1);
    }

}

#if 0
void jtag_clk()
{
    gpio_set(TCK, 0);
    gpio_set(TCK, 1);
    gpio_set(TCK, 0);
}
#endif

void __gpio_init(int gpio_num, char *direct)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "gpio mode %d %s", gpio_num, direct);
    printf("cmd0: %s\n", cmd);
    system(cmd);
}

void gpio_init()
{
    /* TCK OUT */
    /* TMS OUT */
    /* TDI OUT */
    /* TDO IN  */
    __gpio_init(TCK, "out");
    __gpio_init(TMS, "out");
    __gpio_init(TDI, "out");
    __gpio_init(TDO, "in");
}

int jtag_clk()
{
    int tdo = 0;
    gpio_set(TCK, 0);
    usleep(1);
    gpio_set(TCK, 1);
    usleep(1);
    tdo = gpio_get(TDO);

    gpio_set(TCK, 0);

    return tdo;
}

void tap_reset()
{
    int i;
    gpio_set(TMS, 1);

    for(i = 0; i < 5; i++) {
        jtag_clk();
    }
}

void tap_state(int state)
{
    tap_reset();

    switch(state) {
        case (TAP_IRSHIFT):
            gpio_set(TMS, 0);
            jtag_clk();
            gpio_set(TMS, 1);
            jtag_clk();
            jtag_clk();
            gpio_set(TMS, 0);
            jtag_clk();
            jtag_clk();
            break;
        default:
            printf("unknown state %d \n", state);
            exit(-1);
    }

}

int main()
{
    int i = 0;
    u8 b = 0;
    u32 irlen = 0;

    gpio_init();
    gpio_get(TCK);
    gpio_get(TMS);
    gpio_get(TDI);
    gpio_get(TDO);


#if 0
    for(i = 0; i < 100; i++) {
        jtag_clk();
    }

    gpio_set();
#endif

#if 0
    tap_reset();
    tap_reset();

    tap_state(TAP_IRSHIFT);

    /* go to Shift-DR */
    gpio_set(TMS, 0);
    jtag_clk();
        //printf("[%d]: %d\n", i, jtag_clk());

    gpio_set(TMS, 1);
    jtag_clk();
        //printf("[%d]: %d\n", i, jtag_clk());

    gpio_set(TMS, 0);
    jtag_clk();
        //printf("[%d]: %d\n", i, jtag_clk());

    gpio_set(TMS, 0);
    jtag_clk();
        //printf("[%d]: %d\n", i, jtag_clk());

    for(i = 0; i < 64; i++) {
        printf("[%d]: %d\n", i, jtag_clk());
    }


#endif

    /* IR chain length */
    tap_reset();
    tap_reset();

    /* goto Select-DR */
    gpio_set(TMS, 0);
    jtag_clk();

    gpio_set(TMS, 1);
    jtag_clk();

    /* goto Shift-IR */
    gpio_set(TMS, 1);
    jtag_clk();

    gpio_set(TMS, 0);
    jtag_clk();

    gpio_set(TMS, 0);
    jtag_clk();

    printf("IR len: \n");
    /* fill the chain with 0 */
    gpio_set(TDI, 0);
    for(i = 0; i < 70; i++) {
        //printf("[%d]: %d\n", i, jtag_clk());
        jtag_clk();
    }

    gpio_set(TDI, 1);
    for(i = 0; i < 70; i++) {
        b = jtag_clk();

        if (b == 0) {
            irlen++;
        }
        printf("[%d]: %d\n", i, b);
    }

    printf("IR len: %d\n", irlen);

    /* goto Select-DR */
    gpio_set(TMS, 1);
    jtag_clk();

    gpio_set(TMS, 1);
    jtag_clk();

    gpio_set(TMS, 1);
    jtag_clk();

    /* goto Shift-DR */
    gpio_set(TDI, 0);

    gpio_set(TMS, 0);
    jtag_clk();

    gpio_set(TMS, 0);
    jtag_clk();

    printf("number of device: \n");
    /* fill the chain with 0 */
    gpio_set(TDI, 0);
    for(i = 0; i < 70; i++) {
        printf("[%d]: %d\n", i, jtag_clk());
    }

    gpio_set(TDI, 1);
    for(i = 0; i < 70; i++) {
        printf("[%d]: %d\n", i, jtag_clk());
    }

#if 1
    /* number of devices in the jtag chain */
    tap_reset();
    tap_reset();

    /* goto Select-DR */
    gpio_set(TMS, 0);
    jtag_clk();

    gpio_set(TMS, 1);
    jtag_clk();

    /* goto Shift-DR */
    gpio_set(TMS, 0);
    jtag_clk();

    gpio_set(TMS, 0);
    jtag_clk();

    /* send plenty of ones */
    printf("IDCODE: \n");

    gpio_set(TDI, 0);
    //tap_state(TAP_IRSHIFT);
    for(i = 0; i < 70; i++) {
        printf("[%d]: %d\n", i, jtag_clk());
    }

    gpio_set(TDI, 1);
    for(i = 0; i < 70; i++) {
        printf("[%d]: %d\n", i, jtag_clk());
    }

#endif
    return 0;
}

