Black Box Oven Controller
=========================

For KU EECS 690
Giordanno Garcia, Santosh Charles, Warren Scipio, Diego Soliz, Tim Clark


Global variables
----------------

- **v_temp**: measured temperature voltage
- **dig_temp**: the digital representation of the voltage
- **conv_temp**: the measured temperature in actual degrees (celsius?)
- **set_temp**: the goal temperature
- **pid_out**: the PID output to control the heater


Modules
-------

- ADC: Diego, Giordanno
- Temp converter: Giordanno, Warren
- PID: Tim, Santosh
- Heater driver: Santosh, Diego
- UART: Warren, Tim
