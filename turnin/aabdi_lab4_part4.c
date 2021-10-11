/*	Author: aabdi005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, firstState, Unlocked, buttonHash, buttonY, release } state;
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
            if ((PORTB & 0x01) == 0x01) state=lock;
            else if (PINA == 0x00){
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
            state = PINA == 0x02 ? Unlocked : firstState; 
            break;

		case Unlocked:
            state = (PINA == 0x80) ? firstState : Unlocked;
			break;

        
    
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
    PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}