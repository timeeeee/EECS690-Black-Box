Black Box Oven Controller
=========================

For KU EECS 690

Global variables

* (**v_temp**: measured temperature voltage)
* (**dig_temp**: the digital representation of the voltage)
* **conv_temp**: the measured temperature in actual degrees (celsius?)
* **set_temp**: the goal temperature
* **pid_out**: the PID output to control the heater

(From talking after class today it sounded like we wouldn't need v_temp and dig_temp, since the ADC module would just do the conversions and output actual measured temperature conv_temp)