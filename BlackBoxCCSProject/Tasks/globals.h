/*
 * Task_Simple_ADC.h
 *
 *  Created on: Apr 9, 2016
 *      Author: dsolizca
 */

#ifndef TASKS_GLOBALS_H_
#define TASKS_GLOBALS_H_

#include "queue.h"

extern QueueHandle_t temp_qc;
extern QueueHandle_t ReportData_Queue;
extern float set_temp;
extern float OnTime_mS;


#endif /* TASKS_GLOBALS_H_ */
