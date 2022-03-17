/*
 * Stepper_Motor.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Pustake
 */

#include "r_cg_userdefine.h"
#include "r_cg_port.h"
#include "globals.h"
#include "Stepper_Motor.h"
#include "Timer.h"
#include "platform.h"
#include "r_cg_wdt.h"
#include "r_cg_cmt.h"
#include "Config_CMT2.h"
#include "Config_CMT3.h"
#include "Peripheral.h"
#include "can.h"
#include "Stepper_Motor_Varib.h"
#include "All_Header.h"
#include "can_Varib.h"


//unsigned int enable_buff[20];

unsigned int FB_Speed[4][220] = {{530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,529,529,528,528,527,527,526,526,525,525,524,524,523,523,522,522,521,521,520,520,519,519,518,518,517,517,516,516,515,515,514,514,513,513,512,512,511,511,510,510,509,509,508,508,507,507,506,506,505,505,504,504,503,503,502,502,501,501,500,500,499,499,498,498,497,497,496,496,495,495,494,494,493,493,492,492,491,491,490,490,489,489,488,488,487,487,486,486,485,485,484,484,483,483,482,482,481,481,480,480,479,479,478,478,477,477,476,476,475,475,474,474,473,473,472,472,471,471,470,470,469,469,468,468,467,467,466,466,465,465,464,464,463,463,462,462,461,461,460,460,459,459,458,458,457,457,456,456,455,455,454,454,453,453,452,452,451,451,450,450},
								{530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530},
								{830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830},
								{750,750,751,751,752,752,753,753,757,757,755,755,756,756,757,757,758,758,759,759,760,760,761,761,762,762,763,763,767,767,765,765,766,766,767,767,768,768,769,769,770,770,771,771,772,772,773,773,777,777,775,775,776,776,777,777,778,778,779,779,780,780,781,781,782,782,783,783,787,787,785,785,786,786,787,787,788,788,789,789,790,790,791,791,792,792,793,793,797,797,795,795,796,796,797,797,798,798,799,799,500,500,501,501,502,502,503,503,504,504,505,505,506,506,507,507,508,508,509,509,510,510,511,511,512,512,513,513,514,514,515,515,516,516,517,517,518,518,519,519,520,520,521,521,522,522,523,523,524,524,525,525,526,526,527,527,528,528,529,529,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530}};

unsigned int WB_Speed[4][220] = {{530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,529,529,528,528,527,527,526,526,525,525,524,524,523,523,522,522,521,521,520,520,519,519,518,518,517,517,516,516,515,515,514,514,513,513,512,512,511,511,510,510,509,509,508,508,507,507,506,506,505,505,504,504,503,503,502,502,501,501,500,500,499,499,498,498,497,497,496,496,495,495,494,494,493,493,492,492,491,491,490,490,489,489,488,488,487,487,486,486,485,485,484,484,483,483,482,482,481,481,480,480,479,479,478,478,477,477,476,476,475,475,474,474,473,473,472,472,471,471,470,470,469,469,468,468,467,467,466,466,465,465,464,464,463,463,462,462,461,461,460,460,459,459,458,458,457,457,456,456,455,455,454,454,453,453,452,452,451,451,450,450},
								{530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530},
								{830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830,830},
								{750,750,751,751,752,752,753,753,757,757,755,755,756,756,757,757,758,758,759,759,760,760,761,761,762,762,763,763,767,767,765,765,766,766,767,767,768,768,769,769,770,770,771,771,772,772,773,773,777,777,775,775,776,776,777,777,778,778,779,779,780,780,781,781,782,782,783,783,787,787,785,785,786,786,787,787,788,788,789,789,790,790,791,791,792,792,793,793,797,797,795,795,796,796,797,797,798,798,799,799,500,500,501,501,502,502,503,503,504,504,505,505,506,506,507,507,508,508,509,509,510,510,511,511,512,512,513,513,514,514,515,515,516,516,517,517,518,518,519,519,520,520,521,521,522,522,523,523,524,524,525,525,526,526,527,527,528,528,529,529,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530,530}};


