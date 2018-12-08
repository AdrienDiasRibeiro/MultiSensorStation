#include <xc.h>
#include <pic18lf26k83.h>

#pragma config RSTOSC = 0b000 //set 64Mhz internal clocks
#define _XTAL_FREQ 64000000

#include "uart_bluetooth.h"
#include "sensors.h"
#include "manage_interrupt.h"
#include "manage_init.h"

void __interrupt(irq(IRQ_INT0)) INT0_ISR(void){
    manage_int0();
}

void __interrupt(irq(IRQ_U1RX)) U1RXINT1_ISR(void){
    LATCbits.LATC0 = 1; //Pin1 of PORTC high
    char order[]="xxxxxx";
    serial_read(order,6);
    manage_rx_int(order);
    LATCbits.LATC0 = 0; //Pin1 of PORTC low
}

void main(void) {
    general_init();
    interrupt_init();
    init_serial();
    while(1){}
}
