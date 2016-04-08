#include all relevent TIVA libraries 
#include thermister .h file 
#include PID .h file 

//*****************************************************************************
//!  heater.c --> Module Title
//!  Module encharged of turning the Heater on
//! Receives data from the adc converter
//! Compares this data to the desired temperature
//! Determines the time to turn the heater on
//******************************************************************************

//******************************************************************************
//! Set GPIO to the power resistor of the heater
//! powerdrive=off
//*****************************************************************************
 
#include <math.h>

static unsigned long temperatureconecc = 0;

void convertTemperature(void *pvParameters){
	//have to convert the temperature from ADC to a temperature value
	//compare the measured temperature to desired temperature and get the change in power
	//have the power driver control the current through resistor
	//

	//Declaring variables for Vishat Thermistor Resistance Formula
	float d = -3.730535E+03;
	float a = -14.6337;
	float b = 4791.842;
	float c = -115334;
	float rref = 10000;

	//tempval will be the converted value of the temperature
	float tempval;
	float workingtemp = tempval + 273.16 // as seen on the slides in the webpage

	//From now this formula will work in Celsius
	float resistanceval = rref * exp(a+(b/workingtemp) + (c/pow(workingtemp,2) + (d/pow(workingtemp,3))))

	//will use desiredtemperature to calculate the power required to get to that temperature
	float desiredtemperature

	//need to calculate the difference in power to get to the desired temperature(check werbpage)
	//after getting the power apply it
	//will calculate resistance and use it to get a temporary voltage that will be applied on that cycle



}
 
void HeaterTask(void *pvParameters)
{
    while(true)
    {
        //**********************************************************************
        //! Need to obtain the digital measurement from the termistor
        //! The variable name is conv_temp
        //! User the PID to compare conv_temp to set_temp (desired temperature)
        //**********************************************************************
//******************************************************************************      
//!        Obtain measured temperature, conv_temp, from thermistor .c file
//!        Compare Tc to Ts using the PID controller
//******************************************************************************
        if(conv_temp < set_temp)
 
        {  
//******************************************************************************                  
//!As long as the measured temperature is lower than the desired one:
//! Set the Power Drive flag variable to on
//! Use the PID to establish the loop mechanism
//!            Turn Power Drive On or PWM until conv_temp=set_temp
//!            uses feedback loop mechanism of PID to bring Tc to setpoint of Ts
//!            powerdrive=on; 
//!            This increases or steps Temperature from conv_temp to set_temp
//******************************************************************************   
       }
       else
       {
//******************************************************************************              
//! If the mesured temperature is equal or higher than the desired one:
//! Set the Power Drive flag variable to off
//! Keep Power Drive Off
//******************************************************************************   

             powerdrive=off;
 
 
       }
 
    //**************************************************************************
    //! Utilization of VTaskDelay() function for FREERTOS
    //! software from TIVA Board
	//**************************************************************************
 
        vTaskDelay();
 
       }
 
}
