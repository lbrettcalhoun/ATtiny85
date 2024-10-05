/*
    eeprom_write.c
    Write a string into EEPROM
*/

#ifndef __AVR_ATtiny85__
  #define __AVR_ATtiny85__
#endif
#include <avr/io.h>
#include <avr/interrupt.h>

void EEPROM_write(unsigned char ucAddress, unsigned char ucData)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE))
        ;
    /* Set Programming mode */
    EECR &= ~(1<<EEPM1) & ~(1<<EEPM0);
    /* Set up address and data registers */
    EEAR = ucAddress;
    EEDR = ucData;
    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);
    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
}

int main (void) {
    // Set the data direction register for pin 4 to be an output pin
    DDRB |= (1<<PB4);
    // Set pin 4 to low
    PORTB &= ~(1<<PB4);
    // Disable global interrupts
    cli();
    EEPROM_write(0,65);
    EEPROM_write(1,66);
    EEPROM_write(2,67);
    EEPROM_write(3,68);
    // Set pin 4 to high
    PORTB |= (1<<PB4);
    return 0;
 }  