#include "functions.h"



struct objects {

    int objNum;
    double Adistance;
    double Pdistance;
    int angle;
    int Rwidth;
    double Lwidth;

};



void scan(){

    struct objects object[15];
    object[0].objNum = 0;
    int degreesF = 45;
    double y;
    double distance = 0;
    double distanceP = 0;
    int current_object = object[0].objNum;
    int counter = 1;
    char output[20];


    sprintf(output, "scanning");
    uart_sendStr(output);


    while (degreesF <= 135){



            servo_move(degreesF);
            timer_waitMillis(10);
            y = adc_read() + 0.0;

            distanceP = distance;

            distance = 161915.0 * (1/(pow(y, 1.2)));

            if((distance < 300) && (distanceP < 300)){

                if(distance < distanceP){

                    object[current_object].Adistance = ping_read();
                    if((object[current_object].Adistance > distance + 5) || (object[current_object].Adistance < distance - 5)){
                        object[current_object].Adistance = distance;
                    }
                    object[current_object].angle = degreesF;
                }

                object[current_object].Rwidth += 1;

            }
            else if(distance < 300){

                current_object++;
                object[0].objNum++;
                object[current_object].objNum = current_object;
                object[current_object].angle = degreesF;
                object[current_object].Rwidth = 1;
                object[current_object].Adistance = ping_read();

                if((object[current_object].Adistance > distance + 5) || (object[current_object].Adistance < distance - 5)){
                    object[current_object].Adistance = distance;
                }

            }

            if (degreesF % 20 == 0){
                uart_sendChar('.');
            }

            degreesF += 1;
        }

        uart_sendChar('\n');
        uart_sendChar('\r');



        while(counter <= current_object){
            sprintf(output, "%d", object[counter].objNum);
            uart_sendStr(output);

            uart_sendChar('\t');
            uart_sendChar('\t');

            sprintf(output, "%d", object[counter].angle);
            uart_sendStr(output);

            uart_sendChar('\t');
            uart_sendChar('\t');

            sprintf(output, "%.2f", object[counter].Adistance);
            uart_sendStr(output);

            uart_sendChar('\t');
            uart_sendChar('\t');

            sprintf(output, "%d", object[counter].Rwidth);
            uart_sendStr(output);

            uart_sendChar('\t');
            uart_sendChar('\t');

            object[counter].Lwidth = 2.0 * object[counter].Adistance * tan((object[counter].Rwidth * M_PI) / (2.0 * 180.0));

            sprintf(output, "%.2f", object[counter].Lwidth);
            uart_sendStr(output);

            uart_sendChar('\n');
            uart_sendChar('\r');


            counter++;

        }

    return 0;

}



int get_direction(int direction, int turn)
{
    char output[30];
    direction += turn;

    if (direction == 17){
        direction = 1;
    }
    if (direction == 28){
        direction = 2;
    }
    if (direction == 0){
        direction = 16;
    }
    if (direction == -1){
        direction = 15;
    }

    uart_sendChar('\n');
    uart_sendChar('\r');

    if (direction == 1)
    {
        sprintf(output, "North");
    }
    else if (direction == 2)
    {
        sprintf(output, "North by NorthEast");
    }
    else if (direction == 3)
    {
        sprintf(output, "NorthEast");
    }
    else if (direction == 4)
    {
        sprintf(output, "East by NorthEast");
    }
    else if (direction == 5)
    {
        sprintf(output, "East");
    }
    else if (direction == 6)
    {
        sprintf(output, "East by SouthEast");
    }
    else if (direction == 7)
    {
        sprintf(output, "SouthEast");
    }
    else if (direction == 8)
    {
        sprintf(output, "South by SouthEast");
    }
    else if (direction == 9)
    {
        sprintf(output, "South");
    }
    else if (direction == 10)
    {
        sprintf(output, "South by SouthWest");
    }
    else if (direction == 11)
    {
        sprintf(output, "SouthWest");
    }
    else if (direction == 12)
    {
        sprintf(output, "West by SouthWest");
    }
    else if (direction == 13)
    {
        sprintf(output, "west");
    }
    else if (direction == 14)
    {
        sprintf(output, "West by NorthWest");
    }
    else if (direction == 15)
    {
        sprintf(output, "NorthWest");
    }
    else if (direction == 16)
    {
        sprintf(output, "North by NorthWest");
    }

    uart_sendStr(output);

    uart_sendChar('\n');
    uart_sendChar('\r');
    return direction;
}
