/*
 * Task_Simple_ADC.h
 *
 *  Created on: Apr 9, 2016
 *      Author: dsolizca
 */

#ifndef TASKS_GLOBALS_H_
#define TASKS_GLOBALS_H_

#include "FreeRTOS.h"
#include "queue.h"

extern QueueHandle_t temp_qc;
extern QueueHandle_t ReportData_Queue;
extern float set_temp;
extern float OnTime_mS;

typedef struct ReportData_Item {
uint32_t TimeStamp;
uint32_t ReportName;
uint32_t ReportValue_0;
uint32_t ReportValue_1; } ReportData_Item;

extern volatile uint32_t xPortSysTickCount;

#endif /* TASKS_GLOBALS_H_ */
