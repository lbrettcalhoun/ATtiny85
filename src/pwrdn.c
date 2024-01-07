#define __AVR_ATtiny85__
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);
    uint8_t i = 0;

    while (i <= 10) {
        _delay_ms(16000);
        PORTB &= ~(1<<PB4);
        _delay_ms(16000);
        PORTB |= (1<<PB4);
        i++;
    }
    _delay_ms(64000);
    PORTB &= ~(1<<PB4);
    _delay_ms(64000);

    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM1);
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    return 0;
}