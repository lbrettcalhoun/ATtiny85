/*
    blink.c
    Blink pin 4
*/


#define __AVR_ATtiny85__
#include <avr/io.h>
#include <util/delay.h>

int main (void) {
    // Set the data direction register for pin 4 to be an output pin
    DDRB |= (1<<PB4);
    // Use bit shift and logical OR to set pin 4 high
    PORTB |= (1<<PB4);
    uint8_t i = 0;
    // Delay will depend on clock prescale and division. About 8 secs if using no prescale and division of 1.
    while (i <= 30) {
        _delay_ms(16000);
        // Use bit shift, logical AND, and complement to set pin 4 low (clear bit)
        PORTB &= ~(1<<PB4);
        _delay_ms(16000);
        // And set pin 4 back to high
        PORTB |= (1<<PB4);
        i++;
    }

    return 0;
}