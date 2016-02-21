#include adc_converter.h
#include temperature_sensor_definitions 
#include board_libraries 
#include queues 




//*****************************************************************************
//! This module is for the analog digital converter
//! This is for obtaining a temperature sample wave and
//! convert the sample to a digital value.
//! This is then calculated to a value that doesn't take
//! into effect the resistance. 
//! The analog digital converter will be attached to the TIVA Board
//! due to the booster pack via GPIO Pins.
//******************************************************************************
 
//******************************************************************************
//! Necessary libraries and .h files
//******************************************************************************





//******************************************************************************
//! Module to convert the analog input to degrees celsius.
//! Also used to convert digital to actual temperature depending
//! on resistance.
//******************************************************************************

void ADC_TASK( void *pvParameters ) {
    //**************************************************************************
    //! Utilization of queue due to activating ADC or not
    //**************************************************************************
    create queue my_queue;
    my_queue = setup_queue(parameters);
    //**************************************************************************
    //! Set up GPIOs
    //**************************************************************************
    Enable_Peripheral_GPIO;
    Enable_GPIOS;
    GPIO_Configure;
    
    //**************************************************************************
    //! Set up ADC
    //**************************************************************************
    Enable_Peripheral_ADC;
    Enable_ADC;
    ADC_Configure;

    //**************************************************************************
    //! Set local variables
    //! these should include whatever constants our thermister ->
    //!   celsius equation needs later
    //**************************************************************************
    
    while(true) {

    //**************************************************************************
	//! Get ADC data:
    //! Trigger the ADC
    //**************************************************************************
        
        trigger_ADC;
    //**************************************************************************
	//! Wait for ADC to finish
	//**************************************************************************
    while (!ADC_finished()) {};
    
    //**************************************************************************
	//! Get data from adc
	//**************************************************************************
    dig_temp = ADC_data_get();
    //**************************************************************************
	//! Convert resistance to celsius using equation
	//!     V_temp = Rdd * (R / (R + RBias))
	//! Save the results to output conv_temp.
	//! do we need to update this to the equation from the slides?
	//**************************************************************************
    conv_temp = Rdd * (R / (R + RBias));
    //**************************************************************************
	//! Save results to output
	//**************************************************************************
    my_qeueue.send_data(data);
    //**************************************************************************
    //! Utilization of VTaskDelay() function for FREERTOS
    //! software from TIVA Board
	//**************************************************************************
    task_delay();
    }
}
