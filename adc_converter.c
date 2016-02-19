// Include stuff
#include adc_converter.h
include temperature_sensor_definitions 
include board_libraries 
include queues 

/*
 * @ Santosh:
 * Is the ADC going to be a physical component? If so we'll need to
 * read from some number of pins, and generate a number from them.
 * Alternatively, is there an ADC on the Tiva boards? Looking back
 * at old labs we used an ADC "sequencer" but those were different
 * boards. The data sheet for the Tiva boards has analog GPIO pins
 * as part of the "BoosterPack"- I don't know if that means we'll be
 * able to use them or not.
 */

/**
 *  Module to convert the analog input to degrees celsius.
 *  
 */

void ADC_TASK( void *pvParameters ) {
    // @ Santosh: do we need a queue for this?
    create queue my_queue;
    my_queue = setup_queue(parameters);

    //! Set up GPIOs
    Enable_Peripheral_GPIO;
    Enable_GPIOS;
    GPIO_Configure;

    //! Set up ADC
    Enable_Peripheral_ADC;
    Enable_ADC;
    ADC_Configure;

    //! Set local variables
    // these should include whatever constants our thermister ->
    //   celsius equation needs later

    while(true) {


	//! Get ADC data:
        //! Trigger the ADC
        trigger_ADC;
	//! Wait for ADC to finish
	while (!ADC_finished()) {};

	//! Get data from adc
	dig_temp = ADC_data_get();

	//! Convert resistance to celsius using equation
	//!     V_temp = Rdd * (R / (R + RBias))
	//! Save the results to output conv_temp.
	// do we need to update this to the equation from the slides?
	conv_temp = Rdd * (R / (R + RBias));

	//! Save results to output
	my_qeueue.send_data(data);

	task_delay();
    }
}