//***********************************************************************************************************************
// * Function Name	: void power on homing(void)
// * Description	: function used to operate the Feed bucket.
//***********************************************************************************************************************
void Power_On_Homing(void)
{
	Flag_FB_HomIN = ~HIN_FB;
	Flag_WB_HomIN = ~HIN_WB;

	if((Flag_FB_HomIN == 0)||(HIN_FB == 1))
	{
		Flag_FB_Trig   = 1;
		SUI_homing_flag_fb = 1;
		CLK_FB         = 0;
	}

	if((Flag_WB_HomIN == 0)||(HIN_WB == 1))
	{
		Flag_WB_Trig   = 1;
		SUI_homing_flag_wb = 1;
		CLK_WB         = 0;
	}

	Flag_FB_HomIN = 0;
	Flag_WB_HomIN = 0;
	GUI_state=5;
}

//***********************************************************************************************************************
// * Function Name	: void Trigger_FB(void)
// * Description	: function used to operate the Feed bucket.
//***********************************************************************************************************************
void Trigger_FB(void)
{
	//Clr_WatchDog();   //10032022


	if(SUI_homing_flag_fb == 1)
	{
		ENB_FB  = 1;
		CLK_FB ^= 1;

		if(HIN_FB == 0)
		{
			FB_Clk_Pulses  = 0;
			ENB_FB         = 0;
			Flag_FB_Trig   = 0;
			SUI_homing_flag_fb = 0;
			DSidx_FB       = 0;
			CLK_FB         = 0;
		}
	}
	else if((Flag_FB_Trig == 1) && (FB_OD_TMR == 0) && (FB_OT_TMR == 0))// && start_wb_flag == 1)
	{
		CMT2.CMCOR = FB_Speed[MotoPro_FB][DSidx_FB];

		if((FB_Clk_Pulses < MAXPULSES) && (ENB_FB == 1))
		{
			DSidx_FB++;
			shift_speed_row_FB++;

			if(shift_speed_row_FB == 199)
			{
				MotoPro_FB = 1;
				DSidx_FB   = 0;
			}
			else if(shift_speed_row_FB == 399)    //399
			{
				//DIR_FB = 1;
				MotoPro_FB = 2;
				DSidx_FB   = 0;
			}
			else if(shift_speed_row_FB == 599)   //599
			{
				MotoPro_FB = 3;
				DSidx_FB   = 0;
			}
		}
	//if((Flag_FB_Trig == 1)&&(Flag_FB_Trig_Edge == 0)&&(Flag_FB_HomIN == 1)) // Check if FeedBucket trigger flag is set and Edge flag is reset
	if((Flag_FB_Trig == 1)&&(Flag_FB_Trig_Edge == 0))
	{
	//	fb_time_taken_counter=0;
	//	fb_time_taken_flag=1;
		enable_time_count = 0;
		Flag_FB_Trig_Edge = 1;	// Set the Edge flag of the FeedBucket Trigger Flag
		FB_OD_TMR         = FB_OD_Time;	// Set the open Delay for the FeedBucket
	//	Flag_FB_HomIN = 0;		// Force Homing flag of the Feed Bucket to 0 for next event

	}
	else if((FB_OD_TMR == 0)&&(Flag_FB_Trig == 1)&&(Flag_FB_OD_TMR == 0))	//
	{
		FB_Clk_Pulses   = 0;
		ENB_FB          = 1;      // for old stepper driver
		shift_speed_row_FB = 0;
		enb_flag        = 1;
		FB_OT_TMR       = 0;
		Flag_FB_Stage1  = 0;
		Flag_FB_Stage3  = 0;
		Flag_FB_OD_TMR  = 1;
		//ENB_FB        = 0;      // for new stepper driver
	}
	if((FB_Clk_Pulses < MAXPULSES)&&(FB_OT_TMR == 0)&&(ENB_FB == 1)) // for old stepper driver
	//if((FB_Clk_Pulses <= MAXPULSES)&&(FB_OT_TMR == 0)&&(ENB_FB == 0)) // for new stepper driver
	//if((FB_Clk_Pulses <= MAXPULSES)&&(FB_OT_TMR == 0)&&(ENB_FB == 1)&&(Flag_FB_OD_TMR==1)&&(enb_timer==1))
	{
		CLK_FB ^= 1;
		//CLK_FB = 1;

		if(CLK_FB == 1)
		{
			FB_Clk_Pulses++;
	//		FB_Angle_Ptr++;
		}
	}
	if((FB_Clk_Pulses >= 200)&&(Flag_FB_Stage1 == 0))	//300//fire timer open timer at full open (180Deg)
	{
		FB_OT_TMR      = FB_OT_Time;
	//	DIR_FB = 1;
		Flag_FB_OT_TMR = 1;
		Flag_FB_Stage1 = 1;
	}
	if((FB_OT_TMR == 0)&&(Flag_FB_OT_TMR == 1))
	{
		//DIR_FB = 1;
		Flag_FB_Stage2 = 1;
		Flag_FB_Status = 1;
		Flag_FB_OT_TMR = 0;
	}
	if((FB_Clk_Pulses > 300)&&(Flag_FB_Stage2 == 1))   //400
	{
		Flag_FB_Stage3 = 1;
		Flag_FB_Stage2 = 0;
	}

	if(((HIN_FB == 0)&&(Flag_FB_Stage3 == 1))||(FB_Clk_Pulses >= MAXPULSES))		//check homing after stage 3
	//if(((Flag_FB_Stage3 == 1))&&(FB_Clk_Pulses >= MAXPULSES))
	//if(((HIN_FB == 0)&&(Flag_FB_Stage3 == 1)))//||(FB_Clk_Pulses >= MAXPULSES))		//check homing after stage 3
	{
	   //	Clr_WatchDog();         //10032022
		CMT2.CMCOR = _0289_CMT2_CMCOR_VALUE;
		DIR_FB = 0;
		ENB_FB             = 0;  // for old stepper driver
		enb_flag           = 0;
		enable_buff[enb_i] = enable_time_count;
		//enable_buff[enb_i] = FB_Clk_Pulses;
		enb_i++;
		enable_time_count  = 0;
		FB_Clk_Pulses      = 0;
		MotoPro_FB         = 0;
		DSidx_FB           = 0;
		CLK_FB             = 0;
		shift_speed_row_FB = 0;
	    Flag_FB_OD_TMR     = 0;
		Flag_FB_OT_TMR     = 0;
		Flag_FB_Stage1     = 0;
		Flag_FB_Stage2     = 0;
		Flag_FB_Stage3     = 0;
		Flag_FB_Trig       = 0;
		shift_speed_row_FB = 0;
		fb_time_taken_flag = 0;

	}

 }

}

