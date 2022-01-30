

#include "movement.h"






void move_forward(oi_t*sensor, double centimeters){

     double sum = 0.0;
    oi_setWheels(500, 500); // move forward; full speed
    char output[20];


    while (sum < centimeters * 10)
    {

        if ((sensor->bumpRight) || (sensor->bumpLeft)) {  //check for short object
            move_backward(sensor, (sum / 10.0));

            sprintf(output, "bumped");
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');

            sprintf(output, "%.2f", sum / 10.0);
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');

            break;

        }
        if ((sensor->cliffFrontLeft) || (sensor->cliffLeft) || (sensor->cliffRight) || (sensor->cliffFrontRight)){

            move_backward(sensor, (sum / 10.0));

            sprintf(output, "cliff");
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');

            sprintf(output, "%.2f", sum / 10.0);
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');

            break;
        }
        if ((sensor->cliffFrontLeftSignal != 1000) || (sensor->cliffLeftSignal !=  1000) || (sensor->cliffRightSignal !=  1000) || (sensor->cliffFrontRightSignal !=  1000)){

            move_backward(sensor, (sum / 10.0));


            sprintf(output, "wall");
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');

            sprintf(output, "%.2f", sum / 10.0);
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');

            break;
        }
        oi_update(sensor);
        sum += sensor->distance;
    }



    oi_setWheels(0, 0); // stop


     if (sum >= centimeters * 10){

         sprintf(output, "moved forward");
         uart_sendStr(output);

         uart_sendChar('\n');
         uart_sendChar('\r');
     }



}

void move_backward(oi_t*sensor, double centimeters){

     double sum = 0;
     oi_setWheels(-500, -500); // move forward; full speed

     while (sum > -centimeters * 10) {
         oi_update(sensor);
         sum += sensor->distance;

     }

     oi_setWheels(0, 0); // stop




}

void turn_clockwise(oi_t*sensor, double degrees){

    double sum = 0;
    oi_setWheels(150,-150); // turn clockwise, full s19peed

    while(sum < degrees*.94) {
        oi_update(sensor);
        sum+= sensor->angle; //
    }

    oi_setWheels(0, 0); // stop


}

void turn_counter_clockwise(oi_t*sensor, double degrees){

    double sum = 0;
    oi_setWheels(-150,150); // turn counter clockwise, full speed

    while(sum < degrees*.94) {
        oi_update(sensor);
        sum-= sensor->angle; //
    }

    oi_setWheels(0, 0); // stop


}



