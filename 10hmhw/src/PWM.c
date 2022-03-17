/*
 * PWM.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */


#include "PWM.h"
#include "r_cg_userdefine.h"
#include "Timer.h"
#include "globals.h"
#include "r_cg_macrodriver.h"
#include "Config_MTU0.h"
#include "Config_ICU.h"
#include "r_cg_cmt.h"
#include "All_Header.h"

//
void PWM_ISR(void)
{
	//Clr_WatchDog();	  10032022			// Clear watch dog timer and reset

	if(Pulses_SCR == 1)			// must fire atleast two pulses
	{
		Pulses_SCR = 0;			// Reset the Number of pulses triggered to SCR
		PWM_Stop();				// Stop PWM block
		R_Config_ICU_Create();
		R_Config_ICU_IRQ0_Start();		// Start the external zcip ISR block
	}
	Pulses_SCR++;
//	Clr_WatchDog();    //10032022
}
