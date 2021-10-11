/*	Author: aabdi005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, firstState, Unlocked, buttonHash, buttonY, release, lock} state;
void Tick() {
	switch(state){
		case Start:
			state = firstState;
			break;
		case firstState:
			if(PINA == 0x04) state = buttonHash;

			else state = firstState;
			break;

        //Unlock door using code
		case buttonHash:
            if (PINA == 0x00){
				state = release;
			}
            else if(PINA == 0x04){
				state = buttonHash;
			}
			else{
				state = firstState;
			}
            break;
           
		case release:
			if(PINA == 0x00){
				state = release;
			}
            else if(PINA == 0x02){
				state = buttonY;
			}
            else{
				state = firstState;
			}
			break; 
		case buttonY:
            if(PORTB == 0x01) {
                state = lock;
                
            }
            else if(PINA == 0x02){
                state = Unlocked;
            }
            else {
                state = firstState;
            }
            break;

		case Unlocked:
            if(PINA == 0x80) {
                state = firstState;
            }
            else if(PINA == 0x04){
                state = buttonHash;
            }
			break;
        case lock:
            if (PINA == 0x04) {
                state = buttonHash;
            }
            else {
                state = lock;
            }
        
		 default:
			state = Start;
			break;
	}

	switch(state){
		case Start:
			PORTB = 0x00;
			break;
		case firstState:
			PORTB = 0x00;
			break;
		case Unlocked:
            PORTB = 0x01;
			break;
        case lock:
            PORTB = 0x00;
            break;
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

    PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}