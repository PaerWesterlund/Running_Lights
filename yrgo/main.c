/*  Inl�mningsuppgift 1 VG-niv�
    Av: P�r Westerlund          
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
    
    /*  VARIABLER F�RKLARING
        i,j,k = loop variabler
        intensity = ljusstyrkan
        color = f�rg p� aktiv LED
        led_time = proportionell mot tiden LED �r t�nd
        pot1 & pot2 = POT v�rden    */

    uint8_t i, j, k, intensity, color = 3;
    uint16_t led_time, pot1, pot2;

    while(1) {
        
        /* Best�m n�sta LED som ska t�ndas */
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
        
        /* T�nder LED �nskad tid */
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

            /* Sl�ck LEDar */
            while (sw3()) {
                led(0, false);
            }
        }        
    }
}