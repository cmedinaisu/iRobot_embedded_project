#include "servo.h"
#include "timer.h"
#include "lcd.h"
#include "adc.h"
#include "resetSimulation.h"
#include "math.h"
#include "uart.h"
#include "stdio.h"
#include "stdlib.h"
#include "ping.h"


struct objects;

void scan();

int get_direction(int direction, int turn);
