include temperature_sensor_definitions 
include board_libraries 
include queues 
create_queue my_queue 
 
 
ADC_TASK(){ 
my_queue = setup_queue(parameters) 
Enable_Peripheral_GPIO 
Enable_GPIOS 
GPIO_Configure 
Enable_Peripheral_ADC 
Enable_ADC 
ADC_Configure 
 
while(true){ 
 
 
 
trigger_ADC 
data = ADC_data_get() 
my_qeueue.send_data(data) 
 
task_delay() 
} 
} 
