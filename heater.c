#include all relevent TIVA libraries 
#include thermister .h file 
#include PID .h file 

/********************************************//**
*  Need to revise the GPIO port to which the power resistor is connected
*  Assume that the system does not need to work at start point
***********************************************/
//Set GPIO to the power resistor of the heater
//powerdrive=off
 
//void HeaterTask(void *pvParameters)
//{
//    while(true)
//    {
        //!
        //! Need to obtain the digital measurement from the termistor
        //! The variable name is Tc
        //! User the PID to compare Tc to Ts (desired temperature)
        //!
//        Obtain measured temperature, Tc, from thermistor .c file
//        Compare Tc to Ts using the PID controller

//        if(Tc < Ts)
 
//        {
        //!
        //! As long as the measured temperature is lower than the desired one:
        //! Set the Power Drive flag variable to on
        //! Use the PID to establish the loop mechanism
//            Turn Power Drive On or PWM until Tc=Ts
 
 
//            -uses feedback loop mechanism of PID to bring Tc to setpoint of Ts
 
 
//            -powerdrive=on;
 
 
//            -This increases or steps Temperature from Tc to Ts
 
 
//        }
//        else
//        {

        //! If the mesured temperature is equal or higher than the desired one:
        //! Set the Power Drive flag variable to off
 
//            Keep Power Drive off
 
 
//            -powerdrive=off;
 
 
//        }
 
 
 
//        vTaskDelay();
 
//    }
 
//}
