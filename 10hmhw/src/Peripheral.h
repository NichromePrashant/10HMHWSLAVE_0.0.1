/*
 * Peripheral.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

/*typedef enum e_state
{
    STATE_CONNECTING_UART,
    STATE_CONNECTING_CAN,
    STATE_CAN_TO_UART,
    STATE_UART_TO_CAN
} state_t;*/


//sci_hdl_t           g_sci_handle;
//state_t             g_state;



void Init_Pins(void);
void Init_Peripherals(void);

#endif /* PERIPHERAL_H_ */
