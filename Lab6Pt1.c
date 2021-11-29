#include <msp430g2553.h>
volatile long temp, tempRaw; // set expressions
void ConfigureAdc_temp();// variable name for function temp
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    _delay_cycles(5); // delay
    while(1){

        ConfigureAdc_temp(); // calls function for temp
    }
}

void ConfigureAdc_temp(){
     ADC10CTL1 = INCH_10 + ADC10DIV_0 + CONSEQ_2;// select channel 10 adn set clk to SMCLCK
     ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON ;//Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
     ADC10CTL0 |= ENC + ADC10SC +MSC;// disable conversion
     tempRaw = ADC10MEM;                    // read the converted data into a variable
     temp = (((tempRaw-673)*423)/1024); //converts to degree celsius
}
