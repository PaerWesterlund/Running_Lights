/*
 * bcd.c
 *
 * Created: 2023-08-30 11:59:29
 *  Author: mardea0831
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "P1.h"

void set_number(uint8_t number) {


    /*Removes any number that cant be displayed*/
    number &= 0b00001111;
    PORTD &= 0b11110000;
    PORTD |= number;

}