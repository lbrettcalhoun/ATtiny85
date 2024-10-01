/*
    pwrdn.c
    Power Down: 1 of the 3 basic types of low power mode for ATtiny85
    See adcnr.c for comments
*/


#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);
    uint8_t i = 0;

    while (i <= 10) {
        _delay_ms(8000);
        PORTB &= ~(1<<PB4);
        _delay_ms(8000);
        PORTB |= (1<<PB4);
        i++;
    }
    _delay_ms(30000);
    PORTB &= ~(1<<PB4);
    _delay_ms(30000);

    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM1);
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    // 17 uA ... a real power down!
    return 0;
}