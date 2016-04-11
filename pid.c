#include <math.h>

declare static variables error, integral, previous_error;

static unsigned long temp1;//temp variable to store the setpoint temp, Ts
static unsigned long temp2;//temp variable for Tc
unsigned long Kp=100; //sum of previous error
unsigned long Ki=100;//
unsigned long Kd=100;
unsigned long error=0;
unsigned long error_2=0;
unsigned long prev_error=0;
unsigned long count=0;
unsigned PID_trigger=0;
void PIDInit()
{
  integral = 0;
  previous_error = 0;
}

public static double trapez_funct(double x, double err1, int cnt)
{
  unsigned long double y;
  for(int i=0; i< cnt; i++)
  {
    y=(err1/2)*(x + (2*x+err1) + y);
  }
  return y;
}

void PIDTask(void *pvParameters)
{
  while (true)
    {

      temp1=Ts;
      temp2=Tc;



      // PID will take as input Tc (temperature converted) and Ts (desired temperature)
      // It will output a control variable control_variable to drive a PWM
      // The output is the sum three parts, with coefficients for each:
      //     Proportional: Kp * error
      //     Integral: Ki * integral of error so far
      //     Derivative: Kd * rate of change of error
    
      error = temp1-temp2; //(  error = Ts - Tc)
      while (error != 0)
      {
        //output heat:
        PID_trigger=1;


        control_variable = Kp * error;

        //Perform trapezoidal using integral function
        integral = trapez_funct(Ki,error,count);
        control_variable += Ki * integral;
        control_variable += Kd * (error - previous_error) / dt;
        PID_trigger=Kp*error + Ki*error_2 + Kd*(error-prev_error);
        prev_error=error;
        count++;
      }
      PID_trigger=0;
      /*
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
      vTaskDelay();*/
    }
}
