/*
 * Auto_Tare.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#include "Auto_Tare.h"
#include "globals.h"
#include "ADC_CS5532.h"
#include "can.h"
#include "Flash.h"
#include "RUN_OP.h"
#include "Calibration_Varib.h"
#include "All_Header.h"

extern uint32_t gs_test_w_buff[TEST_BUFF_NUM];

extern uint32_t gs_test_r_buff[TEST_BUFF_NUM];

//extern unsigned char 		adc_stable;

//unsigned int Actual_Dump_Counter;



void Auto_Tare()
{
	//Clr_WatchDog();     //10032022
	Cycle_TMR      = AUTO_TARE_CYCLE_TIME;						// Set the Settling Cycle Timer Tare Operation
	Flag_Tare_Done = 0;						// Reset the Tare Done Flag

	while(Cycle_TMR)
	{
		//Clr_WatchDog();
		read_adc();						// Read Load Cell ADC count from CS5532
		check_stable();					// Check if the Counts are Stable
	//	TareCnt=0;
		if(AUI_adc_stable)					// if ADC is stable
		{
			CSI_TareCnt           = ASI_adc_count;		// Move current ADC count to the Tare Count
			Flag_Tare_Done    = 1;			// Set the Tare Flag
			Actual_Dump_Counter = 0;
			gs_test_w_buff[0] = CSI_TareCnt;

			//gs_test_w_buff[1] = Flag_Tare_Done;

			AUI_adc_stable = 0;				// Rest the ADC stable Flag
		//	Clr_WatchDog();

		//	Cycle_TMR=0;
		}
	}

	Auto_Tare_Flag = 0;

	Send_Tarecount();
	Tare_Send_Time = CAN_WAIT_TIME * CAN_SlaveID;
	Tare_Send_Flag = 1;
}
