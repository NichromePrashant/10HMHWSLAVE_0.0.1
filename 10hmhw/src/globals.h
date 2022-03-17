/*
 * Global.h
 *
 *  Created on: Feb 14, 2022
 *      Author: Pustake
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#ifndef GLOBAL_VAR
# define _GLOBAL extern
# define _GLOBAL_INIT(x)
#else
# define _GLOBAL
# define _GLOBAL_INIT(x)  = x
#endif

#define TRUE        (1)
#define FALSE       (0)

#define MAXPULSES   400

#define FB_WAIT_TIME 540

#define CAN_WAIT_TIME 5

#define FB_CYCLE_TIME   2000
#define WB_CYCLE_TIME   2000
#define VIB_CYCLE_TIME  2000
#define SS_CYCLE_TIME   2000
#define CS_CYCLE_TIME   2000

#define CALIB_CYCLE_TIME   5000
#define AUTO_TARE_CYCLE_TIME   2000

#define MAX_LONGTIME_NOT_IN_COMBI_COUNT 20




void Clr_WatchDog(void);



_GLOBAL unsigned int CAN_SlaveID _GLOBAL_INIT(0);
//_GLOBAL volatile uart_msg_t g_uart_msg = MSG_NONE;
_GLOBAL unsigned int t00,t01,t02,t03;
_GLOBAL unsigned int GUI_Error _GLOBAL_INIT(0);
_GLOBAL unsigned int 	VBT_Cntr;				// Actual variable to decide number cycle to be fired
_GLOBAL unsigned char 	Pulses_SCR;				// Number of Pulses of PWM fired to trigger SCR
_GLOBAL unsigned int	SD_LF_TMR;				// Linear feeder Start Delay Timer
_GLOBAL unsigned int	SD_LF_Time _GLOBAL_INIT(5);			// Start Delay of Time of the Linear feeder
_GLOBAL unsigned int 	VBRT_Cyl _GLOBAL_INIT(5);			// Number cycle to be fired
_GLOBAL signed int 	Firing_Angle _GLOBAL_INIT(5500);	// Decide firing angle of the SCR, in multiple of 1 microseconds
_GLOBAL _Bool VBRT_Half;

_GLOBAL unsigned int Cycle_TMR;			// Single Cycle Timer
_GLOBAL unsigned int Settle_TMR _GLOBAL_INIT(0);
_GLOBAL unsigned int Settle_Time _GLOBAL_INIT(200);	// Settling Time in Run Cycle for Weight calculation
_GLOBAL unsigned int Rech_dumy_clk;
_GLOBAL unsigned int Initial_Vibrator_Flag;



/////can//////
_GLOBAL _Bool           Head_In_Combi;
_GLOBAL _Bool           Flag_Run;
_GLOBAL _Bool           Flag_RunCyc;
_GLOBAL _Bool           Flag_Run_Stage1;
_GLOBAL _Bool           Flag_Run_Stage2;
_GLOBAL _Bool           Flag_Run_Stage3;
_GLOBAL _Bool           Flag_Run_Stage4;
_GLOBAL _Bool           Flag_Run_Stage5;
_GLOBAL _Bool           Head_In_Recharge;
_GLOBAL _Bool           Flag_RunOperation;
_GLOBAL _Bool           Start_Weight_Cal_Flag;
_GLOBAL unsigned int    GUI_run_time_flag,GUI_run_time_taken;

_GLOBAL unsigned int    GUI_state _GLOBAL_INIT(0);


/////////calibration/////
_GLOBAL _Bool Calibeate_Flag;
_GLOBAL signed int	CSI_CalibCnt;
_GLOBAL signed int	CSI_CalibSlope;
_GLOBAL signed int 	CSI_TareCnt _GLOBAL_INIT(0);
_GLOBAL _Bool Flag_Tare_Done;
_GLOBAL _Bool Dump_Flag;
_GLOBAL _Bool Tare_Flag;
_GLOBAL unsigned int Tare_Send_Time,Tare_Send_Flag;
_GLOBAL _Bool ot_flag;
_GLOBAL _Bool flag_home_wb,flag_home_fb;
//_GLOBAL _Bool Flag_CalibOperation;
_GLOBAL _Bool Flag_CalibOperation_no;

//_CALIBRATION _Bool Flag_Tare_Done;
_GLOBAL _Bool Flag_Calib_Done;
_GLOBAL _Bool Flag_CalOpr_Stage1;
_GLOBAL _Bool Flag_CalOpr_Stage2;
_GLOBAL _Bool Flag_CalOpr_Stage3;

//////stepper//////
_GLOBAL _Bool Flag_FB_Stage1;
_GLOBAL _Bool Flag_FB_Stage2;
_GLOBAL _Bool Flag_FB_Stage3;
_GLOBAL unsigned int DSidx, DSidx_FB,start_wb_flag,clk_wb_flag;
_GLOBAL unsigned int SUI_homing_flag_fb,SUI_homing_flag_wb;
_GLOBAL unsigned int shift_speed_row_WB,shift_speed_row_FB;



_GLOBAL _Bool Flag_FB_Trig;				// FeedBucket Run Flag
_GLOBAL _Bool Flag_FB_Trig_Edge;		// Check edge of the feedBucket Run Flag
_GLOBAL _Bool Flag_FB_OD_TMR;
_GLOBAL _Bool Flag_FB_OT_TMR;

_GLOBAL _Bool Flag_FB_HomIN;
_GLOBAL _Bool Flag_FB_Status;


_GLOBAL _Bool Flag_WB_Trig;				// Weighing Bucket Run Flag
_GLOBAL _Bool Flag_WB_Trig_Edge;		// Check edge of the WeighingBucket Run Flag
_GLOBAL _Bool Flag_WB_OD_TMR;
_GLOBAL _Bool Flag_WB_OT_TMR;
_GLOBAL _Bool Flag_WB_Stage1;
_GLOBAL _Bool Flag_WB_Stage2;
_GLOBAL _Bool Flag_WB_Stage3;
_GLOBAL _Bool Flag_WB_HomIN;

_GLOBAL _Bool Flag_DumpCyc;
_GLOBAL _Bool Flag_RechCyc;
_GLOBAL _Bool Flag_WB_Status;

_GLOBAL _Bool ot_flag;


_GLOBAL unsigned int FB_Clk_Pulses,WB_Clk_Pulses;

_GLOBAL unsigned int WB_Clk_Pulses;			// Clock Pulses for the Weighing Bucket
_GLOBAL unsigned int WB_OD_Time _GLOBAL_INIT(10);		// Open Delay time for he WeighingBucket
_GLOBAL unsigned int WB_OT_Time _GLOBAL_INIT(10);		// Open Time time for the Weighing Bucket
_GLOBAL unsigned int WB_OD_TMR;				// Open Delay Timer of the Weighing Bucket
_GLOBAL unsigned int WB_OT_TMR;				// Open Time Timer of Weighing Bucket
_GLOBAL unsigned int WB_Angle_Ptr;			// Variable similar to WB_Clk_Pulses.

_GLOBAL unsigned int FB_Clk_Pulses;			// Clock Pulses for the Feed Bucket
_GLOBAL unsigned int FB_OD_Time _GLOBAL_INIT(10);		// Open Delay time for the FeedBucket
_GLOBAL unsigned int FB_OT_Time _GLOBAL_INIT(10);		// Open Time time for the FeedBucket
_GLOBAL unsigned int FB_OD_TMR;				// Open Delay Timer of the Feed Bucket
_GLOBAL unsigned int FB_OfD_TMR;
_GLOBAL unsigned int FB_OfD_Time _GLOBAL_INIT(300);				// disable Delay Timer of the Feed Bucket enable
_GLOBAL unsigned int FB_OT_TMR;				// Open Time Timer of Feed Bucket
_GLOBAL unsigned int FB_Angle_Ptr;			// variable similar to FB_Clk_Pulses.


_GLOBAL unsigned int MotoPro _GLOBAL_INIT(0);
_GLOBAL unsigned int MotoPro_FB;
_GLOBAL unsigned int shift_speed_row_WB,shift_speed_row_FB;


///////manual oprn/////
_GLOBAL _Bool Flag_ManualOperation;
_GLOBAL _Bool Flag_ManOpr_Stage1;
_GLOBAL _Bool Flag_ManOpr_Stage2;
_GLOBAL _Bool Flag_ManOpr_Stage3;
_GLOBAL _Bool Flag_ManOpr_Stage4;
_GLOBAL _Bool Flag_SingleCycle;

//_GLOBAL _Bool ManOpr_Vib_Flag;
_GLOBAL _Bool ManOpr_FB_Flag;
_GLOBAL _Bool ManOpr_WB_Flag;
_GLOBAL _Bool ManOpr_SS_Flag;
_GLOBAL _Bool ManOpr_CS_Flag;


///runnn operation/////
_GLOBAL unsigned int calibration_wt_flag;
_GLOBAL unsigned int Auto_Zero_Interval;
_GLOBAL signed int RSI_Calib_Cnt_1,RSI_Calib_Cnt_2,RSI_Calib_Cnt_3,RSI_Calib_Cnt_4,RSI_Calib_Cnt_5,RSI_Calib_Cnt_6,RSI_Calib_Cnt_7,RSI_Calib_Cnt_8,RSI_Calib_Cnt_9,RSI_Calib_Cnt_10;
_GLOBAL signed int RSI_Tare_Cnt_1,RSI_Tare_Cnt_2,RSI_Tare_Cnt_3,RSI_Tare_Cnt_4,RSI_Tare_Cnt_5,RSI_Tare_Cnt_6,RSI_Tare_Cnt_7,RSI_Tare_Cnt_8,RSI_Tare_Cnt_9,RSI_Tare_Cnt_10;
_GLOBAL signed int RSI_Calib_Slope_1,RSI_Calib_Slope_2,RSI_Calib_Slope_3,RSI_Calib_Slope_4,RSI_Calib_Slope_5,RSI_Calib_Slope_6,RSI_Calib_Slope_7,RSI_Calib_Slope_8,RSI_Calib_Slope_9,RSI_Calib_Slope_10;
_GLOBAL unsigned int time_to_start_fb,time_to_start_fb_flag;
_GLOBAL unsigned int run_time_flag,run_time_taken;
_GLOBAL _Bool Flag_WtReady;
_GLOBAL unsigned int fb_time_taken_counter,wb_time_taken_counter,lf_time_taken_counter;
_GLOBAL _Bool Head_In_Combi;
_GLOBAL _Bool Head_In_Recharge;
_GLOBAL _Bool Flag_RunOperation;
_GLOBAL _Bool Flag_Run;
_GLOBAL _Bool Flag_RunCyc;
_GLOBAL _Bool Flag_Run_Stage1;
_GLOBAL _Bool Flag_Run_Stage2;
_GLOBAL _Bool Flag_Run_Stage3;
_GLOBAL _Bool Flag_Run_Stage4;
_GLOBAL _Bool Flag_Run_Stage5;

_GLOBAL _Bool wt_calculated_flag;
_GLOBAL _Bool Start_Weight_Cal_Flag;

_GLOBAL unsigned int Auto_Tare_Flag;
_GLOBAL unsigned int Actual_Dump_Counter;
//_RUN unsigned int Auto_Zero_Interval;

//_RUN unsigned int calibration_wt_flag;

_GLOBAL unsigned int a,Dump,Recharge;
_GLOBAL unsigned int LongTime_Not_In_Combi_Count,LongTime_Not_In_Combi_flag;


//_RUN signed int RSI_Calib_Cnt_1,RSI_Calib_Cnt_2,RSI_Calib_Cnt_3,RSI_Calib_Cnt_4,RSI_Calib_Cnt_5,RSI_Calib_Cnt_6,RSI_Calib_Cnt_7,RSI_Calib_Cnt_8,RSI_Calib_Cnt_9,RSI_Calib_Cnt_10;


_GLOBAL unsigned int Run_Cycle_Time_Flag;
_GLOBAL unsigned int Run_Cycle_Counter;
_GLOBAL unsigned int fb_time_taken_flag,wb_time_taken_flag,lf_time_taken_flag,FB_OfD_TMR_flag;
_GLOBAL unsigned int fb_time_taken_counter,wb_time_taken_counter,lf_time_taken_counter;
_GLOBAL unsigned int enable_buff[20],enb_i,enb_flag,enable_time_count;

#endif /* GLOBAL_H_ */
