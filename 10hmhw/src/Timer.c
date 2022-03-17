/*
 * Timer.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */


#include "Timer.h"
#include "r_cg_wdt.h"
#include "r_cg_cmt.h"
#include "Config_ICU.h"
#include "r_cg_port.h"
#include "Config_CMT1.h"
#include "Config_WDT.h"
#include "globals.h"
#include  "Config_CMT1.h"
#include "Config_MTU0.h"
#define VAR_PWM
#include "PWM.h"
#include "RUN_OP.h"
#include "r_cg_userdefine.h"
#include "ADC_CS5532.h"
#include "can.h"
#include "platform.h"
#include "Stepper_Motor.h"
#include "Calibration_Varib.h"
#include "Stepper_Motor_Varib.h"
#include "can_Varib.h"

#include "All_Header.h"
////zcdip////
//void Clr_WatchDog(void);

//extern unsigned int WB_OT_TMR;
extern _Bool ot_flag;


extern void PWM_Stop();
extern void PWM_Start();

void mS_Delay(unsigned int mS)
{
	mS_Cnt = mS;

	while(mS_Cnt)
	{
		Clr_WatchDog();		// Used to clear watch dog timer
	}
}

void Timer0_IT_ISR(void)
{

	if(run_time_flag == 1)
		run_time_taken++;

	if(ot_flag == 1 && WB_OT_TMR == 0 )
		ot_flag = 0;

	if(Tare_Send_Time)
		Tare_Send_Time--;

	if(time_to_start_fb_flag)
		time_to_start_fb--;

	if(time_to_start_fb_flag == 1 && time_to_start_fb == 0 )
	{
		Head_In_Recharge      = 0;

		if(Flag_Tare_Done)
		{
			Flag_WB_Status    = 1;
		}

		time_to_start_fb_flag = 0;
	}

	//if(Run_Cycle_Time_Flag)     ///2/3/22
	//	Run_Cycle_Counter++;     ///2/3/22

	if(lf_time_taken_flag)
		lf_time_taken_counter++;

	if(fb_time_taken_flag)
		fb_time_taken_counter++;

	if(wb_time_taken_flag)
		wb_time_taken_counter++;

	//if((Settle_TMR) && (Flag_Run==1))
	if((Settle_TMR))
		Settle_TMR--;

	if(msflag==0)
	 msflag=1;

	else if(msflag)
	{
		if(enb_flag == 1)
		{
			enable_time_count++;
		}
		msflag = 0;
		ad_time_out_flag = 1;



		if(mS_Cnt) 			mS_Cnt--;
	//	if(Settle_TMR)		Settle_TMR--;
		if(WB_OD_TMR)		WB_OD_TMR--;
		if(WB_OT_TMR)		WB_OT_TMR--;
		if(FB_OD_TMR)		FB_OD_TMR--;
		if(FB_OT_TMR)		FB_OT_TMR--;
		if(Cycle_TMR)		Cycle_TMR--;
		if(SD_LF_TMR)		SD_LF_TMR--;
		//if(SetTimer)		SetTimer--;
		if(t00)	t00--;
		if(t01)	t01--;
		if(t02)	t02--;
 		if(t03)	t03--;
 		if(mscount>0)
		{
			mscount--;
			if(mscount==0)
			{
				mscount    = 100;
				ms100_flag = 1;
			}
		}
	}
}



//*************************
//  Watchdog timer
//*********************8
/*void Clr_WatchDog(void)
{
	R_Config_WDT_Restart();
}
*/
void Init_Vals(void)
{
	mscount = 100;
	GUI_state = 2;
}


//***********************************************************************************************************************
// * Function Name	: void Timer1_FAngle_ISR(void)
// * Description	: function contains the ISR body of the Timer1,
//					  it is used to generate firing angle vibrator.
//***********************************************************************************************************************
void Timer1_FAngle_ISR(void)
{
	//Clr_WatchDog();		        ///10032022 // Clear and Reset the Watch Timer
	R_Config_CMT1_Stop();		 // The function used to stop Compare match Timer1
	Pulses_SCR = 0;				// Set the Firing Pulse count to Zero.

	if(Initial_Vibrator_Flag==1 && (VBT_Cntr <= VBRT_Cyl-2))
		PWM_Start();				// Start the PWM triggering logic
	else
	{
		R_Config_ICU_Create();
		R_Config_ICU_IRQ0_Start();


	}
	Initial_Vibrator_Flag = 1;
}

//***********************************************************************************************************************
// * Function Name	: void Timer2_FBucket_ISR(void)
// * Description	: function contains the ISR body of the Timer2,
//					  it is used to generate clock pulses for feed Bucket.
//***********************************************************************************************************************
void Timer2_FBucket_ISR(void)
{
	//Clr_WatchDog();		///10032022// Clear and Reset the Watch Timer
	Trigger_FB();		// The function used to decide rotation pattern of the feed Bucket

}


//***********************************************************************************************************************
// * Function Name	: void Timer3_WBucket_ISR(void)
// * Description	: function contains the ISR body of the Timer3,
//					  it is used to generate clock pulses for Weighing Bucket.
//***********************************************************************************************************************
void Timer3_WBucket_ISR(void)
{
	//Clr_WatchDog();               ///032022		/10// Clear and Reset the Watch Timer
	Trigger_WB();		// The function used to decide rotation pattern of the Weighing Bucket
}



////////zcdip/////


void ISR_ZCIP(void)
{
	/*The below pin used to check the status of the IRQ on port pin used to check the noise*/

	//Clr_WatchDog();                     //10032022
	CPin      ^= 1;					// Reflect the status of External Interrupt Request on port // @suppress("Field cannot be resolved")
	VBRT_Half ^= 1;

	if(VBRT_Half)
	{
		if(VBT_Cntr > 0)
		{
			lf_time_taken_flag=1;
			VBT_Cntr--;							// Decrease the vibration counter
			CMT1.CMCOR = Firing_Angle;			// The value of the Timer as of Firing angle of Vibrater
			R_Config_ICU_IRQ0_Stop();			// Stop the External Interrupt Request
			R_Config_CMT1_Start();				// Start the Compare and Match Timer
		}
		else if(VBT_Cntr==0)
		{
			lf_time_taken_flag=0;
		}
	}

	//Clr_WatchDog();      ///10032022
}
