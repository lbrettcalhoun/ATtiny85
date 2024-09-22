/*
    timer0_adcnr.c
    Implement a simple 1 min delay using Timer0 with overflow and ISR.
    Put the ATTiny85 to sleep for 1 minutes (1 mins on, then sleep)

    6.38 mA when on, 2.12 mA when sleeping

*/
/*
    8Mhz clock, Timer0 prescalar 1024, 8 bit Timer0 (256 values)
    TOV0 freq = 8,000,000/(1024*256) = 30.517578125 hz
    TOV0 time = 1/30.517578125*1,000 = 32.768 ms

*/

#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
uint16_t count = 0;

ISR (TIMER0_OVF_vect) {
    count++;
    if (count == 1831) {
        __asm__ __volatile__ ( "sleep" "\n\t" :: );
    }
}

int main (void) {
    // Set the data direction register for pin 4 to be an output pin
    DDRB |= (1<<PB4);
    // Set pin 4 to low
    PORTB &= ~(1<<PB4);
    // Enable Timer0 and set it to prescalar 1024
    TCCR0B |= (1<<CS02) | (1<<CS00);
    // Clear the Timer0 overflow flag
    TIFR |= (1<<TOV0);
    // Enable global interrupts
    sei();
    // Enable the Timer0 overflow interrupt
    TIMSK |= (1<<TOIE0);
    // Enable sleep
    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM0);

    while (1) { 
        ;
    }
 }