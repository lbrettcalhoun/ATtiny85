#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);

    while (1) {
        _delay_ms(1000);
        PORTB &= ~(1<<PB4);
        _delay_ms(1000);
        PORTB |= (1<<PB4);
    }
    return 0;
}