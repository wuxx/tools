#include <stdio.h>
#include <unistd.h>


unsigned char stm32f407_led_1_bin[] = {
    0x08, 0x04, 0x00, 0x20, 0x9d, 0x01, 0x00, 0x08, 0xa5, 0x02, 0x00, 0x08,
    0xa1, 0x02, 0x00, 0x08, 0xa3, 0x02, 0x00, 0x08, 0xe5, 0x01, 0x00, 0x08,
    0xcd, 0x03, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x02, 0x00, 0x08,
    0xe7, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0xa7, 0x02, 0x00, 0x08,
    0x79, 0x03, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08,
    0xb7, 0x01, 0x00, 0x08, 0xb7, 0x01, 0x00, 0x08, 0xdf, 0xf8, 0x0c, 0xd0,
    0x00, 0xf0, 0x18, 0xf8, 0x00, 0x48, 0x00, 0x47, 0xed, 0x03, 0x00, 0x08,
    0x08, 0x04, 0x00, 0x20, 0x06, 0x48, 0x80, 0x47, 0x06, 0x48, 0x00, 0x47,
    0xfe, 0xe7, 0xfe, 0xe7, 0xfe, 0xe7, 0xfe, 0xe7, 0xfe, 0xe7, 0xfe, 0xe7,
    0xfe, 0xe7, 0xfe, 0xe7, 0xfe, 0xe7, 0xfe, 0xe7, 0x7d, 0x03, 0x00, 0x08,
    0x89, 0x01, 0x00, 0x08, 0x06, 0x4c, 0x07, 0x4d, 0x06, 0xe0, 0xe0, 0x68,
    0x40, 0xf0, 0x01, 0x03, 0x94, 0xe8, 0x07, 0x00, 0x98, 0x47, 0x10, 0x34,
    0xac, 0x42, 0xf6, 0xd3, 0xff, 0xf7, 0xda, 0xff, 0x48, 0x04, 0x00, 0x08,
    0x68, 0x04, 0x00, 0x08, 0xfe, 0xe7, 0x70, 0x47, 0x01, 0xb5, 0x00, 0x98,
    0x41, 0x1e, 0x00, 0x91, 0x00, 0x28, 0xfa, 0xd1, 0x08, 0xbd, 0xf0, 0xb5,
    0x00, 0x23, 0x01, 0x24, 0x03, 0x27, 0x0d, 0x68, 0x04, 0xfa, 0x03, 0xf2,
    0x15, 0x40, 0x95, 0x42, 0x42, 0xd1, 0xd0, 0xf8, 0x00, 0xc0, 0x5e, 0x00,
    0x07, 0xfa, 0x06, 0xf5, 0x2c, 0xea, 0x05, 0x0c, 0xc0, 0xf8, 0x00, 0xc0,
    0x91, 0xf8, 0x04, 0xc0, 0xd0, 0xf8, 0x00, 0xe0, 0x0c, 0xfa, 0x06, 0xfc,
    0x4c, 0xea, 0x0e, 0x0c, 0xc0, 0xf8, 0x00, 0xc0, 0x91, 0xf8, 0x04, 0xc0,
    0xbc, 0xf1, 0x01, 0x0f, 0x02, 0xd0, 0xbc, 0xf1, 0x02, 0x0f, 0x1f, 0xd1,
    0xd0, 0xf8, 0x08, 0xc0, 0x2c, 0xea, 0x05, 0x0c, 0xc0, 0xf8, 0x08, 0xc0,
    0x91, 0xf8, 0x05, 0xc0, 0xd0, 0xf8, 0x08, 0xe0, 0x0c, 0xfa, 0x06, 0xfc,
    0x4c, 0xea, 0x0e, 0x0c, 0xc0, 0xf8, 0x08, 0xc0, 0xd0, 0xf8, 0x04, 0xc0,
    0x2c, 0xea, 0x02, 0x0c, 0xc0, 0xf8, 0x04, 0xc0, 0x42, 0x68, 0x91, 0xf8,
    0x06, 0xc0, 0x0c, 0xfa, 0x03, 0xfc, 0x1f, 0xfa, 0x8c, 0xfc, 0x42, 0xea,
    0x0c, 0x02, 0x42, 0x60, 0xc2, 0x68, 0xaa, 0x43, 0xc2, 0x60, 0xca, 0x79,
    0xc5, 0x68, 0xb2, 0x40, 0x2a, 0x43, 0xc2, 0x60, 0x5b, 0x1c, 0x10, 0x2b,
    0xb3, 0xd3, 0xf0, 0xbd, 0x41, 0x83, 0x70, 0x47, 0x01, 0x83, 0x70, 0x47,
    0xfe, 0xe7, 0xfe, 0xe7, 0x70, 0x47, 0x70, 0x47, 0x04, 0x4a, 0x00, 0x29,
    0x11, 0x68, 0x01, 0xd0, 0x01, 0x43, 0x00, 0xe0, 0x81, 0x43, 0x11, 0x60,
    0x70, 0x47, 0x00, 0x00, 0x30, 0x38, 0x02, 0x40, 0x70, 0x47, 0x00, 0x00,
    0x0c, 0xb5, 0x00, 0x20, 0x27, 0x49, 0x01, 0x90, 0x00, 0x90, 0x0a, 0x68,
    0x42, 0xf4, 0x80, 0x32, 0x0a, 0x60, 0x4f, 0xf4, 0xa0, 0x63, 0x0a, 0x68,
    0x02, 0xf4, 0x00, 0x32, 0x00, 0x92, 0x01, 0x9a, 0x52, 0x1c, 0x01, 0x92,
    0x00, 0x9a, 0x12, 0xb9, 0x01, 0x9a, 0x9a, 0x42, 0xf3, 0xd1, 0x0a, 0x68,
    0x92, 0x03, 0x34, 0xd5, 0x01, 0x20, 0x00, 0x90, 0x1a, 0x48, 0x40, 0x30,
    0x02, 0x68, 0x42, 0xf0, 0x80, 0x52, 0x02, 0x60, 0x18, 0x48, 0x02, 0x68,
    0x42, 0xf4, 0x80, 0x42, 0x02, 0x60, 0x15, 0x48, 0x08, 0x30, 0x02, 0x68,
    0x02, 0x60, 0x02, 0x68, 0x42, 0xf4, 0x00, 0x42, 0x02, 0x60, 0x02, 0x68,
    0x42, 0xf4, 0xa0, 0x52, 0x02, 0x60, 0x03, 0x1f, 0x10, 0x4a, 0x1a, 0x60,
    0x0a, 0x68, 0x42, 0xf0, 0x80, 0x72, 0x0a, 0x60, 0x0a, 0x68, 0x92, 0x01,
    0xfc, 0xd5, 0x0d, 0x4a, 0x40, 0xf2, 0x05, 0x61, 0x11, 0x60, 0x01, 0x68,
    0x21, 0xf0, 0x03, 0x01, 0x01, 0x60, 0x01, 0x68, 0x41, 0xf0, 0x02, 0x01,
    0x01, 0x60, 0x01, 0x68, 0xc1, 0xf3, 0x81, 0x01, 0x02, 0x29, 0xfa, 0xd1,
    0x0c, 0xbd, 0x00, 0x90, 0x0c, 0xbd, 0x00, 0x00, 0x00, 0x38, 0x02, 0x40,
    0x00, 0x70, 0x00, 0x40, 0x08, 0x54, 0x40, 0x07, 0x00, 0x3c, 0x02, 0x40,
    0x70, 0x47, 0x00, 0x00, 0x0f, 0x48, 0x10, 0xb5, 0x01, 0x68, 0x41, 0xf0,
    0x01, 0x01, 0x01, 0x60, 0x0c, 0x4a, 0x00, 0x21, 0x08, 0x32, 0x11, 0x60,
    0x02, 0x68, 0x0b, 0x4b, 0x1a, 0x40, 0x02, 0x60, 0x03, 0x1d, 0x0a, 0x4a,
    0x1a, 0x60, 0x02, 0x68, 0x22, 0xf4, 0x80, 0x22, 0x02, 0x60, 0x05, 0x48,
    0x0c, 0x30, 0x01, 0x60, 0xff, 0xf7, 0x8a, 0xff, 0x05, 0x49, 0x4f, 0xf0,
    0x00, 0x60, 0x08, 0x60, 0x10, 0xbd, 0x00, 0x00, 0x00, 0x38, 0x02, 0x40,
    0xff, 0xff, 0xf6, 0xfe, 0x10, 0x30, 0x00, 0x24, 0x08, 0xed, 0x00, 0xe0,
    0xfe, 0xe7, 0x02, 0xe0, 0x08, 0xc8, 0x12, 0x1f, 0x08, 0xc1, 0x00, 0x2a,
    0xfa, 0xd1, 0x70, 0x47, 0x70, 0x47, 0x00, 0x20, 0x01, 0xe0, 0x01, 0xc1,
    0x12, 0x1f, 0x00, 0x2a, 0xfb, 0xd1, 0x70, 0x47, 0x01, 0x21, 0x08, 0x20,
    0xff, 0xf7, 0x5a, 0xff, 0x11, 0x48, 0x4f, 0xf4, 0x70, 0x45, 0x01, 0x21,
    0x05, 0x60, 0x01, 0x71, 0x00, 0x21, 0x81, 0x71, 0x03, 0x22, 0x42, 0x71,
    0xc1, 0x71, 0x0d, 0x4c, 0x01, 0x46, 0x20, 0x46, 0xff, 0xf7, 0xf1, 0xfe,
    0x0b, 0x4f, 0xa6, 0x14, 0x6f, 0xf0, 0x7f, 0x48, 0x31, 0x46, 0x20, 0x46,
    0xff, 0xf7, 0x3c, 0xff, 0x38, 0x46, 0xff, 0xf7, 0xdf, 0xfe, 0x29, 0x46,
    0x20, 0x46, 0xff, 0xf7, 0x33, 0xff, 0x40, 0x46, 0xff, 0xf7, 0xd8, 0xfe,
    0xf0, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x0c, 0x02, 0x40,
    0xff, 0xff, 0x3f, 0x00, 0x68, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20,
    0x08, 0x00, 0x00, 0x00, 0xce, 0x03, 0x00, 0x08, 0x70, 0x04, 0x00, 0x08,
    0x08, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 0x00, 0xde, 0x03, 0x00, 0x08,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int main()
{
    write(STDOUT_FILENO, stm32f407_led_1_bin, sizeof(stm32f407_led_1_bin));

    return 0;
}