#include all relevent TIVA libraries 
#include thermister .h file 
#include PID .h file 

//*****************************************************************************
//  heater.c --> Module Title
//  Module encharged of turning the Heater on
// Receives data from the adc converter
// Compares this data to the desired temperature
// Determines the time to turn the heater on
//******************************************************************************

//******************************************************************************
// Set GPIO to the power resistor of the heater
// powerdrive=off
//*****************************************************************************
 
void HeaterTask(void *pvParameters)
{
    while(true)
    {
        //**********************************************************************
        // Need to obtain the digital measurement from the termistor
        // The variable name is Tc
        // User the PID to compare Tc to Ts (desired temperature)
        //**********************************************************************
//******************************************************************************      
//        Obtain measured temperature, Tc, from thermistor .c file
//        Compare Tc to Ts using the PID controller
//******************************************************************************
        if(Tc < Ts)
 
        {  
//******************************************************************************                  
//As long as the measured temperature is lower than the desired one:
// Set the Power Drive flag variable to on
// Use the PID to establish the loop mechanism
//            Turn Power Drive On or PWM until Tc=Ts
//
//            uses feedback loop mechanism of PID to bring Tc to setpoint of Ts
//            powerdrive=on; 
//            This increases or steps Temperature from Tc to Ts
//******************************************************************************   
       }
       else
       {
//******************************************************************************              
// If the mesured temperature is equal or higher than the desired one:
// Set the Power Drive flag variable to off
// Keep Power Drive Off
//******************************************************************************   

             powerdrive=off;
 
 
       }
 
    //**************************************************************************
    // Utilization of VTaskDelay() function for FREERTOS
    // software from TIVA Board
	//**************************************************************************
 
        vTaskDelay();
 
       }
 
}
