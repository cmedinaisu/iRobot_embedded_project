/*
 * adc.c
 *
 *  Created on: Oct 9, 2020
 *      Author: Cristofer Medina
 */

#include "adc.h"
#include "timer.h"
#include "lcd.h"
#include "resetSimulation.h"


// initialize and configure the ADC
void acd_init() {
    SYSCTL_RCGCADC_R |= 0b01;
    SYSCTL_RCGCGPIO_R |= 0b00011010;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    GPIO_PORTB_AFSEL_R |= 0b00010000;
    GPIO_PORTB_DEN_R &= 0b111101;
    GPIO_PORTB_DIR_R |= 0b00010000;
    GPIO_PORTB_AMSEL_R = 0b00010000;
    GPIO_PORTB_ADCCTL_R = 0x00;

    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;         //disable SS0 sample sequencer to configure it
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;      //initialize the ADC trigger source as processor
    ADC0_SSMUX0_R |= 0x000A;                   //set 1st sample to use the AIN10 ADC pin
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);    //enable raw interrupt status
    ADC0_SAC_R |= ADC_SAC_AVG_64X;          //enable oversampling to average
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;        //re-enable ADC0 SS0

}

// Function for taking ADC samples
int adc_read(){
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
    ADC0_PSSI_R=ADC_PSSI_SS0;
    while ((ADC0_RIS_R & ADC_RIS_INR0) == 0) {

    }
    ADC0_ISC_R=ADC_ISC_IN0;
    return ADC0_SSFIFO0_R & 0xFFF;
}
