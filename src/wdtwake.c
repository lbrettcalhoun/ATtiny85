/*
    wdt_wake.c
    Wake the ATTiny85 after 10 minutes of sleep (10 mins sleep, then wake, 1 min on, repeat)

    6.38 mA when on, 0.00 mA when sleeping

*/
/*

WDT: 128 kHz, 8 sec overflow: WDP3 = 1, WDP0 = 1

*/

#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t wdtcount, idle = 0;
volatile uint16_t t0count = 0;

ISR (WDT_vect) {
    wdtcount++;
}

ISR (TIMER0_OVF_vect) {
    t0count++;
}

int main (void) {
    // Set the data direction register for pin 4 to be an output pin
    DDRB |= (1<<PB4);
    // Set pin 4 to low
    PORTB &= ~(1<<PB4);
    // Set WDT to interrupt instead of reset and prescalar to 8 secs
    MCUCR &= ~(1<<WDRF);
    WDTCR |= (1<<WDCE) | (1<<WDE);
    WDTCR &= ~(1<<WDE);
    WDTCR |= (1<<WDIE);
    WDTCR |= (1<<WDP3) | (1<<WDP0);
    // Enable Timer0 and set it to prescalar 1024
    TCCR0B |= (1<<CS02) | (1<<CS00);
    TIFR |= (1<<TOV0);
    TIMSK |= (1<<TOIE0);
    // Enable global interrupts
    sei();
    // Go to sleep
    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM1);  // Idle
    idle = 1;
    __asm__ __volatile__ ( "sleep" "\n\t" :: );

    while (1) {
        if (idle) {
            if (wdtcount == 70) {
                wdtcount = 0;
                PORTB |= (1<<PB4);
                t0count = 0;
                idle = 0;
            }
            else {
                PORTB &= ~(1<<PB4);
                __asm__ __volatile__ ( "sleep" "\n\t" :: );
            }
        }
        else {
            if (t0count == 1831) {
                t0count = 0;
                PORTB &= ~(1<<PB4);
                idle = 1;
                wdtcount = 0;
                __asm__ __volatile__ ( "sleep" "\n\t" :: );
            }
            else {
                PORTB |= (1<<PB4);
            }
        }
    }
 }  