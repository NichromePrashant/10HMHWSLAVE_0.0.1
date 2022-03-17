/*
 * Peripheral.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */


#include "r_cg_userdefine.h"
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "r_sci_rx_if.h"
#include "r_rscan_rx_if.h"
//#include "Can1.h"
#include "r_cg_port.h"
#include "Peripheral.h"
#include "r_cg_wdt.h"
#include "r_cg_cmt.h"
#include "Config_ICU.h"
#include "can.h"
#include "Config_PORT.h"
#include "globals.h"
#include "All_Header.h"
#include "can_Varib.h"

extern state_t             g_state;    //added on 15032022
void Init_Pins(void)
{
	R_Config_PORT_Create();	// Initialize all the SFRs of the PortPin
	DIR_FB = 0;		// Direction pin of the stepper motor1, set to default	(double inversion)
	DIR_WB = 0;		// Direction pin of the stepper motor2, set to default	(double inversion)
	ENB_FB = 0;		// Enable pin of the stepper motor1, set to default as disable (double inversion)
//	ENB_FB = 1;       // for new stepper driver
	ENB_WB = 0;		// Enable pin of the stepper motor2, set to default as disable (double inversion)
//	ENB_WB = 1;        // for new stepper driver
	CLK_FB = 1;		// Clock pin of the stepper motor1, set to default as Low (invertion is there)
	CLK_WB = 1;		// Clock pin of the stepper motor2, set to default as Low (invertion is there)
	HOP_FB = 0;		// Photo Interrupter is On, PNP Logic
	HOP_WB = 0;		// Photo Interrupter is On, PNP Logic
	GUI_state = 1;
}


void Init_Peripherals(void)
{
	/*The Instruction below used to Initiate CAN Communication*/
	g_state = STATE_CONNECTING_CAN;
	init_can();
	R_Config_CMT0_Start();			// Start the Compare Match Timer0 used for Interval Timer
	R_Config_CMT1_Start();
	R_Config_CMT2_Start();			// Start the Compare Match Timer1 used for FeedBucket
	R_Config_CMT3_Start();			// Start the Compare Match Timer2 used for Weighing Bucket
	R_Config_ICU_IRQ0_Start();		// Start the External Port Pin Interrupt
	GUI_state = 3;
}
