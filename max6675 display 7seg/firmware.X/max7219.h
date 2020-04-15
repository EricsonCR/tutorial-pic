/* 
 * File:   max7219.h
 * Author: Ericson
 *
 * Created on 6 de abril de 2020, 04:23 PM
 */

#ifndef MAX7219_H
#define	MAX7219_H

char __digitos_1[11] = {
    0b11110101,
    0b01100000,
    0b10110110,
    0b11110010,
    0b01100011,
    0b11010011,
    0b11010111,
    0b01110000,
    0b11110111,
    0b11110011,
    0b00000000
};

char __digitos_2[11] = {
    0b11001111,
    0b00000011,
    0b10101110,
    0b00101111,
    0b01100011,
    0b01101101,
    0b11101101,
    0b00001011,
    0b11101111,
    0b01101111,
    0b00000000
};

#define max7219_din         LATCbits.LATC1
#define max7219_din_tris    TRISCbits.TRISC1
#define max7219_load        LATCbits.LATC2
#define max7219_load_tris   TRISCbits.TRISC2
#define max7219_clk         LATCbits.LATC3
#define max7219_clk_tris    TRISCbits.TRISC3

#define MAX7219_POINTS_ON   0x01
#define MAX7219_POINTS_OFF  0x00
#define MAX7219_NIVEL_UP    0x01
#define MAX7219_NIVEL_DOWN  0x00
#define MAX7219_BRILLO_BAJO     0x00
#define MAX7219_BRILLO_MEDIO    0x08
#define MAX7219_BRILLO_ALTO     0x0F

#define	MAX7219_DECO	0x09
#define	MAX7219_BRIG	0x0A
#define	MAX7219_SCAN	0x0B
#define	MAX7219_SHUT	0x0C
#define	MAX7219_TEST	0x0F

void max7219_config(unsigned int brig);
void __max7219_write(unsigned int address, unsigned int data);
void max7219_writeInteger(unsigned int nivel, unsigned int valor);
void max7219_points(unsigned int points, unsigned int nivel);

void max7219_config(unsigned int brig) {
    max7219_load = 1;
    max7219_din_tris = 0;
    max7219_load_tris = 0;
    max7219_clk_tris = 0;

    __max7219_write(MAX7219_DECO, 0x00);
    __max7219_write(MAX7219_BRIG, brig);
    __max7219_write(MAX7219_SCAN, 0x07);
    __max7219_write(MAX7219_SHUT, 0x01);
    __max7219_write(MAX7219_TEST, 0x00);

    max7219_writeInteger(MAX7219_NIVEL_UP, 0);
    max7219_writeInteger(MAX7219_NIVEL_DOWN, 0);
}

void __max7219_write(unsigned int address, unsigned int data) {
    unsigned int i = 0, j;
    unsigned int dataSend = 0;
    dataSend = address;
    dataSend <<= 8;
    dataSend += data;
    dataSend &= 0x0FFF;
    max7219_load = 0;
    for (i = 16; i > 0; i--) {
        if (dataSend & (1 << (i - 1))) {
            max7219_din = 1;
        } else {
            max7219_din = 0;
        }
        max7219_clk = 1;
        max7219_clk = 0;
    }
    max7219_load = 1;
}

void max7219_writeInteger(unsigned int nivel, unsigned int valor) {
    if (nivel == MAX7219_NIVEL_UP) {
        __max7219_write(1, __digitos_1[valor / 1000]);
        __max7219_write(5, __digitos_1[(valor % 1000) / 100]);
        __max7219_write(7, __digitos_1[((valor % 1000) % 100) / 10]);
        __max7219_write(3, __digitos_1[((valor % 1000) % 100) % 10]);
    } else {
        __max7219_write(8, __digitos_2[valor / 1000]);
        __max7219_write(6, __digitos_2[(valor % 1000) / 100]);
        __max7219_write(2, __digitos_2[((valor % 1000) % 100) / 10]);
        __max7219_write(4, __digitos_2[((valor % 1000) % 100) % 10]);
    }
}

void max7219_points(unsigned int points, unsigned int nivel) {
    unsigned int i = 0;
    if (points == MAX7219_POINTS_ON) {
        if (nivel == MAX7219_NIVEL_UP) {
            for (i = 0; i < 10; i++) {
                __digitos_1[i] |= 0x08;
            }
        } else {
            for (i = 0; i < 10; i++) {
                __digitos_2[i] |= 0x10;
            }
        }
    } else {
        if (nivel == MAX7219_NIVEL_UP) {
            for (i = 0; i < 10; i++) {
                __digitos_1[i] &= ~(0x08);
            }
        } else {
            for (i = 0; i < 10; i++) {
                __digitos_2[i] &= ~(0x10);
            }
        }
    }
}

#endif	/* MAX7219_H */

