//******************************************************************************
//! Include things
//!  modules:
//!\param     ADC converter
//!\param     PID controller
//!\param    Heater
//!\param   FreeRTOS
//******************************************************************************

//******************************************************************************
//! Declare globals
//******************************************************************************

extern double v_temp;   // Measured temperature voltage
extern double dig_temp; //!< The digital representation of the voltage)
extern double conv_temp; //!< The measured temperature in actual degrees(celsius)
extern double set_temp;  //!< The goal temperature
extern double pid_out;  //!< The PID output to control the heater

int main(void) {





 //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    //GPIOPinConfigure(GPIO_PA0_U0RX);
    //GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
    

    //
    //ADC Module task creation.
    //
    //  Creates an ADC task to be handled by the freeRTOS task scheduler.
    //
    xTaskCreate(ADC_TASK);
    //
    // Heater Module task creation.
    //
    //  Creates Heater task to be handled by the freeRTOS task scheduler.
    //
    xTaskCreate(HEATER_TASK);
    // Temperature Convertor task creation.
    //
    //  Creates Temperature Converter task to be handled by the freeRTOS task scheduler.
    //
    xTaskCreate(TEMP_CONV_TASK);
    //
    // System Initilization.
    //
    //  Initiliazed the boards system.
    //
    SystemInitialize();
    //
    // Task Scheduler
    //
    //  Initiliazes freeRTOS task scheduler.
    //
    vTaskStartScheduler();

  while (true) {
  }
}


