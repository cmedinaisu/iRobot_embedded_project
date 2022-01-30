/*
 * adc.c
 *
 *  Created on: Oct 23, 2020
 *      Author: Cristofer Medina
 */

#include "servo.h"
#include "timer.h"
#include "lcd.h"
#include "resetSimulation.h"


// initialize and configure the TIMER
void servo_init() {
    SYSCTL_RCGCGPIO_R |= 0x2;
    SYSCTL_RCGCTIMER_R |= 0x2;
    GPIO_PORTB_AFSEL_R |= 0b00100000;
    GPIO_PORTB_PCTL_R |= 0x00700000;
    GPIO_PORTB_DIR_R |= 0b00100000;
    GPIO_PORTB_DEN_R |= 0b00100000;

    TIMER1_CTL_R &= 0x0;                            //disable timer to config
    TIMER1_TBMR_R |= 0xA;                       //periodic and PWM enable
    TIMER1_CFG_R |= 0x4;                            //set size of timer to 16
    TIMER1_TBILR_R = 320000 & 0xFFFF;      //lower 16 bits of the interval
    TIMER1_TBPR_R = 320000 >> 16;          //set the upper 8 bits of the interval
//    TIMER1_TBMATCHR_R = (320000 - 19500) & 0xFFFF;        //Move servo to middle
//    TIMER1_TBPMR_R = (320000 - 19500) >> 16;
    TIMER1_CTL_R |= 0x100;                      //enable timer
}

// Move the servo motor with given degree
int servo_move(int degrees){
    int pulse_width = 9000 + (128 * degrees);
    TIMER1_TBMATCHR_R = (320000 - pulse_width) & 0xFFFF;
    TIMER1_TBPMR_R = (320000 - pulse_width) >> 16;
    timer_waitMillis(50);
    return 0;
}
