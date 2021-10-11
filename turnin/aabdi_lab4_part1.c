/*	Author: 
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{Start, offRelease, onPress, onRelease, offPress} state;



void Tick() {
    switch(state){
        case Start:
        state = offRelease;
        break;

        case onPress:
            state = (PINA & 0x01) == 0x01 ? onPress : onRelease;
            break;

        case onRelease:
            state = (PINA & 0x01) == 0x01 ? offPress : onRelease;
            break;
        case offPress:
            state = (PINA & 0x01) == 0x01 ? offPress : offRelease;
            break;
        case offRelease:
            state = (PINA & 0x01) == 0x01 ? onPress : offRelease;
            break;
        default:
            state = Start;
            break;
    }
    
        switch(state){
            case Start:
            PORTB = 0x01;
            break;

        case onPress:
            PORTB = 0x02;
            break;
            
        case onRelease:
            PORTB = 0x02;
            break;
            
        case offPress:
            PORTB = 0x01;
            break;
        
        case offRelease:
            PORTB = 0x01;
            break;
        default:
            PORTB = 0x01;
            break;
            }
    }


int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    while (1) {
        Tick();
    }
    return 1;
}
