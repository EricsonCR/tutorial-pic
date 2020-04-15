/* 
 * File:   oscillator.h
 * Author: Ericson
 *
 * Created on 14 de abril de 2020, 04:41 PM
 */

#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

#define OSCILLATOR_32MHZ    5
#define OSCILLATOR_16MHZ    4
#define OSCILLATOR_8MHZ     3
#define OSCILLATOR_4MHZ     2
#define OSCILLATOR_2MHZ     1
#define OSCILLATOR_1MHZ     0

void oscillator_config(unsigned int freq);

void oscillator_config(unsigned int freq) {

    switch (freq) {
        case OSCILLATOR_32MHZ:
            OSCCONbits.IRCF = 0b1110;
            OSCCONbits.SCS = 0b00;
            OSCCONbits.SPLLEN = 1;
            break;
        case OSCILLATOR_16MHZ:
            OSCCONbits.IRCF = 0b1111;
            OSCCONbits.SCS = 0b10;
            OSCCONbits.SPLLEN = 0;
            break;
        case OSCILLATOR_8MHZ:
            OSCCONbits.IRCF = 0b1110;
            OSCCONbits.SCS = 0b10;
            OSCCONbits.SPLLEN = 0;
            break;
        case OSCILLATOR_4MHZ:
            OSCCONbits.IRCF = 0b1101;
            OSCCONbits.SCS = 0b10;
            OSCCONbits.SPLLEN = 0;
            break;
        case OSCILLATOR_2MHZ:
            OSCCONbits.IRCF = 0b1100;
            OSCCONbits.SCS = 0b10;
            OSCCONbits.SPLLEN = 0;
            break;
        case OSCILLATOR_1MHZ:
            OSCCONbits.IRCF = 0b1011;
            OSCCONbits.SCS = 0b10;
            OSCCONbits.SPLLEN = 0;
            break;
    }
}

#endif	/* OSCILLATOR_H */

