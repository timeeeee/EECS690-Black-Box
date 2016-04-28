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
#include "queue.h"

#include "globals.h"


/**
PID Parameters
(If we want to change these while the board is running they'll need to be declared somewhere else and declared here using extern)
*/
float kp = 1;
float ki = 1;
float kd = 1;

float current_temp;
float error;  // Most recent calculated error
float prev_error = 0;  // Previous error
float integral = 0;  // Sum of all error so far

/**
If we have just turned on the board or a setting changes, the derivative may go
nuts- if this is set to true the PID module will skip the derivative part for
one step.
*/
int skip_derivative_flag = 1;

/// Previous tick count (used to find time since last loop)
TickType_t tick_count;
TickType_t prev_tick_count = 0;

/// Time since last loop
float dt;

extern void Task_PID(void *pvParameters)
{
  while (true) {
    /**PID will take as input current temperature and target
     	*temperature (temp_set).
    	*It will output a control variable control_variable to drive a PWM
    	*The output is the sum three parts, with coefficients for each:
    	*Proportional: Kp * error
    	*Integral: Ki * integral of error so far
    	*Derivative: Kd * rate of change of error
			*/

    /// Get time since last
    tick_count = xTaskGetTickCount();
    dt = tick_count - prev_tick_count;
    prev_tick_count = tick_count;


    /// Get current temp from queue and calculate error
    error = 0;
    if (temp_qc != 0) {
      if (xQueuePeek(temp_qc, (void *) &current_temp, (TickType_t) 10)) {
	printf("PID got temperature %f from queue\n", current_temp);
	error = temp_set - current_temp;
      } else {
	printf("PID couldn't get temperature from queue\n");
      }
    }

    /// Add proportional part
    pid_out = Kp * error;

    // Update integral and add integral part
    integral += (error + prev_error) / 2 * dt;
    pid_out += Ki * integral;

    /** Update derivative part
    	* If a setting has just changed we'll want to skip this for one step.
    	* If skip_derivative_flag is set, skip a step and set the flag back to 0.
    	* Otherwise, calculate derivative from this and previous error.
			*/
    if (skip_derivative_flag == 1) {
      skip_derivative_flag = 0;
    } else {
      pid_out += Kd * (error - prev_error) / dt;
    }

    /// Save this error for next step
    prev_err = error;

    /** Convert pid_out float to time on in ms out of 1000
     	*If pid_out is negative we should decrease temperature- 0 ms
    	* If positive, set time-on to pid_out, but clamp at 1000 max
			*/
    if (pid_out < 0) {
      OnTime_mS = 0;
      printf("PID set heater all the way off\n");
    } else if (pid_out > 1000) {
      OnTime_mS = 1000;
      printf("PID set heater all the way on\n");
    } else {
      OnTime_mS = pid_out;
      printf("PID set heater to %i / 1000\n", OnTime_mS);
    }

    vTaskDelay((1000 * configTICK_RATE_HZ) / 1000));
  }
}
