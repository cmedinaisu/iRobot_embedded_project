
#include "open_interface.h"
#include "uart.h"


void move_forward(oi_t*sensor, double centimeters);

void move_backward(oi_t*sensor, double centimeters);

void turn_clockwise(oi_t*sensor, double degrees);

void turn_counter_clockwise(oi_t*sensor, double degrees);
