#ifndef SENSORS_INCLUDED
#define	SENSORS_INCLUDED

#include <xc.h>  

char read_sens_value (char adresse_port); //read the value 8bits of an ADC
char check_cr (char value); //Check if value == 13 and correct
void detect_sensors (void); //Check if sensors are connected
#endif