/*
    wdt_wake.c
    Wake the ATTiny85 after 1 minutes of sleep (1 mins sleep, then wake)

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
volatile uint8_t count;

ISR (WDT_vect) {

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
    // Enable global interrupts
    sei();
    // Go to sleep
    MCUCR |= (1<<SE);
    MCUCR |= (1<<SM1);  // Idle
    __asm__ __volatile__ ( "sleep" "\n\t" :: );
    
    while (count < 8) { 
        count++;
        __asm__ __volatile__ ( "sleep" "\n\t" :: );
    }
    PORTB |= (1<<PB4);
    return 0;    
 }