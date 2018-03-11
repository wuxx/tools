#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
if ((signal wire length) >= (wavelength / 10)) {
    we need impedance matching
}
*/

const double electromagnetic_wave_speed = 300000000; /* meter / second */
const double pp = 4.7; /* dielectric constant */

/* 1 inch = 2.54 cm */
/* 1000 mil = 25.4 mm */
/* 1000 / 25.4 mil = 1 mm */

int main(int argc, char **argv)
{
    int signal_freq;
    double signal_cycle;
    double wave_speed;
    double wave_length;

    if (argc == 1) {
        printf("%s signal_freq\n", argv[0]);
        exit(1);
    }

    /* wave_speed = electromagnetic_wave_speed * (1 / sqrt(pp)); */ /* meter per second */
    /* wave_speed = (electromagnetic_wave_speed * (1 / sqrt(pp)) * 1000) / 1000000000; */ /* mm per ns */
    wave_speed = (electromagnetic_wave_speed * (1 / sqrt(pp)) ) / 1000000; /* mm per ns */

    printf("wave_speed = %f mm / ns \n", wave_speed);

    signal_freq = strtoul(argv[1], NULL, 0);
    signal_cycle = 1000000000.0 / signal_freq;  /* ns */

    printf("signal_cycle = %f ns \n", signal_cycle);

    /* wave_speed = wave_length / signal_cycle */
    wave_length = wave_speed * signal_cycle;
    printf("(wave_length     ) = %fmm (%f mil)\n", wave_length, wave_length * 1000 / 25.4);

    printf("(wave_length / 10) = %fmm (%f mil)\n", wave_length / 10, wave_length * 100 / 25.4);
    return 0;
}
