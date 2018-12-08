#include <xc.h>
#include <pic18lf26k83.h>

#include "manage_init.h"

void general_init (void)
{
    // define UART pin
    TRISBbits.TRISB4 = 0 ; //Set RB4/TX to output
    TRISBbits.TRISB5 = 1 ; //Set RB5/RX to input
    // define led pin
    TRISCbits.TRISC0 = 0; //Set led C0 output
    LATCbits.LATC0 = 0; //Set led C0 low
    // define interrupt INT0 input pin
    TRISBbits.TRISB0 = 1; //set RB0 as Input
    ANSELBbits.ANSELB0 = 0; //Set RB0 to numeric input
    //define ADC pin
    TRISCbits.TRISC4 = 1; //RC4 ADC input
    ANSELCbits.ANSELC4 = 1; //RC4 analog input
    TRISCbits.TRISC5 = 1; //RC5 ADC input
    ANSELCbits.ANSELC5 = 1; //RC5 analog input
    TRISCbits.TRISC6 = 1; //RC6 ADC input
    ANSELCbits.ANSELC6 = 1; //RC6 analog input
    TRISCbits.TRISC7 = 1; //RC7 ADC input
    ANSELCbits.ANSELC7 = 1; //RC7 analog input
    // Vdd comme ref pour l'ADC (Vdd = 3.3V => q = 3.3/(2^12)-1) = 0.806 mV)
    ADCON0bits.FM = 0; //choix de l'ordre MSB, LSB
    ADCON0bits.CS = 1; //FRC clock
    ADCON0bits.ON = 1; // Set ADC on
}

void interrupt_init (void){
    INTCON0bits.IPEN = 0;                 // Disable interrupt priority
    INTCON0bits.GIE = 1;                  // Enable all interrupts
    PIE1bits.INT0IE = 1;                  // Enable INT0 interrupt
    PIE3bits.U1RXIE = 1;                  // Enable UART1 Rx interrupt

    U1ERRIEbits.FERIE = 0; //Assurer le fonctionnement interruption Uart
    U1ERRIEbits.PERIE = 0; //Assurer le fonctionnement interruption Uart
}
