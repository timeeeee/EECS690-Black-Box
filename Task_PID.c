#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
	 
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
	 
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
	 
#include "FreeRTOS.h"
#include "task.h"

#include "Task_PID.h"

// Get current and target temperature global variables
extern float conv_temp;
extern float set_temp;
extern float OnTime_mS;

/*
PID Parameters
(If we want to change these while the board is running they'll need to be declared somewhere else and declared here using extern)
*/
float kp = 1;
float ki = 1;
float kd = 1;

float error;  // Most recent calculated error
float prev_error = 0;  // Previous error
float integral = 0;  // Sum of all error so far

/*
If we have just turned on the board or a setting changes, the derivative may go
nuts- if this is set to true the PID module will skip the derivative part for
one step.
*/
int skip_derivative_flag = 1;

// Change of time since previous step
float dt = 1;

extern void Task_PID(void *pvParameters)
{
  while (true) {
    // PID will take as input current temperature (temp_conv) and target
    // temperature (temp_set).
    // It will output a control variable control_variable to drive a PWM
    // The output is the sum three parts, with coefficients for each:
    //     Proportional: Kp * error
    //     Integral: Ki * integral of error so far
    //     Derivative: Kd * rate of change of error

    error = temp_set - temp_conv;

    // Add proportional part
    pid_out = Kp * error;

    // Update integral and add integral part
    integral += (error + prev_error) / 2 * dt;
    pid_out += Ki * integral;

    // Update derivative part
    // Wikipedia indicates this is highly prone to noise- we may want to:
    //   Skip it altogether (sounds like this still gives ok results)
    //   Use moving-window average as a low-pass filter
    
    if (skip_derivative_flag == 1) {
      skip_derivative_flag = 0;
    } else {
      pid_out += Kd * (error - prev_error) / dt;
    }

    // Save this error for next step
    prev_err = error;

    // Convert pid_out float to time on in ms out of 1000
    // If pid_out is negative we should decrease temperature- 0 ms
    // If positive, set time-on to pid_out, but clamp at 1000 max
    if (pid_out < 0) {
      TimeOn_mS = 0;
    } else if (pid_out > 1000) {
      TimeOn_mS = 1000;
    } else {
      TimeOn_mS = pid_out;
    }

    vTaskDelay((1000 * configTICK_RATE_HZ) / 1000));
  }
}