void Trigger_WB(void)
{
	//Clr_WatchDog();       ///10032022

	if(SUI_homing_flag_wb == 1)
	{
		ENB_WB  = 1;
		CLK_WB ^= 1;

		if(HIN_WB == 0)
		{
			WB_Clk_Pulses      = 0;
			ENB_WB             = 0;
			Flag_WB_Trig       = 0;
			SUI_homing_flag_wb     = 0;
			DSidx              = 0;
			shift_speed_row_WB = 0;
			CLK_WB             = 1;
		}

	}
	else if((Flag_WB_Trig == 1)&&(WB_OD_TMR == 0)&&(WB_OT_TMR == 0))// && start_wb_flag == 1)
	{
		CMT3.CMCOR = WB_Speed[MotoPro][DSidx];

		if(WB_Clk_Pulses < MAXPULSES && ENB_WB ==1)
		{
			DSidx++;
			shift_speed_row_WB++;

			if(shift_speed_row_WB == 199)
			{
				MotoPro = 1;
				DSidx   = 0;
			}
			else if(shift_speed_row_WB == 399)  //399
			{
			//	DIR_WB = 1;
				MotoPro = 2;
				DSidx   = 0;
			}
			else if(shift_speed_row_WB == 599)  //599
			{
				MotoPro = 3;
				DSidx   = 0;
			}
		}

	//if((Flag_WB_Trig == 1)&&(Flag_WB_Trig_Edge == 0)&&(Flag_WB_HomIN  == 1)) // Check if weighBucket trigger flag is set and Edge flag is reset
	if((Flag_WB_Trig == 1)&&(Flag_WB_Trig_Edge == 0))
	{
	//	wb_time_taken_flag=1;
	//	wb_time_taken_counter=0;

		Flag_WB_Trig_Edge     = 1;	// Set the Edge flag of the weighBucket Trigger Flag
		Flag_WB_OT_TMR        = 0;
		WB_OD_TMR             = WB_OD_Time;	// Set the open Delay for the weighBucket
//		Flag_WB_HomIN         = 0;		// Force Homing flag of the weigh Bucket to 0 for next event
		Flag_WB_OD_TMR        = 0;
	//	ENB_WB                = 1;
//		time_to_start_fb_flag = 0;
	}
	else if((WB_OD_TMR == 0)&&(Flag_WB_Trig == 1)&&(Flag_WB_OD_TMR == 0))	//
	{
		WB_Clk_Pulses  = 0;
		ENB_WB         = 1;
		shift_speed_row_WB = 0;
		Flag_DumpCyc   = 1;
		WB_OT_TMR      = 0;
		Flag_WB_Stage1 = 0;
		Flag_WB_Stage3 = 0;
		Flag_WB_OD_TMR = 1;
	}

	if((WB_Clk_Pulses < MAXPULSES)&&(WB_OT_TMR == 0)&&(ENB_WB == 1)&& (ot_flag == 0))   // for old stepper drive
	//if((WB_Clk_Pulses <= MAXPULSES)&&(WB_OT_TMR == 0)&&(ENB_WB == 0))     // for new stepper drive
	{
		if(Flag_DumpCyc)
		{
			CLK_WB ^= 1;
		}

		if(CLK_WB == 1)
		{
			WB_Clk_Pulses++;
		//	WB_Angle_Ptr++;
		}
	}

	if((WB_Clk_Pulses >= 200)&&(Flag_WB_Stage1 == 0))	//fire timer open timer at full open (180Deg)
	{
//		Flag_WB_Status=0;
		WB_OT_TMR      = WB_OT_Time;
//		DIR_WB = 1;
		Flag_WB_OT_TMR = 1;
		ot_flag        = 1;
		Flag_WB_Stage1 = 1;
	}

	if((WB_OT_TMR == 0)&&(Flag_WB_OT_TMR == 1))
	{
		Flag_WB_Stage2 = 1;
//		Flag_WB_Status = 1;
		Flag_WB_OT_TMR = 0;
	}

	if((WB_Clk_Pulses > 300)&&(Flag_WB_Stage2 == 1)&&(Flag_WB_Stage3 == 0))
	{
		Flag_WB_Stage3 = 1;
	}

	if(((HIN_WB == 0)&&(Flag_WB_Stage3 == 1))||(WB_Clk_Pulses >= MAXPULSES))		//check homing after stage 3
	//if(((Flag_WB_Stage3 == 1))&&(WB_Clk_Pulses >= MAXPULSES))		//check homing after stage 3
	{
		//Clr_WatchDog();      //10032022

		CMT3.CMCOR = _01F3_CMT3_CMCOR_VALUE;
	//	DIR_WB = 0;
	//	ENB_WB             = 1;        // for new stepper drive
		ENB_WB             = 0;        // for old stepper drive

		WB_Clk_Pulses      = 0;
		shift_speed_row_WB = 0;
		MotoPro            = 0;
		DSidx              = 0;
		Flag_WB_Trig_Edge  = 0;
		CLK_WB             = 0;
		Flag_WB_OT_TMR     = 0;
		Flag_WB_Stage2     = 0;
		Flag_WB_Stage3     = 0;
		Flag_DumpCyc       = 0;
		Flag_WB_Trig       = 0;
		wb_time_taken_flag = 0;
		//Clr_WatchDog();       ///10032022
	}
 }

}


