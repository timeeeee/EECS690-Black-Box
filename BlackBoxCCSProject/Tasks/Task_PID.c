#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
	 
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <Tasks/globals.h>
	 
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "globals.h"


/*
PID Parameters
(If we want to change these while the board is running they'll need to be declared somewhere else and declared here using extern)
*/
float Kp = 800;
float Ki = 3;
float Kd = 0;

float pid_out = 0;

float current_temp;
float error;  // Most recent calculated error
float prev_error = 0;  // Previous error
float integral = 0;  // Sum of all error so far
float integral_max;
float integral_decay = .99;

/*
If we have just turned on the board or a setting changes, the derivative may go
nuts- if this is set to true the PID module will skip the derivative part for
one step.
*/
int skip_derivative_flag = 1;

// Previous tick count (used to find time since last loop)
TickType_t tick_count;
TickType_t prev_tick_count = 0;

// Time since last loop (seconds)
float dt;

extern void Task_PID(void *pvParameters){
	integral_max = 1000.0 / Ki;  // Integral maximum should be just enough to keep the heater at 100%.
  while (true) {
    // PID will take as input current temperature and target
    // temperature (temp_set).
    // It will output a control variable control_variable to drive a PWM
    // The output is the sum three parts, with coefficients for each:
    //     Proportional: Kp * error
    //     Integral: Ki * integral of error so far
    //     Derivative: Kd * rate of change of error

    // Get time since last loop
    tick_count = xTaskGetTickCount();
    dt = (tick_count - prev_tick_count) / 1000;
    prev_tick_count = tick_count;
    
    
    // Get current temp from queue and calculate error
    error = 0;
    if (temp_qc != 0) {
      if (xQueueReceive(temp_qc, (void *) &current_temp, (TickType_t) 10)) {
		error = set_temp - current_temp;
      } else {
    	  printf("PID couldn't get temperature from queue\n");
      }
    }

    // Add proportional part
    pid_out = Kp * error;

    // Update integral and add integral part
    integral += (error + prev_error) / 2 * dt;
    if (integral > integral_max) integral = integral_max;
    if (integral < -integral_max) integral = -integral_max;
    // integral *= integral_decay;
    pid_out += Ki * integral;
    //printf("integral of error so far: %f\n", integral);

    // Update derivative part
    // If a setting has just changed we'll want to skip this for one step.
    // If skip_derivative_flag is set, skip a step and set the flag back to 0.
    // Otherwise, calculate derivative from this and previous error.
    if (skip_derivative_flag == 1) {
      skip_derivative_flag = 0;
    } else {
      printf(", %f", error);
      pid_out += Kd * (error - prev_error) / dt;
      printf(", %f", Kd * (error - prev_error) / dt);
    }

    printf(", %f", integral);

    // Save this error for next step
    prev_error = error;

    // Convert pid_out float to time on in ms out of 1000
    // If pid_out is negative we should decrease temperature- 0 ms
    // If positive, set time-on to pid_out, but clamp at 1000 max
    if (pid_out < 0) {
      OnTime_mS = 0;
    } else if (pid_out > 1000) {
      OnTime_mS = 1000;
    } else {
      OnTime_mS = pid_out;
    }
    printf(", %f\n", OnTime_mS);

    vTaskDelay((1000 * configTICK_RATE_HZ) / 1000);
  }
}
