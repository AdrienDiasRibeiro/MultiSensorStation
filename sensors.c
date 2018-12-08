#include <xc.h>
#include <pic18lf26k83.h>
#define _XTAL_FREQ 64000000

#include "sensors.h"
#include "uart_bluetooth.h"

char light_sensor = 0b00010100; //RC4
char temp_sensor = 0b00010101; //RC5
char PIR_sensor = 0b00010110; //RC6
char sound_sensor =0b00010111; //RC7

char check_cr (char value)//To avoid send a carriage return
{
    if (value == 13)
        {
            value = 12;
        }
    return value;
}

char read_sens_value (char address_port) //Read the sensor value of an ADC 
{
    char value;
    ADPCH = address_port;
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO); //Wait for conversion done
    value = check_cr(ADRESH);
    return value;
}

void detect_sensors (void)
{
    char sensor_byte = 0b00000000;
    char sensor_address[4];
    sensor_address[0] = light_sensor, sensor_address[1] = temp_sensor;
    sensor_address[2] = PIR_sensor, sensor_address[3] = sound_sensor;
    char mask[4] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};
    for (int i=0; i<4; i++)
    {
        ADPCH = sensor_address[i];
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO); //Wait for conversion done
        if (check_cr(ADRESH) > 40)
        {
            sensor_byte = sensor_byte | mask[i];
        }
    }
    char val[2] = {0, 0};
    val[0] = sensor_byte;
    serial_print(val,1);
}