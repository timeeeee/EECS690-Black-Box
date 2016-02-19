// Include things
//   modules:
//     ADC converter
//     Temperature converter
//     PID controller
//     Heater

//   FreeRTOS

// Declare globals
extern double v_temp;  //measured temperature voltage
extern double dig_temp; // the digital representation of the voltage)
extern double conv_temp; //the measured temperature in actual degrees (celsius?)
extern double set_temp;  //the goal temperature
extern double pid_out;  //the PID output to control the heater

int main(void) {
  // call xTaskCreate on tasks

  // call init functions

  vTaskStartScheduler();

  while (1) {
    
  }
}

//   ADC converter
//   Temperature converter
//   PID controller
//   Heater


