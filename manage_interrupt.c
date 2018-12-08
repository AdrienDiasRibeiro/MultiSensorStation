#include <xc.h>
#include <pic18lf26k83.h>
#define _XTAL_FREQ 64000000

#include "manage_interrupt.h"
#include "sensors.h"
#include "uart_bluetooth.h"
#include <string.h>

char light_sensor = 0b00010100; //RC4
char temp_sensor = 0b00010101; //RC3
char PIR_sensor = 0b00010110; //RC6
char sound_sensor =0b00010111; //RC7

void manage_rx_int (char *order)
{
    if (strcmp(order, "RLI001") == 0){ // strcmp function from string.h
        char val[2];
        val[0] = read_sens_value(light_sensor); //read RC4 port of light ADC
        val[1] = 0;
        serial_print(val,1);
    }
    else if (strcmp(order, "RTP001") == 0){ // strcmp function from string.h
        char val[2];
        val[0] = read_sens_value(temp_sensor); //read RC3 port of light ADC
        val[1] = 0;
        serial_print(val,1);
    }
    else if (strcmp(order, "RPIR01") == 0){ // strcmp function from string.h
        char val[2];
        val[0] = read_sens_value(PIR_sensor); //read RC3 port of light ADC
        val[1] = 0;
        serial_print(val,1);
    }
    else if (strcmp(order, "RS0001") == 0){ // strcmp function from string.h
        char val[2];
        val[0] = read_sens_value(sound_sensor); //read RC3 port of light ADC
        val[1] = 0;
        serial_print(val,1);
    }
    else if (strcmp(order, "NAME00") == 0){ // strcmp function from string.h
        serial_print("SmateV1.0",1);
    }
    else if (strcmp(order, "DSENS0") == 0){ // strcmp function from string.h
        detect_sensors();
    }
}

void manage_int0(void)
{
    PIR1bits.INT0IF = 0; // Clear the interrupt flag
    LATCbits.LATC0 = 1; //Pin1 of PORTC high
    char word[] = "HEY";
    serial_print(word,1); //ecrire sur le port serie, 1 rajoute un carriage return
    __delay_ms(100); 
    LATCbits.LATC0 = 0; //Pin1 of PORTC low
}

