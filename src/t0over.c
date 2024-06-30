/*
    timer0_overflow.c
    Implement a simple 10 second delay using Timer0 with overflow and ISR.
    Yes, you could do this with avr-libc's _delay_ms but we are going to do it the hard way.
    Use PINB4 (pin 3) to blink LED at 5 second interval.
*/
/*
    Option 1:
    8Mhz clock, Timer0 prescaler 1, 8 bit Timer0 (256 values)
    TOV0 freq = 8,000,000/256 = 31.250 Khz
    TOV0 time = 1/31250*1,000,000 = 32 us

    Option 2:
    8Mhz clock, Timer0 prescalar 1024, 8 bit Timer0 (256 values)
    TOV0 freq = 8,000,000/(1024*256) = 30.517578125 hz
    TOV0 time = 1/30.517578125*1,000 = 32.768 ms

    Option 3:
    1Mhz clock, Timer0 prescalar 1024, 8 bit Timer0 (256 values)
    TOV0 freq = 1,000,000/(1024*256) = 3.814697265625 hz
    TOV0 time = 1/3.814697265625*1,000 = 262.144 ms

*/

#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
uint16_t count = 0;

ISR (TIMER0_OVF_vect) {
    count++;

    // Option 2: 10 mins = 18310 Timer0 overflows
    if (count == 18310) {
        // Toggle pin 4
        PORTB ^= (1<<PB4);
        // Start it all over
        count = 0;        
    }
}

int main (void) {
    // Set the data direction register for pin 4 to be an output pin
    DDRB |= (1<<PB4);
    // Use bit shift and logical OR to set pin 4 high
    PORTB |= (1<<PB4);
    // Option 2
    // Enable Timer0 and set it to prescalar 1024
    TCCR0B |= (1<<CS02) | (1<<CS00);
    // Clear the Timer0 overflow flag
    TIFR |= (1<<TOV0);
    // Enable global interrupts
    sei();
    // Enable the Timer0 overflow interrupt
    TIMSK |= (1<<TOIE0);
    // Infinite loop
    while (1) { 
        ;
    }
 }