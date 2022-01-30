/*
 * servo.h
 *
 *  Created on: Oct 23, 2020
 *      Author: Cristofer Medina
 */

#ifndef SERVO_INIT_H_
#define SERVO_INIT_H_

#include "timer.h"
#include "lcd.h"
#include "resetSimulation.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

void servo_init();

int servo_move(int degrees);

#endif
