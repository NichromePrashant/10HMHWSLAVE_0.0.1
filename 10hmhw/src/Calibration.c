/*
 * Calibration.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Pustake
 */

#include "r_rscan_rx_if.h"
#include "globals.h"
#include "Peripheral.h"
#include "r_cg_userdefine.h"
#include "Calibration.h"
#include "Flash.h"
#include "ADC_CS5532.h"
#include "can.h"
#include "RUN_OP.h"
#include "Calibration_Varib.h"
#include "Stepper_Motor_Varib.h"
#include "All_Header.h"


//extern unsigned char 		adc_stable;
//extern unsigned int	     GUI_Cycle_TMR;
extern uint32_t gs_test_w_buff[TEST_BUFF_NUM];

extern uint32_t gs_test_r_buff[TEST_BUFF_NUM];
//***********************************************************************************************************************
// * Function Name	: void CalibOperation(void)
// * Description	: function defines the calibration process of the system.
//***********************************************************************************************************************
void CalibOperation(void)
{

	/*The Following two condition used to generate Dump trigger*/
	if((Dump_Flag==TRUE)&&(Flag_CalOpr_Stage1 == 0))	// Check if Dump Button is pressed
	{
		if(HIN_WB==0 && ENB_WB == 0)
		{
			Flag_WB_Trig_Edge  = 0;
		//	WB_Angle_Ptr = 0;
			Flag_WB_Trig       = 1;				// Used to Trigger WeighBucket of the System
			CLK_WB             = 1;
		//	Flag_DumpCyc       = 1;				// Decode weather to Run the Weighing Bucket
			Flag_CalOpr_Stage1 = 1;			// Inter-Clock of Stage 1 Complition Flag
			Dump_Flag          = FALSE;
		}
		else
		{
			if(SUI_homing_flag_wb == 0 && Flag_WB_Trig == 0)
			{
				SUI_homing_flag_wb     = 1;
				Flag_CalOpr_Stage1 = 1;
				Dump_Flag          = FALSE;
			}
		}

	}

	if(((Dump_Flag==FALSE))&&(Flag_CalOpr_Stage1 == 1))		// Check is Dump Button is released
	{
		Flag_CalOpr_Stage1 = 0;			// Reset the Inter-Lock of Stage 1 Complition Flag
	}

/*The Following two condition represent calibration time taring logic*/


	if((Tare_Flag==TRUE)&&(Cycle_TMR == 0))		       // Check if Tare Button is Pressed  (Flag_CalOpr_Stage2 == 0)&&
	{
		Cycle_TMR          = CALIB_CYCLE_TIME;		  // Set the Settling Cycle Timer Tare Operation
		Flag_Tare_Done     = 0;						 // Reset the Tare Done Flag
	//	Flag_CalOpr_Stage2 = 1;					    // Set the Inter-Lock of Tare Calibration operation

		while(Cycle_TMR)
		{
		///	Clr_WatchDog();     ///10032022
			read_adc();                               // Read Load Cell ADC count from CS5532
			check_stable();					          // Check if the Counts are Stable
	//		TareCnt=0;

			if(AUI_adc_stable)					         // if ADC is stable
			{
				CSI_TareCnt           = ASI_adc_count;		// Move current ADC count to the Tare Count
				Flag_Tare_Done    = 1;			   // Set the Tare Flag
				gs_test_w_buff[0] = CSI_TareCnt;

				//Send_Tarecount();
				//gs_test_w_buff[1] = Flag_Tare_Done;

				AUI_adc_stable        = 0;				// Rest the ADC stable Flag
				Tare_Flag=FALSE;
				Cycle_TMR         = 0;
				//Clr_WatchDog();     ////10032022
			}
		}
		Tare_Send_Time = CAN_WAIT_TIME * CAN_SlaveID;
		Tare_Send_Flag = 1;
    }

	/*if((Tare_Flag==FALSE)&&(Flag_CalOpr_Stage2 == 1)&&(Cycle_TMR == 0)) // Check if Tare Button is Released
	{
		Flag_CalOpr_Stage2 = 0;		// Reset the Inter-Lock of Tare calibration Operation
	}*/

/*The Following two condition used to generate calib count for weighing.*/
	if((Calibeate_Flag==TRUE)&&(Cycle_TMR == 0))				// Check if Calib Button is Pressed
	{
		Cycle_TMR = CALIB_CYCLE_TIME;	  // Set the Settling Cycle Timer for Calib operation
		Flag_Calib_Done    = 0;			 // Reset the calibration Done Flag
		Flag_CalOpr_Stage3 = 1;			// Set the Inter-Lock of Calib Operation

		while(Cycle_TMR)
		{
			read_adc();			      // Read Load Cell ADC count from CS5532
			check_stable();		     // Check if the Counts are Stable
			CSI_CalibSlope=0;
			if(AUI_adc_stable)
			{
				CSI_CalibCnt          = ASI_adc_count;		// Move Current ADC count to the Calib Count
				Flag_Calib_Done   = TRUE;		   // Set the Calib Done Flag
				gs_test_w_buff[1] = CSI_CalibCnt;
				//gs_test_w_buff[3] = Flag_Calib_Done;
				AUI_adc_stable        = 0;				         // Reset the ADC Stabel Flag
				CSI_CalibSlope = (CSI_CalibCnt - CSI_TareCnt)/1;		// 5 indicates 500gm
				Send_Calibcount();
				//Send_CalibSlope();
				gs_test_w_buff[2] = CSI_CalibSlope;
				Calibeate_Flag    = FALSE;
				Cycle_TMR         = 0;
   	// 			write_calib_data(gs_test_w_buff);
				///Clr_WatchDog();     ////10032022
			}
		}
		//Clr_WatchDog();    ///10032022
	}

/*	if((Calibeate_Flag==FALSE)&&(Flag_CalOpr_Stage3 == 1)&&(Cycle_TMR == 0))
	{
		Flag_CalOpr_Stage3 = 0;			// Reset the Inter-Lock of Calib Operation
	}*/
}
