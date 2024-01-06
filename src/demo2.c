#define __AVR_ATtiny85__
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);

    while (1) {
        _delay_ms(500);
        PORTB &= ~(1<<PB4);
        _delay_ms(500);
        PORTB |= (1<<PB4);
    }
    return 0;
}