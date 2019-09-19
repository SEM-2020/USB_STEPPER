/*
 * USB_Decode.c
 *
 *  Created on: ???/???/????
 *      Author: Tefa
 */

#include "USB_Decode.h"



/****************************************************
 *                Private Variables
 ****************************************************/


/****************************************************
 *                Private functions
 *****************************************************/

/*
 * Usage : For calculation of desired.
 *
 * Structure : moving old angle decimal point to add the new number
 *             converting the received number from ASCII into Decimal
 *             getting new angle by addition of last time angle and the new number
 *
 * Parameters :
 *             Received number
 *             last time  angle
 *
 * Return :     new angle
 *
 */

static unsigned long  uint32Angle_Decoding (unsigned long USB_Received_Angle , unsigned long New_Angle )
{
    New_Angle = New_Angle * 10 ;
    USB_Received_Angle = USB_Received_Angle - Numbers_Ascii_Base ; /* convert number from ASCII to Decimal */
    New_Angle = New_Angle + USB_Received_Angle ;
    return New_Angle ;
}




/****************************************************
 *                Public functions
 *****************************************************/


/*
 * Usage : For calculation of desired angle and send it to its required motor
 *
 * Structure : has two states :
 *            (1) Choose which motor we will assign the new angle into it or unexpected received data
 *            we will make an error action to handle it and also canceling last calculation to make sure it would not
 *            affect next angle.
 *            (2) calculation of Angle .
 *            (3) sends the step count to the queue.
 * Parameters :
 *             Received character
 *
 * Return :     Void
 *
 */
void vUSB_Data_Decoding (char USB_Received_Char )
{

    static  int32_t int32_Decoding_Angle =0; /* Getting Final Angle in here */
    static  int32_t i32_Sign=1;
    int16_t int16_STEPS; // calculated steps
    if(((USB_Received_Char) > (Numbers_Ascii_Base + Numbers_Ascii_Offset)) || ((USB_Received_Char) < (Numbers_Ascii_Base)))
    {
        /*  which motor we will modify its current angle or if a negative angle */
        switch (USB_Received_Char){
        /* X for steering motor */
        case 'x' :
        case 'X' :

            int16_STEPS = ((int)(((float)int32_Decoding_Angle)/STEERING_STEP))*i32_Sign;
            //Queue steering steps
            xQueueOverwrite(Queue_steering,
                            &int16_STEPS
                            );
            //reset for other
            int32_Decoding_Angle = 0 ;
            i32_Sign=1;

            break;
        /* Y for Throttle motor */
        case 'y' :
        case 'Y' :
            int16_STEPS = ((int)(((float)int32_Decoding_Angle)/THROTLE_STEP))*i32_Sign;
            //Queue steering steps
            xQueueOverwrite(Queue_throtle,
                            &int16_STEPS
                            );
            //reset for other
            int32_Decoding_Angle = 0 ;
            i32_Sign=1;

            break ;
        /* Z for brakes motor */
        case 'z' :
        case 'Z' :
            int16_STEPS = ((int)(((float)int32_Decoding_Angle)/BRAKES_STEP))*i32_Sign;
            //Queue steering steps
            xQueueOverwrite(Queue_brakes,
                            &int16_STEPS
                            );
            //reset for other
            int32_Decoding_Angle = 0 ;
            i32_Sign=1;

            break ;
        /* - for negative angle */
        case '-' :
            i32_Sign=-1;
            int32_Decoding_Angle = 0 ;
            break ;

        /* unexpected Received data Case */
        default :
            i32_Sign=1;
            int32_Decoding_Angle = 0 ;
            /* Any Error Action */
        }
    }
    else
    {
        /* calculating desired angle */
        int32_Decoding_Angle = uint32Angle_Decoding ( USB_Received_Char , int32_Decoding_Angle ) ;
    }

    return ;
}
