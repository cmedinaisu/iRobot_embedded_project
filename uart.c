#include "uart.h"




volatile char uart_data;
volatile int flag = 0;

void uart_init(void){
    SYSCTL_RCGCGPIO_R |= 0b000010;
    SYSCTL_RCGCUART_R |= 0b00000010;
    GPIO_PORTB_AFSEL_R |= 0x03;
    GPIO_PORTB_PCTL_R &= 0x11;
    GPIO_PORTB_PCTL_R |= 0x11;
    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_DIR_R &= 0x01;
    GPIO_PORTB_DIR_R |= 0x01;

    UART1_CTL_R &= 0xFE; // setting UARTEN to 0 but preserve else
    UART1_IBRD_R = 8; // baud for 115,200
    UART1_FBRD_R = 44;
    UART1_LCRH_R = 0x60;
    UART1_CC_R = 0x0;
    UART1_CTL_R = 0x0301;

}

void uart_sendChar(char data){
    while(UART1_FR_R & 0x20)
    {
    }
    UART1_DR_R = data;
}

char uart_receive(){
    char data = 0;
    while(UART1_FR_R & 0x10)
    {
    }
    data = (UART1_DR_R & 0xFF);
    return data;
}

void uart_sendStr(const char *data){
    while(*data != '\0')
        {
            uart_sendChar(*data);
            data++;
        }
}

void uart_interrupt_init()
{
    UART1_IM_R |= 0x10;
    NVIC_EN0_R |= 0x40;
    IntRegister(INT_UART1,handler);
}

void handler()
{
     //char input;
    if(UART1_IM_R & 0x10)
    {

        uart_data  = UART1_DR_R & 0xFF;
        //lcd_putc(uart_data);
        UART1_ICR_R |= 0x10;
        flag = 1;

    }
}

