/* 
 * File:   max6675.h
 * Author: Ericson
 *
 * Created on 15 de abril de 2020, 09:22 AM
 */

#ifndef MAX6675_H
#define	MAX6675_H

#define max6675_so          PORTAbits.RA1
#define max6675_so_tris     TRISAbits.TRISA1
#define max6675_so_ansel    ANSELAbits.ANSA1

#define max6675_cs          LATCbits.LATC0
#define max6675_cs_tris     TRISCbits.TRISC0
#define max6675_cs_ansel    ANSELCbits.ANSC0

#define max6675_csk         LATAbits.LATA2
#define max6675_csk_tris    TRISAbits.TRISA2
#define max6675_csk_ansel   ANSELAbits.ANSA2

void max6675_config(void) {
    max6675_csk = 0;
    max6675_csk_ansel = 0;
    max6675_csk_tris = 0;

    max6675_so_ansel = 0;
    max6675_so_tris = 1;

    max6675_cs = 1;
    max6675_cs_ansel = 0;
    max6675_cs_tris = 0;
}

int max6675_read(void) {
    unsigned int c = 0, i = 0, temp = 0;

    max6675_csk = 0;
    max6675_cs = 0;
    for (c = 0; c < 1000; c++);

    for (i = 0; i < 16; i++) {
        max6675_csk = 0;
        for (c = 0; c < 1000; c++);
        if (max6675_so) {
            temp++;
        }
        temp <<= 1;
        max6675_csk = 1;
        for (c = 0; c < 1000; c++);
    }

    for (c = 0; c < 1000; c++);
    max6675_cs = 1;

    if (temp & (0x04)) {
        temp = 0;
    } else {
        temp >>= 3;
        float t = temp;
        t *= 0.25;
        temp = t;
    }

    return temp;
}

#endif	/* MAX6675_H */

