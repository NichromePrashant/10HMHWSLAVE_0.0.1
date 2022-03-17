/*
 * RUN_OP.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Pustake
 */

#include "RUN_OP.h"
#include "globals.h"
#include "Peripheral.h"
#include "r_cg_userdefine.h"
#include "platform.h"
#include "r_cg_port.h"
#include "Timer.h"
#include "can.h"
#include "RUN_OP_Varib.h"
#include "Stepper_Motor_Varib.h"
#include "Calibration_Varib.h"
//#include "r_cg_userdefine.h"
#include "can_Varib.h"
#include "All_Header.h"


//extern unsigned int Actual_Dump_Counter;
//***********************************************************************************************************************
// * Function Name	: void RunOperation(void)
// * Description	: function defines the operation run sequence of the system.
//***********************************************************************************************************************
void RunOperation(void)
{
	//Clr_WatchDog();   //10032022

	if(Flag_Run == 1  && Auto_Tare_Flag == 0 ) // Check for the Run Flag
	{
		if((Head_In_Combi)&&(Flag_RunCyc == 0)&&(Flag_Run_Stage1 == 0))
		{

			if(HIN_WB == 0 && ENB_WB == 0)
			{
				SUI_homing_flag_wb    = 0;
				Flag_WB_Trig 	  = 1;		// Trigger WeighBucket of the Systems
				Flag_WB_Trig_Edge = 0;
				CLK_WB            = 1;
				Flag_DumpCyc 	  = 1;		// Decode weather to Run the Weighing Bucket

				Actual_Dump_Counter++;

				if(Actual_Dump_Counter < Auto_Zero_Interval)
				{
					time_to_start_fb      = FB_WAIT_TIME;
					time_to_start_fb_flag = 1;
				}

				Flag_Run_Stage5 = 0;		// Reset the Stage 5 complition Flag
				Head_In_Combi   = 0;

				Flag_WB_Status  = 0;
				Flag_FB_Status  = 0;



			if(Actual_Dump_Counter >= Auto_Zero_Interval)
			{
				Flag_Tare_Done      = 0;
			//	Actual_Dump_Counter = 0;
			//	Auto_Tare();
				Flag_Run_Stage1     = 0;
				Flag_RunCyc         = 0;
				Auto_Tare_Flag      = 1;
				Flag_Run            = 0;     // 14/12/21
				Flag_RunOperation   = 0;     // 14/12/21
			}
			else
			{
				Flag_Run_Stage1 = 1;		// Inter-lock of Stage 1 complition flag
				Flag_RunCyc 	= 1;		// Inter-lock of Run Cycle Trigger
			}
			}
			else
			{
				Flag_Run_Stage4 = 1;
				Flag_Run_Stage5 = 0;
				VBT_Cntr        = 0;

				if(SUI_homing_flag_wb == 0 && Flag_WB_Trig == 0)
				{
					SUI_homing_flag_wb = 1;
					Flag_WB_Trig   = 0;
				}
			}
		}

		if((Head_In_Recharge)&&(Flag_RunCyc == 0)&&(Flag_Run_Stage1 == 0)&&(Flag_Tare_Done))
		{
		//	CurrentWt = 0;				// Send the Current Wt is Zero till Setting Timer
			Flag_WB_Trig_Edge     = 0;
			WB_Angle_Ptr          = 0;
//			Flag_WB_Trig 	      = 1;		// Trigger the Weighing Bucket of the Systems
			time_to_start_fb      = FB_WAIT_TIME;
			time_to_start_fb_flag = 1;
			//Flag_RechCyc        = 1;

			Flag_DumpCyc 	      = 0;		// Decode weather to Run the Weighing Bucket
	//		Flag_WB_HomIN 	      = 0;		// Force Zero to Weighing Bucket Homing Flag to get the Next Homing Signal
			Flag_RunCyc 	      = 1;		// Inter-lock of Run Cycle Trigger
	//		Flag_WtReady 	      = 0;		// Indicate Weight is not ready to send
			Flag_Run_Stage5       = 0;		// Reset the Stage 5 complition Flag
			Flag_Run_Stage1       = 1;		// Inter-lock of Stage 1 complition Flag
			Flag_Run_Stage2       = 0;
		  //Head_In_Recharge      = 0;

			Flag_WB_Status        = 0;
			Flag_FB_Status        = 0;
		}

		//if((Flag_RunCyc == 1)&&(Flag_Run_Stage1 == 1)&&(Flag_Run_Stage2 == 0)&&(Flag_WB_Stage2 == 1))
		if((Flag_RunCyc == 1)&&(Flag_Run_Stage1 == 1)&&(Flag_Run_Stage2 == 0)&&(Flag_WB_Status == 1)&&(Flag_Tare_Done))
		{
			if(HIN_FB == 0 && ENB_FB == 0)
			{
				SUI_homing_flag_fb  = 0;
				Flag_FB_Trig    = 1;			  // Trigger FeedBucket of the System
				CLK_FB          = 1;
		//		Flag_FB_HomIN   = 0;			// Force Zero to FeedBucket Homing Flag to get the Next Homing Event
				Flag_Run_Stage2 = 1;		   // Inter-Lock of Stage 2 complition Flag
				Flag_Run_Stage3 = 0;
			}
			else
			{
				Flag_Run_Stage4 = 1;
				Flag_Run_Stage5 = 0;
				VBT_Cntr        = 0;

				if(SUI_homing_flag_fb == 0 && Flag_FB_Trig == 0)
				{
					SUI_homing_flag_fb = 1;
					Flag_FB_Trig   = 0;
				}
			}
		}
		//if((Flag_RunCyc == 1)&&(Flag_Run_Stage2 == 1)&&(Flag_Run_Stage3 == 0)&&(Flag_FB_Stage2 == 1))
		if((Flag_RunCyc == 1)&&(Flag_Run_Stage2 == 1)&&(Flag_Run_Stage3 == 0)&&(Flag_FB_Status == 1))
		{
			SD_LF_TMR  = SD_LF_Time;		// Start Delay of the Linear Feeder
			Settle_TMR = Settle_Time;
			wt_calculated_flag = 0;
			calibration_wt_flag = 0;

			Flag_Run_Stage3 = 1;		// Inter-Lock of Stage 3 complition Flag
			Flag_Run_Stage4 = 0;
		}
		if((Flag_RunCyc == 1)&&(Flag_Run_Stage3 == 1)&&(Flag_Run_Stage4 == 0)&&(SD_LF_TMR == 0))
		{
			VBT_Cntr = VBRT_Cyl;		 // Trigger the Vibrator just by loading the Number of Firing Pulses
			Flag_Run_Stage4 = 1;		// Inter-Lock of Stage 4 complition Flag
			Flag_Run_Stage5 = 0;
		}
		//if((Flag_RunCyc == 1)&&(Flag_Run_Stage4 == 1)&&(Flag_Run_Stage5 == 0)&&(Settle_TMR == 0))
		if((Flag_RunCyc == 1)&&(Flag_Run_Stage4 == 1)&&(Flag_Run_Stage5 == 0))    //&&(VBT_Cntr == 0)
		{
		  //Settle_TMR = Settle_Time;
			Flag_WtReady          = 0;
		//	Flag_WtReady 	      = 1;		// Set the Weight Ready Flag transmition
			Start_Weight_Cal_Flag = 0;
		//	Flag_Run 		      = 0;		// Terminate the Run Process for Next cycle
			Flag_RunCyc	 	      = 0;		// Reset the RunCycle InterLcok of the Run Cycle
			Flag_Run_Stage1       = 0;		// Reset the All the Run Stage flag for Next Cycle
			Flag_Run_Stage2       = 0;
			Flag_Run_Stage3       = 0;
			Flag_Run_Stage4       = 0;
			Flag_Run_Stage5       = 1;
			Flag_RechCyc          = 0;
			Flag_FB_Status        = 0;
			Flag_WB_Status        = 0;
			Flag_RunOperation     = 0;
			GUI_run_time_flag = 0;

		}
	}

	//Clr_WatchDog();      //10032022


}
