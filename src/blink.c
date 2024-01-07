#define __AVR_ATtiny85__
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);
    uint8_t i = 0;

    while (i <= 30) {
        _delay_ms(16000);
        PORTB &= ~(1<<PB4);
        _delay_ms(16000);
        PORTB |= (1<<PB4);
        i++;
    }

    return 0;
}