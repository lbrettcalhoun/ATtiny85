/*
    timer0_wake.c
    Implement a simple 1 min delay using Timer0 with overflow and ISR.
    Wake the ATTiny85 after 1 minutes of sleep (1 mins sleep, then wake)

    6.38 mA when on, 0.00 mA when sleeping


    DOES NOT WORK! CANNOT use Timer0 overflow to wake from idle because
    the peripheral clock is NOT running!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
    if (count == 183) {
        count = 0;
        MCUCR &= ~(1<<SE);
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
    // Enable general pin change interrupt
    GIMSK |= (1<<PCIE);
    // Enable PCINT4 interrupt
    PCMSK |= (1<<PCINT4);
    // Go to sleep
    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM1);
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    
    while (1) { 
        ;
    }
 }