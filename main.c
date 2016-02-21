// Include things
//   modules:
//     ADC converter
//     PID controller
//     Heater

//   FreeRTOS

// Declare globals
extern double v_temp;  //!< Measured temperature voltage
extern double dig_temp; //!< The digital representation of the voltage)
extern double conv_temp; //!< The measured temperature in actual degrees (celsius?)
extern double set_temp;  //!< The goal temperature
extern double pid_out;  //!< The PID output to control the heater

int main(void) {
    //!ADC Module task creation.
    /*!
      Creates an ADC task to be handled by the freeRTOS task scheduler.
    */
    xTaskCreate(ADC_TASK);
    //! Heater Module task creation.
    /*!
      Creates Heater task to be handled by the freeRTOS task scheduler.
    */
    xTaskCreate(HEATER_TASK);
    //! Temperature Convertor task creation.
    /*!
      Creates Temperature Converter task to be handled by the freeRTOS task scheduler.
    */
    xTaskCreate(TEMP_CONV_TASK);
    //! System Initilization.
    /*!
      Initiliazed the boards system.
    */
    SystemInitialize();
    //! Task Scheduler
    /*!
      Initiliazes freeRTOS task scheduler.
    */
    vTaskStartScheduler();

  while (true) {
  }
}


