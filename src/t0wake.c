/*
    timer0_wake.c
    Implement a simple 1 min idle sleep using Timer0 with overflow and ISR.
    Wake the ATTiny85 after 1 minutes of sleep (1 mins sleep, then wake)

    Note: Only works with IDLE sleep ... will not work with ADC Noise
    Reduction or Power down

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
volatile uint16_t count;

ISR (TIMER0_OVF_vect) {
    count++;
}

int main (void) {
    // Setup PB4
    DDRB |= (1<<PB4);
    PORTB &= ~(1<<PB4);
    // Enable Timer0 and set it to prescalar 1024
    TCCR0B |= (1<<CS02) | (1<<CS00);
    // Clear the Timer0 overflow flag
    TIFR |= (1<<TOV0);
    // Enable global interrupts
    sei();
    // Enable the Timer0 overflow interrupt
    TIMSK |= (1<<TOIE0);
    // Disable Analog Comparator for even more power saving in idle mode
    ACSR &= ~(1<<ACIE);
    ACSR |= (1<<ACD);
    // Go to sleep (just idle ... not ADCNR or PDWN)
    MCUCR |= (1<<SE);
    MCUCR &= ~(1<<SM1) & ~(1<<SM0);
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    
    while (1) { 
        if (count == 1831) {
            count = 0;
            PORTB |= (1<<PB4);
            return 0;
        }
        else {
            __asm__ __volatile__ ( "sleep" "\n\t" :: );
        }
    }
 }