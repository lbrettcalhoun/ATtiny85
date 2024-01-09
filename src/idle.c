/*
    idle.c
    Idle: 1 of the 3 basic types of low power mode for ATtiny85
    See adcnr.c for comments
*/


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
    MCUCR &= ~(1<<SM1) & ~(1<<SM0);

    _delay_ms(64000);
    MCUCR |= (1<<SE);
//    Don't really need to clear these bits ... they are clear by default
//    MCUCR &= ~(1<<SM1) | ~(1<<SM0);
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    return 0;
}