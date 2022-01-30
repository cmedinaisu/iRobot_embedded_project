

/**
 * main.c
 */

#include "servo.h"
#include "timer.h"
#include "lcd.h"
#include "adc.h"
#include "resetSimulation.h"
#include "math.h"
#include "uart.h"
#include "stdio.h"
#include "stdlib.h"
#include "movement.h"
#include "open_interface.h"
#include "functions.h"
#include "ping.h"




int main(void)
{
    timer_init();
    //resetSimulationBoard();
    lcd_init();
    acd_init();
    uart_init();
    servo_init();
    ping_init();

    char input;
    char output[20];
    int direction = 1;
    oi_t *sensor = oi_alloc();

    oi_init(sensor);





    while(1){
        input = uart_receive();


        timer_waitMillis(10);

        uart_sendChar('\n');
        uart_sendChar('\r');



        if(input == 'w'){

            move_forward(sensor, 20.0);

        }

        else if(input == 'a'){

            turn_counter_clockwise(sensor, 45);
            direction = get_direction(direction, -2);
        }

        else if (input == 'z')
        {

            turn_counter_clockwise(sensor, 22.5);
            direction = get_direction(direction, -1);
        }
        else if (input == 'x')
        {

            turn_clockwise(sensor, 22.5);
            direction = get_direction(direction, 1);
        }
        else if (input == 'd'){

            turn_clockwise(sensor, 45);
            direction = get_direction(direction, 2);
        }

        else if(input == 's'){
            move_backward(sensor, 20.0);

            sprintf(output, "moved backward");
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');
        }

        else if(input == 'e'){
            scan();
        }
    }

	return 0;
}
