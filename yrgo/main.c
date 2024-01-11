/*  Inlämningsuppgift 1 VG-nivå
    Av: Pär Westerlund          
    Datum: 2023-10-21           */

#include <avr/io.h>
#include "p1/P1.h"
#include <time.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    setup_p1();
    led(0, false);
    
    /*  VARIABLER FÖRKLARING
        i,j,k = loop variabler
        intensity = ljusstyrkan
        color = färg på aktiv LED
        led_time = proportionell mot tiden LED är tänd
        pot1 & pot2 = POT värden    */

    uint8_t i, j, k, intensity, color = 3;
    uint16_t led_time, pot1, pot2;

    while(1) {
        
        /* Bestäm nästa LED som ska tändas */
        if (!sw2()) {
            switch(color) { 
                case 1:
                    color++;
                    break;
                case 2:
                    color++;
                    break;
                case 3:
                    color = 1;
                    break;
                default:
                    break;
            }           
        } else {
            switch(color) {
                case 1:
                    color = 3;
                    break;
                case 2:
                    color--;
                    break;
                case 3:
                    color--;
                    break;
                default:
                    break;
            }
        }           

        pot1 = read_pot1();
        led_time = pot1/10;        
        pot2 = read_pot2();   
        intensity = pot2/20;
        led(0, false);
        
        /* Tänder LED önskad tid */
        for (i = 0; i < led_time; i++) {
            
            /* Dimmer loop */
            for (j = 0; j < 51; j++) {
                for (k = 0; k < intensity; k++) { 
                    led(color, true);
                }
                for (k= 51; k > intensity; k--) { 
                    led(color, false);
                }
            }

            /* Frys LED */
            if (sw1() && i != 0) {
                i--;
            }

            /* Släck LEDar */
            while (sw3()) {
                led(0, false);
            }
        }        
    }
}