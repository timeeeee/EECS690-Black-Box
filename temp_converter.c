-Tm, temperature measured 
-Tc, temperature converted 
-Ts, desired temperature 
-R, power resitance 
 
#include all relavent TIVA libraries 
#include ADC converter .h f ile 
Set GPIO of the sensor to the TIVA board 
 
import parameters through the ADC converter to convert signal of temperature  
 
void Tempconverterask(void *pvParameters) 
{  
while(true) 
{  
 
measures temperature of the oven and set that to Tm 
-collect signals from ADC for a time period to obtain constant temp, Tm 
 
measures power resistance using the ADC converter and set that to R 
 
Tm = measured temperature 
R = measured power resistance 
 
convert resistance of to C 
 
convert temperature using equation: 
 
VTemp=Rdd*(R/(R+Rbias) 
 
vTaskDelay(); 
 
} 

 
 
}
