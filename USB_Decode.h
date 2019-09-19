/*
 * USB_Decode.h
 *
 *  Created on: ???/???/????
 *      Author: Tefa
 */

#ifndef USB_DECODE_H_
#define USB_DECODE_H_

//freeRTOS includes

#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>
#include <queue.h>

#include <stdint.h>

/****************************************************
 *                Global Variables
 ****************************************************/
    extern QueueHandle_t Queue_steering;
    extern QueueHandle_t Queue_throtle;
    extern QueueHandle_t Queue_brakes;




/****************************************************
 *                Defines
 ****************************************************/

#define Numbers_Ascii_Base 0x30
#define Numbers_Ascii_Offset 9
#define STEERING_STEP 1.8
#define THROTLE_STEP 1.8
#define BRAKES_STEP 1.8


/******************************************************
 *                Static Configuration
 ******************************************************/


/******************************************************
 *                Dynamic Configuration
 ******************************************************/


/****************************************************
 *                     Functions
 ****************************************************/

void vUSB_Data_Decoding (char USB_Received_Data ) ;

#endif /* USB_DECODE_H_ */
