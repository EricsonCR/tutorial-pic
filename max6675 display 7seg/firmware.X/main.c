/*
 * File:   main.c
 * Author: Ericson
 *
 * Created on 14 de abril de 2020, 04:34 PM
 */

#include <xc.h>
#include "fuses.h"
#include "oscillator.h"
#include "max7219.h"
#include "max6675.h"

unsigned long i = 0;
unsigned int f = 0, temp = 1, last_temp = 0;

void main(void) {

    oscillator_config(OSCILLATOR_32MHZ);
    max7219_config(MAX7219_BRILLO_MEDIO);
    max6675_config();

    while (1) {

        temp = max6675_read();
        if (last_temp != temp) {
            last_temp = temp;
            max7219_writeInteger(MAX7219_NIVEL_DOWN, temp);
        }
        for (i = 0; i < 100000; i++);
    }
}
