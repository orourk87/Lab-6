/// MSP430 Code Composer Code
#include <msp430g2553.h>
volatile long temp, tempRaw, light;
void ConfigureAdc_temp();
void ConfigureAdc_Photo();
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    _delay_cycles(5);
    while(1){

        ConfigureAdc_temp();
        ConfigureAdc_Photo();
    }
}

void ConfigureAdc_temp(){
     ADC10CTL1 = INCH_10 + ADC10DIV_0 + CONSEQ_2;
     ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON ;//Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
     ADC10CTL0 |= ENC + ADC10SC +MSC;
     tempRaw = ADC10MEM;                    // read the converted data into a variable
     temp = (((tempRaw-673)*423)/1024); //converts to degree celsius
}
 void ConfigureAdc_Photo(){
     ADC10CTL1 = INCH_6 + ADC10DIV_0 + CONSEQ_3;
     ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON ;//Vref+, Vss, 64 ATD clocks per sample, internal references, turn ADCON
     ADC10CTL0 |= ENC + ADC10SC +MSC;
     light = ADC10MEM;
 }
