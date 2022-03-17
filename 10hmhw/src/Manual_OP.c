/*
 * Manual_OP.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Pustake
 */

#include "globals.h"
#include "Peripheral.h"
#include "r_cg_userdefine.h"
#include "can.h"
#include "Stepper_Motor.h"
#include "Manual_OP.h"
#include "RUN_OP.h"
#include "Manual_OP_Varib.h"
#include "Stepper_Motor_Varib.h"
#include "All_Header.h"

//extern unsigned int	GUI_Cycle_TMR;
//***********************************************************************************************************************
// * Function Name	: void ManualOperation(void)
// * Description	: function defines the manual triggering logic of the mutli head weigher(system)
//***********************************************************************************************************************
void ManualOperation(void)
{
	Head_In_Recharge=0;

	if((ManOpr_FB_Flag==1)&&(FB_Clk_Pulses==0)&&(t00 == 0))		// Check if FeedBucket Button is Pressed
	{
         //	Flag_FB_HomIN=1;
		if(HIN_FB == 0  && ENB_FB == 0 )
		{
			SUI_homing_flag_fb    = 0;
			Flag_FB_Trig      = 1;				// Trigger the FeedBucket of the System
			Flag_FB_Trig_Edge = 0;
			CLK_FB            = 1;
			t00 = FB_CYCLE_TIME;						// Wait for next cycle of the FeedBucket
		}
		else
		{
			if(SUI_homing_flag_fb == 0 && Flag_FB_Trig == 0)
			{
				SUI_homing_flag_fb = 1;
				Flag_FB_Trig   = 0;
				t00 = FB_CYCLE_TIME;
			}
		}
	}

	if((ManOpr_WB_Flag==1)&&(WB_Clk_Pulses==0)&&(t01 == 0))		// Check if weighBucket Button is Pressed
	{
	//	Flag_WB_HomIN = 1;
		if(HIN_WB == 0 && ENB_WB == 0 )
		{
			SUI_homing_flag_wb    = 0;
			Flag_WB_Trig      = 1;				// Trigger the WeighBucket of the System
		//	WB_Angle_Ptr       = 0;
			Flag_WB_Trig_Edge = 0;
			CLK_WB            = 1;
		//	Flag_DumpCyc      = 1;				// Decode weather to Run the Weighing Bucket
			Flag_RechCyc      = 0;
			Rech_dumy_clk     = 0;
			t01 = WB_CYCLE_TIME;						// Wait for Next Cycle of the WeighBucket
		}
		else
		{
			if(SUI_homing_flag_wb == 0 && Flag_WB_Trig == 0)
			{
				SUI_homing_flag_wb = 1;
				Flag_WB_Trig   = 0;
				t01 = WB_CYCLE_TIME;
			}
		}
	}

	if((ManOpr_Vib_Flag==1)&&(VBT_Cntr == 0)&&(t02 == 0))			// Check if Linear Feeder Button is Pressed
	{
		VBT_Cntr = VBRT_Cyl;			// Load the Vibration Counts to the Vibration Counter
		t02      = VIB_CYCLE_TIME;						// Wait for Next Cycle of the Linear Feeder
	}

	if((ManOpr_SS_Flag==1)&&(Cycle_TMR == 0)&&(Flag_SingleCycle == 0))		// Check if Single cycle Button is pressed
	{
		Flag_ManOpr_Stage1 = 0;		// Reset the Flags of Manual Operation Stages
		Flag_ManOpr_Stage2 = 0;
		Flag_ManOpr_Stage3 = 0;
		Flag_ManOpr_Stage4 = 0;
		Flag_SingleCycle   = 1;	   // Set the single Cycle Flag for complete
		Cycle_TMR = SS_CYCLE_TIME;		  // Wait for Next Cycle
	}

	else if((ManOpr_SS_Flag==0)&&(Cycle_TMR == 0)&&(Flag_SingleCycle == 1))		//rdata[0]&0x10)!= 0x10 Check if Single Cycle Button is released
	{
		Flag_SingleCycle = 0;			// Reset the Single Cycle flag of the Manual operation
	}

	if((ManOpr_CS_Flag==1)&&(Cycle_TMR == 0))		// Check if Continuous Cycle Button is pressed
	{

		Flag_ManOpr_Stage1 = 0;			// Reset the Flags of Manual Operation stages
		Flag_ManOpr_Stage2 = 0;
		Flag_ManOpr_Stage3 = 0;
		Flag_ManOpr_Stage4 = 0;
		Cycle_TMR = CS_CYCLE_TIME;				// Wait for Next Cycle
	}

	if((Flag_ManOpr_Stage1 == 0)&&(Cycle_TMR))
	{

		if(HIN_WB == 0 && ENB_WB == 0)
		{
			SUI_homing_flag_wb     = 0;
			Flag_WB_Trig       = 1;				 // Trigger the WeighBucket of the Systems
			CLK_WB             = 0;
			Flag_DumpCyc       = 1;				// Decode weather to Run the Weighing Bucket
			Flag_ManOpr_Stage1 = 1;			// Set the Inter-Lock of Stage 1 for Manual Operation
		}
		else
		{
			if(SUI_homing_flag_wb == 0 && Flag_WB_Trig == 0)
				SUI_homing_flag_wb = 1;
		}
	}

	if((Flag_ManOpr_Stage1 == 1)&&(Flag_ManOpr_Stage2 == 0)&&(Flag_WB_Stage2 == 1)&&(Cycle_TMR))
	{
		if(HIN_FB == 0 && ENB_FB == 0)
		{
			SUI_homing_flag_fb     = 0;
			Flag_FB_Trig       = 1;				 // Triiger the FeedBucket of the System
			CLK_FB             = 0;
			Flag_ManOpr_Stage2 = 1;			// Set the Inter-Lock of Stage 2 for Manual Operation
		}
		else
		{
			if(SUI_homing_flag_fb == 0 && Flag_FB_Trig == 0)
				SUI_homing_flag_fb = 1;
		}
	}

	if((Flag_ManOpr_Stage2 == 1)&&(Flag_ManOpr_Stage3 == 0)&&(Flag_FB_Stage2 == 1)&&(Cycle_TMR))
	{
		SD_LF_TMR          =  SD_LF_Time;    // Start Delay of the Linear Feeder
		Flag_ManOpr_Stage3 = 1;			   // Set the Inter-Lock of Stage 3 for Manual Operation
	}

	if((Flag_ManOpr_Stage3 == 1)&&(Flag_ManOpr_Stage4 == 0)&&(SD_LF_TMR == 0)&&(Cycle_TMR))
	{
		VBT_Cntr           = VBRT_Cyl;
		Flag_ManOpr_Stage4 = 1;
	}

}
