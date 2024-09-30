/*
    adcnr.c
    ADC Noise Reduction: 1 of the 3 basic types of low power mode for ATtiny85
*/

#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main (void) {
    // Setup pin 4 as output and set pin 4 high
    DDRB |= (1<<PB4);
    PORTB |= (1<<PB4);
    uint8_t i = 0;

    // Toggle pin 4 (10x). Actual wall time for delay will be approximately 8 secs when using no clock prescale (1)
    // Current draw will vary from 6.7 mA - 8.2 mA
    while (i <= 10) {
        _delay_ms(8000);
        PORTB &= ~(1<<PB4);
        _delay_ms(8000);
        PORTB |= (1<<PB4);
        i++;
    }
    // Pause for approximately 30 secs ... 8.2 mA
    _delay_ms(30000);
    // Set pin 4 low
    PORTB &= ~(1<<PB4);
    // Pause another 30 secs ... 6.7 mA
    _delay_ms(30000);

    // Enable ADC noise reduction low power mode
    // Set the sleep enable bit and the ADC noise reduction sleep mode bit
    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM0);
    // Call the sleep ASM instruction ... approximately 2.6 mA
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    return 0;
}