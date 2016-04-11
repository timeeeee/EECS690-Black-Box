declare static variables error, integral, previous_error;

static unsigned long temp1;//temp variable to store the setpoint temp, Ts
static unsigned long temp2;//temp variable for Tc
unsigned long Kp; //sum of previous error
unsigned long Ki;//
unsigned long Kd;
unsigned long error;
unsigned long error_2;
unsgined long prev_error;
unsigned PID_trigger;

void PIDInit()
{
  integral = 0;
  previous_error = 0;
}

void PIDTask(void *pvParameters)
{
  while (true)
    {

      temp1=Ts;
      temp2=Tc;


      PID_trigger=Kp*error + Ki*error_2 + Kd*(error-prev_error);
      // PID will take as input Tc (temperature converted) and Ts (desired temperature)
      // It will output a control variable control_variable to drive a PWM
      // The output is the sum three parts, with coefficients for each:
      //     Proportional: Kp * error
      //     Integral: Ki * integral of error so far
      //     Derivative: Kd * rate of change of error

      error = Ts - Tc;

      // Proportional
      control_variable = Kp * error;

      // Integral
      // Use trapezoidal approximation to cumulatively calculate integral
      integral += (error + previous_error) / 2 * dt;
      control_variable += Ki * integral;

      // Derivative
      // Wikipedia indicates that this is highly prone to noise- we may want to either:
      //     Skip it altogether
      //     Use a moving-window average as a make-shift low-pass filter
      // Approximate graph of error as straight line from last time step to now
      control_variable += Kd * (error - previous_error) / dt;

      previous_error = error;
      vTaskDelay();
    }
}
