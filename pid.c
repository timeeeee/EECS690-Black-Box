#include "globals.h"

/*
From globals.h, we get:

  - float conv_temp, the current measured temperature
  - float set_temp, the current target temperature
  - unsigned longs Kp, Ki, Kd (declared but not set)
  - float pid_out, the output variable used to drive the heater
*/

float dt;
float error;
float prev_error;
float integral;
int delay_ms = what;


void PIDInit()
{
  integral = 0;

  prev_error = 0;
  
  Kp = 100;
  Ki = 100;
  Kd = 100;
}

// Calculate the "area" between errors 'err1' and 'err2' over time 'dt'
static double trapez_funct(float err1, float err2, float dt)
{
  return (err1 + err2) / 2 / dt;
}

void PIDTask(void *pvParameters)
{
  while (true) {
    // PID will take as input current temperature (temp_conv) and target
    // temperature (temp_set).
    // It will output a control variable control_variable to drive a PWM
    // The output is the sum three parts, with coefficients for each:
    //     Proportional: Kp * error
    //     Integral: Ki * integral of error so far
    //     Derivative: Kd * rate of change of error

    // Get time since last loop
    dt = 1.0; // fix this

    error = Ts - Tc;

    // Add proportional part
    pid_out = Kp * error;

    // Update integral and add integral part
    integral += trapez_funct(err, prev_err, dt);
    pid_out += Ki * integral;

    // Update derivative part
    // Wikipedia indicates this is highly prone to noise- we may want to:
    //   Skip it altogether (sounds like this still gives ok results)
    //   Use moving-window average as a low-pass filter
    pid_out += Kd * (error - prev_error) / dt;

    // Save this error for next step
    prev_err = error;

    vTaskDelay(delay_ms);
  }
}
