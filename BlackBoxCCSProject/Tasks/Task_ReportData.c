/*--Task_ReportData.c
 *
 * Author:! ! ! Gary J. Minden
 * Organization:!! KU/EECS/EECS 690
 * Date:! ! ! ! March 13, 2016 (B60313)
 *
 * Description:! ! Transmits data via UART to PC.
 *
 */
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include "Drivers/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"

#include "Tasks/globals.h"



extern volatile uint32_t xPortSysTickCount;

//
// Define the ReportData Task
//
ReportData_Item theReport;
BaseType_t queuestatus;

//
// Insure UARTStdio is initialized
//
//UART_Initialization();
//
// Define ReportData_Queue
//
extern void Task_ReportData ( void *pvParameters ) {
	while ( 1 ) {
	 //
	 // Try to read ReportItem from ReportData_Queue.
	 // If a ReportData_Item is returned, print the contents
	 //! ! to the UART via UARTStdioPrintf

		queuestatus = xQueueReceive( ReportData_Queue, &theReport, 10 * portTICK_PERIOD_MS );
		if ( queuestatus == pdTRUE ) {
			UARTprintf( "%08d,%02d,%d,%d\n",
			theReport.TimeStamp, theReport.ReportName,
			theReport.ReportValue_0, theReport.ReportValue_1 );
		}
		vTaskDelay( (1000 * configTICK_RATE_HZ) / 1000 );
	}
}
