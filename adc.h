/*
 * adc.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Cristofer Medina
 */

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

#include "timer.h"
#include "lcd.h"
#include "resetSimulation.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

void acd_init();

int adc_read();

#endif
