#include all relevent TIVA libraries 
#include thermister .h file 
#include PID .h file 
Set GPIO to the power resistor of the heater 
powerdrive=off 
 
void HeaterTask(void *pvParameters) 
{  
while(true) 
{  
 
Obtain measured temperature, Tc, from thermistor .c file 
Compare Tc to Ts using the PID controller 
 
if(Tc != Ts) 
 
{ 
 
 
 
 
Turn Power Drive On or PWM until Tc=Ts  
 
 
-uses feedback loop mechanism of PID to bring Tc to setpoint of Ts 
 
 
-powerdrive=on; 
 
 
-This increases or steps Temperature from Tc to Ts 
 
 
} 
 
else 
 
{ 
 
Keep Power Drive off 
 
 
-powerdrive=off; 
 
 
} 
 
 
 
vTaskDelay(); 
 
} 

 
 
 

 
} 
