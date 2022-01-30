#include "ping.h"
#include <math.h>
#include "lcd.h"
volatile int time_past = 0;
volatile int time_current = 0;
volatile int edge_detect = 0;
volatile int time = 0;
volatile int overflows = 0;

void ping_init()
{
/////////////GPIO///////////////////////////// (for Input Edge Time mode)
    SYSCTL_RCGCGPIO_R |= 0b000010; //port B

    SYSCTL_RCGCTIMER_R |= 0b001000; //timer 3

    GPIO_PORTB_AFSEL_R |= 0x08; //  port B bit 3 (timer)

    GPIO_PORTB_PCTL_R |= 0x7000; //enable timer

    GPIO_PORTB_DIR_R &= 0xF7; //bit 3 input

    GPIO_PORTB_DEN_R |= 0xFF; // all digital

///////////TIMER EDGE TIME MODE//////////////////////////

    TIMER3_CTL_R &= 0x0000; //disable timer B

    TIMER3_CFG_R |= 0x00000004; //set to IETM

    TIMER3_TBMR_R |= 0x007; //fix to count down mode, capture mode, enable interrupts
    TIMER3_TBMR_R &= ~0x10;

    TIMER3_CTL_R |= 0x0C00; //set event in timer B to Both Edges

    TIMER3_TBILR_R |= 0xFFFF;  //ask TA about this register

    TIMER3_TBPR_R |= 0xFF; //ask TA about this register

    ///////////////////INTERRUPTS///////////////////////////

    TIMER3_IMR_R |= 0x0400; //bit 9 is capture mode interrupt

    NVIC_EN1_R |= 0x10; //interrupt 52 vector 36 for timer 3

    IntRegister(INT_TIMER3B, ping_handler); //change
    IntMasterEnable();
}

void ping_handler()
{
    edge_detect++;
    if (edge_detect == 1) //rising edge
    {
        time_past = time_current;
        time_current = TIMER3_TBR_R;
    }

    else if (edge_detect == 2) //falling edge
    {

        time_past = time_current;
        time_current = TIMER3_TBR_R;
    }
    TIMER3_ICR_R |= 0x400;
}

void send_pulse()
{
    TIMER3_CTL_R &= 0x0C00;
    TIMER3_IMR_R &= 0x0000; //unmask the interrupt
    GPIO_PORTB_AFSEL_R &= 0xF7; //disable AF
    GPIO_PORTB_DIR_R |= 0x08; //bit 3 output
    GPIO_PORTB_DATA_R |= 0x08; //set bit 3 high
    timer_waitMicros(10); //time high = 5 us
    GPIO_PORTB_DATA_R &= 0x00; //set bit 3 low
    GPIO_PORTB_AFSEL_R |= 0x08; //reset bit 3 to alternate function
    GPIO_PORTB_DIR_R &= 0xF7; //reset bit 3 to input
    TIMER3_CTL_R |= 0x0100; //bit 8 is enable bit
    TIMER3_IMR_R |= 0x0400; //mask the interrupt

}

double ping_read()
{
    send_pulse();
   // char str1[80];
    double distance = 0.0;
    while (edge_detect < 2) //get data from pulses
    {
    }
    time = time_past - time_current;
    if (time_current > time_past) //if counter restarts
    {
        overflows++;
        time = (overflows << 24) + time; //shift it 24 bits to the randle (right)
    }
    distance = 0.5 * (double) time * (1.0 / 16000000.0) * 34000.0;
    //sprintf(str1, "Pulse width: %d\nOverflows: %d\nDistance: %.2f\n", time, overflows, distance);
   // lcd_printf(str1); //display info on lcd screen
    edge_detect = 0;
    //time = 0;
    time_past = 0;
    time_current = 0;
    overflows = 0;
    return distance;
}
