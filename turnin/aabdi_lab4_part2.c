/*	Author: aabdi005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States{Start, firstState, increment, decrement, reset} state;


void Tick() {
    switch(state){
        case Start:
            PORTC = 0x07;
            state = firstState;
            break;

        case firstState:
            if(PINA == 0x01){
                if (PORTC < 0x09) PORTC++; 
                state = increment;
            }
            else if(PINA == 0x02) {
                if (PORTC > 0x00) PORTC--; 
                state = decrement;
            }
            else if(PINA == 0x03){
                PORTC = 0x00;
                state = reset;
            }
            break;


        case reset:
           if(PINA == 0x00){
                state = firstState;
            }
            else if(PINA == 0x01){
                if (PORTC < 0x09) PORTC++; 
                state = increment;
            }
            else if(PINA == 0x02) {
                if (PORTC > 0x00) PORTC--; 
                state = decrement;
            }
            else if(PINA == 0x03){
                state = reset;
            }
            break;
        
        
        case increment:
            if(PINA == 0x00){
                state = firstState;
            }
            else if(PINA == 0x01){
                state = increment;
            }
            else if(PINA == 0x02) {
                if (PORTC > 0x00) PORTC--;
                state = decrement;
            }
            else if(PINA == 0x03){
                PORTC = 0x00;
                state = reset;
            }
            break;

        case decrement:
            if(PINA == 0x00){
                state = firstState;
            }
            else if(PINA == 0x01){
                if (PORTC < 0x09) PORTC++; 
                state = increment;
            }
            else if(PINA == 0x02) {
                state = decrement;
            }
            else if(PINA == 0x03){
                PORTC = 0x00;
                state = reset;
            }
            break;
        default:
            break;
    }
 
}
        


int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x07;
    
    while (1) {
        Tick();
        
    }
    return 1;
}
