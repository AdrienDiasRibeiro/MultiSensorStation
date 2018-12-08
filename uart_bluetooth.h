#ifndef UART_BLUETOOTH_INCLUDED
#define	UART_BLUETOOTH_INCLUDED

#include <xc.h>  

void init_serial (void);
void serial_print(unsigned char *Pline,int nl);
void serial_read(char *order, int nbcar);

#endif