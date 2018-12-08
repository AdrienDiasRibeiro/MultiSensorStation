#include <xc.h>
#include <pic18lf26k83.h>

#include "uart_bluetooth.h"

void init_serial (void){
    //Init UART1 serial port 1
    U1CON1bits.ON = 0; //Disable uart port
    U1CON0bits.MODE = 0x00; //Asynchronous 8-bit UART mode
    // Desired baud rate = Fosc / [16*(UxBRG + 1)] => For 1 Mbps and Fosc = 64Mhz, U1BRG = 3
    U1BRGL = 34; //U1BRG low 8bits
    U1BRGH = 0x00; //U1BRG high 8bits  115200baud
    U1CON0bits.U1BRGS = 0; //Default multiplier baudrate
    //Init TX 
    U1CON0bits.TXEN = 1; //Enable TX 
    RB4PPS = 0b00010011; //RB4 <- TX, RxyPPS register (page 267)
    //Init RX
    U1CON0bits.RXEN = 1; //Enable RX
    U1RXPPS = 0b00001101; //RB5 <- RX
    ANSELBbits.ANSELB5 = 0; //Set RB5/RX to numeric input
    //
    U1CON1bits.ON = 1; //Enable uart port
}

void serial_print(unsigned char *Pline,int nl)
{
int x = 0;
for ( x = 0; Pline[x]!=0x00 ; x++)
{
while (U1TXMTIF == 0) {}
U1TXB = Pline[x];
}
while (U1TXMTIF == 0 ) {}
if(nl == 1) U1TXB = 0x0D ; // new line, carriage return
if(nl == 2) U1TXB = 255 ; // new line, carriage return
while (U1TXMTIF == 0 ) {}
}

void serial_read(char *order, int nbcar)
{
    int i;
    for (i=0; i<nbcar; i++){
        while(U1FIFObits.U1RXBE){} // attend s'il n'y a rien à lire
        order[i] = U1RXB;        
    }
}
