/*
 * Can.c
 *
 *  Created on: Feb 8, 2022
 *      Author: Pustake
 */
/*
 * Can.c
 *
 *  Created on: Feb 8, 2022
 *      Author: Pustake
 */

#ifndef SMC_GEN_CAN_C_
#define SMC_GEN_CAN_C_


//#include <stdio.h>              // sprintf()
//#include <string.h>             // strlen()
//#include "platform.h"

//#include "main.h"
//#include "r_sci_rx_if.h"
#include "r_rscan_rx_if.h"
#define CAN_VAR
#include "can.h"
#include "globals.h"
#define TIM_VAR
#include "Timer.h"
#include "ADC_CS5532.h"
#include "All_Header.h"
#include "Manual_OP_Varib.h"
#include "Stepper_Motor_Varib.h"
#define CAN_VAR
#include "can_Varib.h"
#include "functions.h"
#include "r_rscan_rx_if.h"
/* Configuration file for this package. */
#include "r_rscan_rx_config.h"
/* Private header file for this package. */
#include "r_rscan_rx_private.h"
//volatile uart_msg_t g_uart_msg;
//unsigned  int 	CAN_SlaveID = 0;
typedef enum e_uart_msg
{
    MSG_NONE,
    MSG_DISPLAY_MENU,
    MSG_SEND_CAN,
    MSG_RESUME_CAN,
    MSG_OVERFLOW
} uart_msg_t;


volatile uart_msg_t g_uart_msg = MSG_NONE;
//extern volatile uart_msg_t g_uart_msg;
can_txmsg_t         g_txmsg;
can_rxmsg_t         g_rxmsg;


//volatile uart_msg_t g_uart_msg = MSG_NONE;

struct CFrame
{
	 unsigned long int 	id;
	    uint8_t     rtr;
	    uint8_t     dlc;

	    unsigned char 		data[8];
};
struct CFrame CANFrame;

/*typedef struct st_can_rxmsg
{
    uint8_t     ide;
    uint8_t     rtr;
    uint32_t    id;
    uint8_t     dlc;
    uint8_t     data[8];
    uint16_t    label;          // 12-bit label from receive rule
    uint16_t    timestamp;
} can_rxmsg_t;
*/


//_Bool ManOpr_Vib_Flag;


void init_can(void)
{

	//Clr_WatchDog();
    can_err_t       err;
    can_cfg_t       config;
    can_bitrate_t   baud;

    /* Configure CAN port for channel 0 */
    can_rx231_init_ports();

    /* Open driver. Timestamp source is arbitrary. */
    config.timestamp_src = CAN_TIMESTAMP_SRC_HALF_PCLK;     // commented by DT on 25/08/2021
    config.timestamp_div = CAN_TIMESTAMP_DIV_1024;          // commented by DT on 25/08/2021

    err = R_CAN_Open(&config, MainCallback);
    if (err != CAN_SUCCESS)
    {
        while(1)
        {


        }


        //Clr_WatchDog();
    }

    /* Initialize channel 0 (includes mailboxes) */
    baud.prescaler = CAN_RSK_8MHZ_XTAL_500KBPS_PRESCALER;
    baud.tseg1 = CAN_RSK_8MHZ_XTAL_500KBPS_TSEG1;
    baud.tseg2 = CAN_RSK_8MHZ_XTAL_500KBPS_TSEG2;
    baud.sjw = CAN_RSK_8MHZ_XTAL_500KBPS_SJW;
    err = R_CAN_InitChan(CAN_CH0, &baud, ChanCallback);     // CAN_CFG_CLOCK_SOURCE 1
    if (err != CAN_SUCCESS)
    {
        while(1)
        {

        }

    }

    /* Initialize a receive FIFO */
    err = R_CAN_ConfigFIFO(CAN_BOX_RXFIFO_0,
                           CAN_FIFO_THRESHOLD_1,    // set int flag at every message received
                           CAN_BOX_NONE);           // unused field for RXFIFO
    if (err != CAN_SUCCESS)
    {
        while(1)
        {

        }

    }

    /* Do not need transmit FIFO */
    /* Do not need history FIFO */

    /* Initialize a receive rule filter for all message IDs */
    g_filter.check_ide = TRUE;    // check the IDE field in message
    g_filter.ide = 0;             // 0 = 11-bit ID
    g_filter.check_rtr = FALSE;   // do not check the RTR field in message
    g_filter.rtr = 0;             // (value does not matter here; not checking)
    g_filter.id = 0x00;          // (value does not matter here; not checking)
    g_filter.id_mask = 0x000;     // all messages are accepted
    g_filter.min_dlc = 0;         // message data can be 0 to 8 bytes
    g_filter.label = 0x800;       // arbitrary label (unused)

    /* Add rule to channel 0. Route filtered messages to receive FIFO 0 */
    err = R_CAN_AddRxRule(CAN_CH0, &g_filter, CAN_BOX_RXFIFO_0);
    if (err != CAN_SUCCESS)
    {
        while(1)
        {

        }

    }

    /* Initialization complete. Go to communications mode */
    err = R_CAN_Control(CAN_CMD_SET_MODE_COMM, 0);
    if (err != CAN_SUCCESS)
    {
        while(1)
        {

        }
    }

    /* Setup a message to transmit. ID, DLC, and data will be filled in by by user via UART */
    g_txmsg.ide = 0;
    g_txmsg.rtr = 0;
    g_txmsg.one_shot = FALSE;          // do normal retries when sending
    g_txmsg.log_history = FALSE;       // do not log this message in history FIFO

    return;
}

//***********************************************************************************************************************
// * Function Name	: void process_can_msg(can_rxmsg_t *rxmsg)
// * Description	: function used to process the frame received over CAN network
// * Arguments		: rxmsg - Message received over CAN network.
//   Version        : edited by sg .
//***********************************************************************************************************************

void process_can_msg(can_rxmsg_t *rxmsg)
{
	   Clr_WatchDog();       //10032022


	unsigned int temp_command;

	Dump     = 0;
	Recharge = 0;

	if((rxmsg->id) == 0x00)
	{
		Flag_CalibOperation  = 0;
//		Flag_RunOperation = 1;
		Flag_ManualOperation = 0;

		Dump     = 0;
		Recharge = 0;

		Dump = (unsigned int)(rxmsg->data[0]<<8);
		Dump = (unsigned int)(Dump|(rxmsg->data[1]));

		Recharge = (unsigned int)(rxmsg->data[2]<<8);
		Recharge = (unsigned int)(Recharge|(rxmsg->data[3]));

		Dump     = Dump&0x0fff;
		Recharge = Recharge&0x0fff;

		Dump = (Dump>>(CAN_SlaveID)-1);
		Dump = Dump & 0x1;

		Recharge = (Recharge>>(CAN_SlaveID)-1);
		Recharge = Recharge&0x1;

		//if((((Dump>>(CAN_SlaveID)-1))&0x1)==1)
		if((Dump!=0) && (Auto_Tare_Flag == 0) && (Settle_TMR==0))
		{
			GUI_run_time_flag = 1;
			GUI_run_time_taken = 0;
			Start_Weight_Cal_Flag      = 1;
			Head_In_Recharge           = 0;
			Head_In_Combi              = 1;
			Flag_RunCyc                = 0;
			Flag_Run_Stage1            = 0;
			Flag_WB_Trig               = 0;
			Flag_RunOperation          = 1;
			LongTime_Not_In_Combi_flag = 0;
			Flag_Run                   = 1;
		}
		//else if((((Recharge>>(CAN_SlaveID)-1))&0x1)==1)
		else if((Recharge!=0) && (Auto_Tare_Flag == 0) && (Settle_TMR==0))
		{
			Start_Weight_Cal_Flag      = 1;
			Head_In_Combi              = 0;
			Head_In_Recharge           = 1;
			Flag_RunCyc                = 0;
			Flag_Run_Stage1            = 0;
			Flag_WB_Trig               = 0;
			Flag_RunOperation          = 1;
			LongTime_Not_In_Combi_flag = 0;
			Flag_Run                   = 1;
		}
		else
		{
			Head_In_Combi         = 0;
			Head_In_Recharge      = 0;
			Flag_RunOperation     = 0;
			Flag_Run              = 0;
			Start_Weight_Cal_Flag = 0;
			LongTime_Not_In_Combi_Count++;
		}
	}



	if((rxmsg->id) == 0xAD)
	{
		AUI_GAIN = (unsigned int)(rxmsg->data[0]<<8);
		AUI_GAIN = (unsigned int)(AUI_GAIN|(rxmsg->data[1]));

		AUI_SPEED = (unsigned int)(rxmsg->data[2]<<8);
		AUI_SPEED = (unsigned int)(AUI_SPEED|(rxmsg->data[3]));

		ADSAMPLES = (unsigned int)(rxmsg->data[4]<<8);
		ADSAMPLES = (unsigned int)(ADSAMPLES|(rxmsg->data[5]));

		Diff_Cnt_Val = (unsigned int)(rxmsg->data[6]<<8);
		Diff_Cnt_Val = (unsigned int)(Diff_Cnt_Val|(rxmsg->data[7]));
	}
	else if((rxmsg->id) == 0xAE)
	{
		Stable_Count_Val = (unsigned int)(rxmsg->data[0]<<8);
		Stable_Count_Val = (unsigned int)(Stable_Count_Val|(rxmsg->data[1]));

		Auto_Zero_Interval = (unsigned int)(rxmsg->data[2]<<8);
		Auto_Zero_Interval = (unsigned int)(Auto_Zero_Interval|(rxmsg->data[3]));

		Settle_Time = (unsigned int)(rxmsg->data[6]<<8);
		Settle_Time = (unsigned int)(Settle_Time|(rxmsg->data[7]));
	}
	else if((rxmsg->id) == 0xAF)
	{
		Firing_Angle = (unsigned int)(rxmsg->data[2]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[3]));

		Firing_Angle = ((-80)*Firing_Angle)+8000;

		SD_LF_Time = (unsigned int)(rxmsg->data[4]<<8);
		SD_LF_Time = (unsigned int)(SD_LF_Time|(rxmsg->data[5]));

		VBRT_Cyl = (unsigned int)(rxmsg->data[6]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[7]));
	}
	else if((rxmsg->id) == 0xB1)
	{
		FB_OD_Time = (unsigned int)(rxmsg->data[0]<<8);
		FB_OD_Time = (unsigned int)(FB_OD_Time|(rxmsg->data[1]));

		WB_OT_Time = (unsigned int)(rxmsg->data[2]<<8);
		WB_OT_Time = (unsigned int)(WB_OT_Time|(rxmsg->data[3]));

		WB_OD_Time = (unsigned int)(rxmsg->data[4]<<8);
		WB_OD_Time = (unsigned int)(WB_OD_Time|(rxmsg->data[5]));

		WB_OT_Time = (unsigned int)(rxmsg->data[6]<<8);
		WB_OT_Time = (unsigned int)(WB_OT_Time|(rxmsg->data[7]));
	}
	else if((rxmsg->id) == 0xB3)
	{
		RSI_Calib_Slope_9 = (signed int)(rxmsg->data[2]<<8);
		RSI_Calib_Slope_9 = (signed int)(RSI_Calib_Slope_9|(rxmsg->data[3]));

		RSI_Calib_Slope_10 = (signed int)(rxmsg->data[4]<<8);
		RSI_Calib_Slope_10 = (signed int)(RSI_Calib_Slope_10|(rxmsg->data[5]));

		if(CAN_SlaveID==1)
			CSI_CalibSlope = RSI_Calib_Slope_1;
		else if(CAN_SlaveID==2)
			CSI_CalibSlope = RSI_Calib_Slope_2;
		else if(CAN_SlaveID==3)
			CSI_CalibSlope = RSI_Calib_Slope_3;
		else if(CAN_SlaveID==4)
			CSI_CalibSlope = RSI_Calib_Slope_4;
		else if(CAN_SlaveID==5)
			CSI_CalibSlope = RSI_Calib_Slope_5;
		else if(CAN_SlaveID==6)
			CSI_CalibSlope = RSI_Calib_Slope_6;
		else if(CAN_SlaveID==7)
			CSI_CalibSlope = RSI_Calib_Slope_7;
		else if(CAN_SlaveID==8)
			CSI_CalibSlope = RSI_Calib_Slope_8;
		else if(CAN_SlaveID==9)
			CSI_CalibSlope = RSI_Calib_Slope_9;
		else if(CAN_SlaveID==10)
			CSI_CalibSlope = RSI_Calib_Slope_10;
	}
	else if((rxmsg->id) == 0xB4)
	{
		RSI_Tare_Cnt_1 = (signed int)(rxmsg->data[0]<<8);
		RSI_Tare_Cnt_1 = (signed int)(RSI_Tare_Cnt_1|(rxmsg->data[1]));

		RSI_Tare_Cnt_2 = (signed int)(rxmsg->data[2]<<8);
		RSI_Tare_Cnt_2 = (signed int)(RSI_Tare_Cnt_2|(rxmsg->data[3]));

		RSI_Tare_Cnt_3 = (signed int)(rxmsg->data[4]<<8);
		RSI_Tare_Cnt_3 = (signed int)(RSI_Tare_Cnt_3|(rxmsg->data[5]));

		RSI_Tare_Cnt_4 = (signed int)(rxmsg->data[6]<<8);
		RSI_Tare_Cnt_4 = (signed int)(RSI_Tare_Cnt_4|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_TareCnt = RSI_Tare_Cnt_1;
		else if(CAN_SlaveID==2)
			CSI_TareCnt = RSI_Tare_Cnt_2;
		else if(CAN_SlaveID==3)
			CSI_TareCnt = RSI_Tare_Cnt_3;
		else if(CAN_SlaveID==4)
			CSI_TareCnt = RSI_Tare_Cnt_4;
		else if(CAN_SlaveID==5)
			CSI_TareCnt = RSI_Tare_Cnt_5;
		else if(CAN_SlaveID==6)
			CSI_TareCnt = RSI_Tare_Cnt_6;
		else if(CAN_SlaveID==7)
			CSI_TareCnt = RSI_Tare_Cnt_7;
		else if(CAN_SlaveID==8)
			CSI_TareCnt = RSI_Tare_Cnt_8;
		else if(CAN_SlaveID==9)
			CSI_TareCnt = RSI_Tare_Cnt_9;
		else if(CAN_SlaveID==10)
			CSI_TareCnt = RSI_Tare_Cnt_10;
	}
	else if((rxmsg->id) == 0xB5)
	{
		RSI_Tare_Cnt_5 = (signed int)(rxmsg->data[0]<<8);
		RSI_Tare_Cnt_5 = (signed int)(RSI_Tare_Cnt_5|(rxmsg->data[1]));

		RSI_Tare_Cnt_6 = (signed int)(rxmsg->data[2]<<8);
		RSI_Tare_Cnt_6 = (signed int)(RSI_Tare_Cnt_6|(rxmsg->data[3]));

		RSI_Tare_Cnt_7 = (signed int)(rxmsg->data[4]<<8);
		RSI_Tare_Cnt_7 = (signed int)(RSI_Tare_Cnt_7|(rxmsg->data[5]));

		RSI_Tare_Cnt_8 = (signed int)(rxmsg->data[6]<<8);
		RSI_Tare_Cnt_8 = (signed int)(RSI_Tare_Cnt_8|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_TareCnt = RSI_Tare_Cnt_1;
		else if(CAN_SlaveID==2)
			CSI_TareCnt = RSI_Tare_Cnt_2;
		else if(CAN_SlaveID==3)
			CSI_TareCnt = RSI_Tare_Cnt_3;
		else if(CAN_SlaveID==4)
			CSI_TareCnt =RSI_Tare_Cnt_4;
		else if(CAN_SlaveID==5)
			CSI_TareCnt = RSI_Tare_Cnt_5;
		else if(CAN_SlaveID==6)
			CSI_TareCnt = RSI_Tare_Cnt_6;
		else if(CAN_SlaveID==7)
			CSI_TareCnt = RSI_Tare_Cnt_7;
		else if(CAN_SlaveID==8)
			CSI_TareCnt = RSI_Tare_Cnt_8;
		else if(CAN_SlaveID==9)
			CSI_TareCnt = RSI_Tare_Cnt_9;
		else if(CAN_SlaveID==10)
			CSI_TareCnt = RSI_Tare_Cnt_10;
	}
	else if((rxmsg->id) == 0xB6)
	{
		RSI_Tare_Cnt_9 = (signed int)(rxmsg->data[0]<<8);
		RSI_Tare_Cnt_9 = (signed int)(RSI_Tare_Cnt_9|(rxmsg->data[1]));

		RSI_Tare_Cnt_10 = (signed int)(rxmsg->data[2]<<8);
		RSI_Tare_Cnt_10 = (signed int)(RSI_Tare_Cnt_10|(rxmsg->data[3]));

		RSI_Calib_Cnt_1 = (signed int)(rxmsg->data[4]<<8);
		RSI_Calib_Cnt_1 = (signed int)(RSI_Calib_Cnt_1|(rxmsg->data[5]));

		RSI_Calib_Cnt_2 = (signed int)(rxmsg->data[6]<<8);
		RSI_Calib_Cnt_2 = (signed int)(RSI_Calib_Cnt_2|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_TareCnt = RSI_Tare_Cnt_1;
		else if(CAN_SlaveID==2)
			CSI_TareCnt = RSI_Tare_Cnt_2;
		else if(CAN_SlaveID==3)
			CSI_TareCnt = RSI_Tare_Cnt_3;
		else if(CAN_SlaveID==4)
			CSI_TareCnt = RSI_Tare_Cnt_4;
		else if(CAN_SlaveID==5)
			CSI_TareCnt = RSI_Tare_Cnt_5;
		else if(CAN_SlaveID==6)
			CSI_TareCnt = RSI_Tare_Cnt_6;
		else if(CAN_SlaveID==7)
			CSI_TareCnt = RSI_Tare_Cnt_7;
		else if(CAN_SlaveID==8)
			CSI_TareCnt = RSI_Tare_Cnt_8;
		else if(CAN_SlaveID==9)
			CSI_TareCnt = RSI_Tare_Cnt_9;
		else if(CAN_SlaveID==10)
			CSI_TareCnt = RSI_Tare_Cnt_10;

		if(CAN_SlaveID==1)
			CSI_CalibCnt = RSI_Calib_Cnt_1;
		else if(CAN_SlaveID==2)
			CSI_CalibCnt = RSI_Calib_Cnt_2;
		else if(CAN_SlaveID==3)
			CSI_CalibCnt = RSI_Calib_Cnt_3;
		else if(CAN_SlaveID==4)
			CSI_CalibCnt = RSI_Calib_Cnt_4;
		else if(CAN_SlaveID==5)
			CSI_CalibCnt = RSI_Calib_Cnt_5;
		else if(CAN_SlaveID==6)
			CSI_CalibCnt = RSI_Calib_Cnt_6;
		else if(CAN_SlaveID==7)
			CSI_CalibCnt = RSI_Calib_Cnt_7;
		else if(CAN_SlaveID==8)
			CSI_CalibCnt = RSI_Calib_Cnt_8;
		else if(CAN_SlaveID==9)
			CSI_CalibCnt = RSI_Calib_Cnt_9;
		else if(CAN_SlaveID==10)
			CSI_CalibCnt = RSI_Calib_Cnt_10;
	}
	else if((rxmsg->id) == 0xB7)
	{
		RSI_Calib_Cnt_3 = (signed int)(rxmsg->data[0]<<8);
		RSI_Calib_Cnt_3 = (signed int)(RSI_Calib_Cnt_3|(rxmsg->data[1]));

		RSI_Calib_Cnt_4 = (signed int)(rxmsg->data[2]<<8);
		RSI_Calib_Cnt_4 = (signed int)(RSI_Calib_Cnt_4|(rxmsg->data[3]));

		RSI_Calib_Cnt_5 = (signed int)(rxmsg->data[4]<<8);
		RSI_Calib_Cnt_5 = (signed int)(RSI_Calib_Cnt_5|(rxmsg->data[5]));

		RSI_Calib_Cnt_6 = (signed int)(rxmsg->data[6]<<8);
		RSI_Calib_Cnt_6 = (signed int)(RSI_Calib_Cnt_6|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_CalibCnt = RSI_Calib_Cnt_1;
		else if(CAN_SlaveID==2)
			CSI_CalibCnt = RSI_Calib_Cnt_2;
		else if(CAN_SlaveID==3)
			CSI_CalibCnt = RSI_Calib_Cnt_3;
		else if(CAN_SlaveID==4)
			CSI_CalibCnt = RSI_Calib_Cnt_4;
		else if(CAN_SlaveID==5)
			CSI_CalibCnt = RSI_Calib_Cnt_5;
		else if(CAN_SlaveID==6)
			CSI_CalibCnt = RSI_Calib_Cnt_6;
		else if(CAN_SlaveID==7)
			CSI_CalibCnt = RSI_Calib_Cnt_7;
		else if(CAN_SlaveID==8)
			CSI_CalibCnt = RSI_Calib_Cnt_8;
		else if(CAN_SlaveID==9)
			CSI_CalibCnt = RSI_Calib_Cnt_9;
		else if(CAN_SlaveID==10)
			CSI_CalibCnt = RSI_Calib_Cnt_10;
	}
	else if((rxmsg->id) == 0xB8)
	{
		RSI_Calib_Cnt_7 = (signed int)(rxmsg->data[0]<<8);
		RSI_Calib_Cnt_7 = (signed int)(RSI_Calib_Cnt_7|(rxmsg->data[1]));

		RSI_Calib_Cnt_8 = (signed int)(rxmsg->data[2]<<8);
		RSI_Calib_Cnt_8 = (signed int)(RSI_Calib_Cnt_8|(rxmsg->data[3]));

		RSI_Calib_Cnt_9 = (signed int)(rxmsg->data[4]<<8);
		RSI_Calib_Cnt_9 = (signed int)(RSI_Calib_Cnt_9|(rxmsg->data[5]));

		RSI_Calib_Cnt_10 = (signed int)(rxmsg->data[6]<<8);
		RSI_Calib_Cnt_10 = (signed int)(RSI_Calib_Cnt_10|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_CalibCnt = RSI_Calib_Cnt_1;
		else if(CAN_SlaveID==2)
			CSI_CalibCnt = RSI_Calib_Cnt_2;
		else if(CAN_SlaveID==3)
			CSI_CalibCnt = RSI_Calib_Cnt_3;
		else if(CAN_SlaveID==4)
			CSI_CalibCnt = RSI_Calib_Cnt_4;
		else if(CAN_SlaveID==5)
			CSI_CalibCnt = RSI_Calib_Cnt_5;
		else if(CAN_SlaveID==6)
			CSI_CalibCnt = RSI_Calib_Cnt_6;
		else if(CAN_SlaveID==7)
			CSI_CalibCnt = RSI_Calib_Cnt_7;
		else if(CAN_SlaveID==8)
			CSI_CalibCnt = RSI_Calib_Cnt_8;
		else if(CAN_SlaveID==9)
			CSI_CalibCnt = RSI_Calib_Cnt_9;
		else if(CAN_SlaveID==10)
			CSI_CalibCnt = RSI_Calib_Cnt_10;
	}
	else if((rxmsg->id) == 0xB9)
	{
		RSI_Calib_Slope_1 = (signed int)(rxmsg->data[0]<<8);
		RSI_Calib_Slope_1 = (signed int)(RSI_Calib_Slope_1|(rxmsg->data[1]));

		RSI_Calib_Slope_2 = (signed int)(rxmsg->data[2]<<8);
		RSI_Calib_Slope_2 = (signed int)(RSI_Calib_Slope_2|(rxmsg->data[3]));

		RSI_Calib_Slope_3 = (signed int)(rxmsg->data[4]<<8);
		RSI_Calib_Slope_3 = (signed int)(RSI_Calib_Slope_3|(rxmsg->data[5]));

		RSI_Calib_Slope_4 = (signed int)(rxmsg->data[6]<<8);
		RSI_Calib_Slope_4 = (signed int)(RSI_Calib_Slope_4|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_CalibSlope = RSI_Calib_Slope_1;
		else if(CAN_SlaveID==2)
			CSI_CalibSlope = RSI_Calib_Slope_2;
		else if(CAN_SlaveID==3)
			CSI_CalibSlope = RSI_Calib_Slope_3;
		else if(CAN_SlaveID==4)
			CSI_CalibSlope = RSI_Calib_Slope_4;
		else if(CAN_SlaveID==5)
			CSI_CalibSlope = RSI_Calib_Slope_5;
		else if(CAN_SlaveID==6)
			CSI_CalibSlope = RSI_Calib_Slope_6;
		else if(CAN_SlaveID==7)
			CSI_CalibSlope = RSI_Calib_Slope_7;
		else if(CAN_SlaveID==8)
			CSI_CalibSlope = RSI_Calib_Slope_8;
		else if(CAN_SlaveID==9)
			CSI_CalibSlope = RSI_Calib_Slope_9;
		else if(CAN_SlaveID==10)
			CSI_CalibSlope = RSI_Calib_Slope_10;
	}
	else if((rxmsg->id) == 0xC1)
	{
		RSI_Calib_Slope_5 = (signed int)(rxmsg->data[0]<<8);
		RSI_Calib_Slope_5 = (signed int)(RSI_Calib_Slope_5|(rxmsg->data[1]));

		RSI_Calib_Slope_6 = (signed int)(rxmsg->data[2]<<8);
		RSI_Calib_Slope_6 = (signed int)(RSI_Calib_Slope_6|(rxmsg->data[3]));

		RSI_Calib_Slope_7 = (signed int)(rxmsg->data[4]<<8);
		RSI_Calib_Slope_7 = (signed int)(RSI_Calib_Slope_7|(rxmsg->data[5]));

		RSI_Calib_Slope_8 = (signed int)(rxmsg->data[6]<<8);
		RSI_Calib_Slope_8 = (signed int)(RSI_Calib_Slope_8|(rxmsg->data[7]));

		if(CAN_SlaveID==1)
			CSI_CalibSlope = RSI_Calib_Slope_1;
		else if(CAN_SlaveID==2)
			CSI_CalibSlope = RSI_Calib_Slope_2;
		else if(CAN_SlaveID==3)
			CSI_CalibSlope = RSI_Calib_Slope_3;
		else if(CAN_SlaveID==4)
			CSI_CalibSlope = RSI_Calib_Slope_4;
		else if(CAN_SlaveID==5)
			CSI_CalibSlope = RSI_Calib_Slope_5;
		else if(CAN_SlaveID==6)
			CSI_CalibSlope = RSI_Calib_Slope_6;
		else if(CAN_SlaveID==7)
			CSI_CalibSlope = RSI_Calib_Slope_7;
		else if(CAN_SlaveID==8)
			CSI_CalibSlope = RSI_Calib_Slope_8;
		else if(CAN_SlaveID==9)
			CSI_CalibSlope = RSI_Calib_Slope_9;
		else if(CAN_SlaveID==10)
			CSI_CalibSlope = RSI_Calib_Slope_10;
	}

	if(((rxmsg->id) == 0x70) &&((CAN_SlaveID==1)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x71) &&((CAN_SlaveID==2)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x72) &&((CAN_SlaveID==3)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x73) &&((CAN_SlaveID==4)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x74) &&((CAN_SlaveID==5)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x75) &&((CAN_SlaveID==6)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x76) &&((CAN_SlaveID==7)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x77) &&((CAN_SlaveID==8)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x78) &&((CAN_SlaveID==9)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}
	else if(((rxmsg->id) == 0x79) &&((CAN_SlaveID==10)))
	{
		VBRT_Cyl = (unsigned int)(rxmsg->data[0]<<8);
		VBRT_Cyl = (unsigned int)(VBRT_Cyl|(rxmsg->data[1]));
	}

	if(((rxmsg->id) == 0x40) &&((CAN_SlaveID==1)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x41) &&((CAN_SlaveID==2)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x42)&&((CAN_SlaveID==3)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x43)&&((CAN_SlaveID==4)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x44)&&((CAN_SlaveID==5)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x45)&&((CAN_SlaveID==6)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x46)&&((CAN_SlaveID==7)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x47)&&((CAN_SlaveID==8)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x48)&&((CAN_SlaveID==9)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}
	else if(((rxmsg->id) == 0x49) &&((CAN_SlaveID==10)))
	{
		Firing_Angle = (unsigned int)(rxmsg->data[0]<<8);
		Firing_Angle = (unsigned int)(Firing_Angle|(rxmsg->data[1]));
		Firing_Angle = ((-80)*Firing_Angle)+8000;
	}

	if((rxmsg->id) == 0X19 )
	{
		Flag_ManualOperation = 1;
		Flag_CalibOperation  = 0;
		Flag_RunOperation    = 0;

		temp_command         = 0;

		temp_command = (unsigned int)(rxmsg->data[0]<<8);
		temp_command = (unsigned int)(temp_command|(rxmsg->data[1]));

		if(((temp_command>>(CAN_SlaveID+2))&0x1)==1)
		{
			if((temp_command & 0x7)==0x00)
			{
				ManOpr_Vib_Flag = 1;
				ManOpr_FB_Flag  = 0;
				ManOpr_WB_Flag  = 0;
				ManOpr_SS_Flag  = 0;
				ManOpr_CS_Flag  = 0;
			}
			else if((temp_command & 0x7)==0x01)
			{
				ManOpr_Vib_Flag = 0;
				ManOpr_FB_Flag  = 1;
				ManOpr_WB_Flag  = 0;
				ManOpr_SS_Flag  = 0;
				ManOpr_CS_Flag  = 0;
			}
			else if((temp_command & 0x7)==0x02)
			{
				ManOpr_Vib_Flag = 0;
				ManOpr_FB_Flag  = 0;
				ManOpr_WB_Flag  = 1;
				ManOpr_SS_Flag  = 0;
				ManOpr_CS_Flag  = 0;
			}
			else if((temp_command & 0x7)==0x03)
			{
				ManOpr_Vib_Flag = 0;
				ManOpr_FB_Flag  = 0;
				ManOpr_WB_Flag  = 0;
				ManOpr_SS_Flag  = 1;
				ManOpr_CS_Flag  = 0;
			}
			else if((temp_command & 0x7)==0x04)
			{
				ManOpr_Vib_Flag = 0;
				ManOpr_FB_Flag  = 0;
				ManOpr_WB_Flag  = 0;
				ManOpr_SS_Flag  = 0;
				ManOpr_CS_Flag  = 1;
			}
			else
			{
				ManOpr_Vib_Flag = 0;
				ManOpr_FB_Flag  = 0;
				ManOpr_WB_Flag  = 0;
				ManOpr_SS_Flag  = 0;
				ManOpr_CS_Flag  = 0;
			}
		}
		else
		{
			ManOpr_Vib_Flag = 0;
			ManOpr_FB_Flag  = 0;
			ManOpr_WB_Flag  = 0;
			ManOpr_SS_Flag  = 0;
			ManOpr_CS_Flag  = 0;
		}

	}
	else if((rxmsg->id) == CAN_SlaveID)
	{
		  //	Clr_WatchDog();    ///10032022

			if(rxmsg->data[0] == 1)
			{
			   calibration_wt_flag = 1;
				Create_Send_CAN_Frame();
			}
			else if(Settle_TMR==0)
			{
				calibration_wt_flag = 0;
				Create_Send_CAN_Frame();
			}
	}

	else if((rxmsg->id)==0x0C)
	{
		Flag_RunOperation    = 0;
		Flag_ManualOperation = 0;

		a = (unsigned int)(rxmsg->data[0]<<8);
		a = (unsigned int)(a|(rxmsg->data[1]));

		if(((a>>(CAN_SlaveID+1))&0x1)==1)
		{
			if((a&0x3)==0x0)
			{
				Tare_Flag           = FALSE;
				Dump_Flag           = TRUE;
				Calibeate_Flag      = FALSE;
				Flag_CalibOperation = 1;
			}
			else if((a&0x3)==0x1)
			{
				Tare_Flag           = TRUE;
				Dump_Flag           = FALSE;
				Calibeate_Flag      = FALSE;
				Flag_CalibOperation = 1;
			}
			else if((a&0x3)==0x2)
			{
				Tare_Flag           = FALSE;
				Dump_Flag           = FALSE;
				Calibeate_Flag      = TRUE;
				Flag_CalibOperation = 1;
			}
		}
		rxmsg->data[0] = 0;
		rxmsg->data[1] = 0;
}
	rxmsg->data[0] = 0;
	rxmsg->data[1] = 0;
	rxmsg->data[2] = 0;
	rxmsg->data[3] = 0;
	rxmsg->data[4] = 0;
	rxmsg->data[5] = 0;
	rxmsg->data[6] = 0;
	rxmsg->data[7] = 0;

}

void Check_CAN_Status(void)
{
	uint32_t    status;
	can_err_t   can_err;

/* Check if received CAN message */
   if (R_CAN_GetMsg(CAN_BOX_RXFIFO_0, &g_rxmsg) == CAN_SUCCESS)
   {
	   Clr_WatchDog();  Clr_WatchDog();  Clr_WatchDog();       //10032022
	   process_can_msg(&g_rxmsg);
   }
/* Check if any CAN channel errors */
	status = R_CAN_GetStatusMask(CAN_STAT_CH_ERROR, CAN_CH0, &can_err);

	if (status != 0)
	{
		//process_ch_err_msg(status);
	}
}



/******************************************************************************
* Function Name: can_rx231_init_ports
* Description  : Initializes RX231 port 5 for CAN channel 0
* Arguments    : None
* Return Value : None
*******************************************************************************/
void can_rx231_init_ports(void)
{

    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* init CAN channel 0 */

    PORT1.PODR.BIT.B5 = 1;
    PORT1.PODR.BIT.B4 = 0;
    MPC.P14PFS.BYTE = 0x10;         // Pin Function Select P14 CTXD0
    MPC.P15PFS.BYTE = 0x10;        // Pin Function Select P15 CRXD0
    PORT1.PDR.BIT.B4 = 1;         // set TX pin direction to output
    PORT1.DSCR.BIT.B4 = 1;       // High-drive output
    PORT1.PDR.BIT.B5 = 0;       // set RX pin direction to input (dflt)
    PORT1.PMR.BIT.B4 = 1;       // set TX pin mode to peripheral
    PORT1.PMR.BIT.B5 = 1;       // set RX pin mode to peripheral

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);

    return;
}


/*****************************************************************************
* Function Name: wait_can_network
* Description  : This function sends messages to the terminal until it detects
*                that the CAN network is functioning properly. Note that if
*                no network is connected, this function will return because
*                no error conditions are found.
* Arguments    : none
* Return Value : none
******************************************************************************/


void Create_Send_CAN_Frame(void)
{

		unsigned char D[8];
		unsigned char idx;

		 for(idx=0;idx<8;idx++)
		{
			D[idx] = 0;
		}

		if(Settle_TMR == 0 && wt_calculated_flag == 1)
		{
			D[0] = CurrentWt & 0xff;
			D[1] = (CurrentWt >> 8)& 0xff;
		}
		else
		{
			D[0] = 0;
			D[1] = 0;
		}

		D[2] = 0;
		D[3] = 0;
		D[4] = 0;
		D[5] = 0;
		D[6] = 0;

	    if(Flag_WtReady)
	    	D[2] |= 0x01;
	    else
	    	D[2] &= ~(0x01);

	    if(HIN_WB == 0 && ENB_WB == 0 )
	    {
	    	D[3] |= 0x01;
	    }
	    else
	    {
	    	D[3] &= ~(0x01);

	    	if(SUI_homing_flag_wb == 0 && Flag_WB_Trig == 0)
	    	{
	    		SUI_homing_flag_wb = 1;
	    		Flag_WB_Trig   = 0;
	    	}
	    }

	    if(HIN_FB == 0 && ENB_FB == 0)
		{
	    	D[4] |= 0x01;
		}
		else
		{
			D[4] &= ~(0x01);

			if(SUI_homing_flag_fb == 0 && Flag_FB_Trig == 0)
			{
				SUI_homing_flag_fb = 1;
				Flag_FB_Trig   = 0;
			}
		}

	    if(LongTime_Not_In_Combi_flag == 1)
	    {
	    	D[5] |= 0x01;
	    }
	    else
	    {
	    	D[5] &= ~(0x01);
	    }


		CANFrame.id  = CAN_SlaveID + 0X0D;
		CANFrame.rtr=0;            //coomment this if not used
		CANFrame.dlc = 6;        ////5

		for(idx=0;idx<8;idx++)
		{
			CANFrame.data[idx] = D[idx];
		}

		CAN_SEND_MEG(&CANFrame);
}




/*void Send_data(void)
{
	 CANFrame.id=0x131;
	 CANFrame.rtr=0;
	 CANFrame.dlc=2;
	 CANFrame.data[0]=(CSI_TareCnt>>8)&0xFF;
	 CANFrame.data[1]=CSI_TareCnt&0xFF;
	 CAN_SEND_MEG(&CANFrame);

}
*/

void Send_Calibcount()
{
	if(CAN_SlaveID == 1)
		CANFrame.id=0x130;
	if(CAN_SlaveID == 2)
		CANFrame.id=0x133;
	if(CAN_SlaveID == 3)
		CANFrame.id=0x135;
	if(CAN_SlaveID == 4)
		CANFrame.id=0x137;
	if(CAN_SlaveID == 5)
		CANFrame.id=0x139;
	if(CAN_SlaveID == 6)
		CANFrame.id=0x141;
	if(CAN_SlaveID == 7)
		CANFrame.id=0x143;
	if(CAN_SlaveID == 8)
		CANFrame.id=0x145;
	if(CAN_SlaveID == 9)
		CANFrame.id=0x147;
	if(CAN_SlaveID == 10)
		CANFrame.id=0x149;

	CANFrame.rtr=0;
	CANFrame.dlc=4;
	CANFrame.data[0]=(CSI_CalibCnt>>8)&0xFF;
	CANFrame.data[1]=CSI_CalibCnt&0xFF;
	CANFrame.data[2]=(CSI_CalibSlope>>8)&0xFF;
	CANFrame.data[3]=CSI_CalibSlope&0xFF;

	CAN_SEND_MEG(&CANFrame);
}

void Send_Tarecount()
{
	if(CAN_SlaveID == 1)
		CANFrame.id=0x131;
	if(CAN_SlaveID == 2)
		CANFrame.id=0x132;
	if(CAN_SlaveID == 3)
		CANFrame.id=0x134;
	if(CAN_SlaveID == 4)
		CANFrame.id=0x136;
	if(CAN_SlaveID == 5)
		CANFrame.id=0x138;
	if(CAN_SlaveID == 6)
		CANFrame.id=0x140;
	if(CAN_SlaveID == 7)
		CANFrame.id=0x142;
	if(CAN_SlaveID == 8)
		CANFrame.id=0x144;
	if(CAN_SlaveID == 9)
		CANFrame.id=0x146;
	if(CAN_SlaveID == 10)
		CANFrame.id=0x148;

	CANFrame.rtr=0;
	CANFrame.dlc=2;
	CANFrame.data[0]=(CSI_TareCnt>>8)&0xFF;
	CANFrame.data[1]=CSI_TareCnt&0xFF;

	CAN_SEND_MEG(&CANFrame);
}



/*****************************************************************************
* Function Name: wait_can_network
* Description  : This function sends messages to the terminal until it detects
*                that the CAN network is functioning properly. Note that if
*                no network is connected, this function will return because
*                no error conditions are found.
* Arguments    : none
* Return Value : none
******************************************************************************/

/*void wait_can_network(void)
{
    uint32_t    i;

    while(1)
    {

        if ((i % 1000) == 0)
        {
            sprintf(g_txbuf,"\n\rWaiting for CAN network: ");
            while (R_SCI_Send(g_sci_handle, (uint8_t *)g_txbuf, strlen(g_txbuf)) == SCI_ERR_INSUFFICIENT_SPACE) ;
            Delay_Loop(1000);
        }


        sprintf(g_txbuf,"%5d\b\b\b\b\b", i++);
        while (R_SCI_Send(g_sci_handle, (uint8_t *)g_txbuf, 10) == SCI_ERR_INSUFFICIENT_SPACE) ;
        Delay_Loop(1000);


        if (RSCAN0.STSL.BIT.BOSTS == 0)     // not in Bus Off state
        {
            sprintf(g_txbuf,"\n\rBus On state detected. CAN connection established.");
            while (R_SCI_Send(g_sci_handle, (uint8_t *)g_txbuf, strlen(g_txbuf)) == SCI_ERR_INSUFFICIENT_SPACE) ;
            Delay_Loop(1000);


            sprintf(g_txbuf,"\n\r\n\rUART commands available:");
            while (R_SCI_Send(g_sci_handle, (uint8_t *)g_txbuf, strlen(g_txbuf)) == SCI_ERR_INSUFFICIENT_SPACE) ;
            Delay_Loop(1000);
            g_uart_msg = MSG_DISPLAY_MENU;
 //           process_uart_msg();
            Delay_Loop(1000);


            sprintf(g_txbuf, "\n\rWaiting for network messages.\n\r");
            while (R_SCI_Send(g_sci_handle, (uint8_t *)g_txbuf, strlen(g_txbuf)) == SCI_ERR_INSUFFICIENT_SPACE) ;
            Delay_Loop(1000);
            return;
        }
    }
}
*/

/******************************************************************************
* Function Name: MainCallback
* Description  : This function is called from interrupt level whenever a message
*                is received in a receive FIFO or a global error occurs. Global
*                errors include FIFO overflows or a DLC error detection.
* Arguments    : event-
*                   CAN_EVT_RXFIFO_THRESHOLD when threshold messages in an RXFIFO
*                   CAN_EVT_GLOBAL_ERR when a global error is detected
*                p_args-
*                   unused (future)
* Return Value : None
*******************************************************************************/
void MainCallback(can_cb_evt_t event, void *p_args)
{
    uint32_t    mask;
    can_err_t   err;


    if (event == CAN_EVT_GLOBAL_ERR)    // only event interrupts are configured for
    {
        /* Get mask of which global error(s) occurred */
        mask = R_CAN_GetStatusMask(CAN_STAT_GLOBAL_ERR, 0, &err);

        if (mask & CAN_MASK_ERR_DLC)
        {
            nop();  // no processing of this error to be done
        }

        if (mask & CAN_MASK_ERR_FIFO_OVFL)
        {
        	//mask = R_CAN_GetStatusMask(CAN_STAT_FIFO_OVFL, 0, &err);
        	//g_state = STATE_CONNECTING_CAN;
        	//init_can();                                                           ///16032022
            g_ovfl_cnt++;   // rx FIFO overflowed
        }
    }

    return;
}


/******************************************************************************
* Function Name: ChanCallback
* Description  : This function is called from interrupt level whenever a channel
*                transmit or channel error occurs.
* Arguments    : chan-
*                    Channel in which the interrupt occurred on
*                event-
*                    CAN_EVT_TRANSMIT for mailbox transmit complete, abort
*                           complete, or TX/GW/HIST FIFO at threshold
*                    CAN_EVT_CHANNEL_ERR for channel error detection, which
*                           includes (among others) error passive state entry,
*                           bus off entry, and bus off recovery.
*                    CAN_EVT_GWFIFO_RX_THRESHOLD for GW FIFO at receive
*                           threshhold
* Return Value : None
*******************************************************************************/
void ChanCallback(uint8_t       chan,
                  can_cb_evt_t  event,
                  void          *p_args)
{

    if (event == CAN_EVT_TRANSMIT)
    {
        /* No processing needed.
         * Only using interrupts instead of blocking so that the rx FIFO
         * can be serviced more frequently at application level.
         */
        nop();
    }
    else if (event == CAN_EVT_CHANNEL_ERR)
    {
        /* No processing needed.
         * Errors are polled for at the application level to insure error messages
         * do not interfere with possible UART communications in progress
         */
        nop();
    }

    return;
}

void CAN_SEND_MEG(struct CFrame *CANFrame1)
{
	/*Do not make any changes in the following sequence*/
	g_txmsg.ide 	= 0;
	g_txmsg.rtr 	= CANFrame1->rtr;					// Remote Transmission request byte
	g_txmsg.id		= CANFrame1->id;		            // Slave or Frame ID
	g_txmsg.dlc 	= CANFrame1->dlc;					// Frame Size / Must not be more than 8 in Byte
	g_txmsg.data[0] = CANFrame1->data[0];	            // Frame Structure in 8 Bytes
	g_txmsg.data[1] = CANFrame1->data[1];
	g_txmsg.data[2] = CANFrame1->data[2];
	g_txmsg.data[3] = CANFrame1->data[3];
	g_txmsg.data[4] = CANFrame1->data[4];
	g_txmsg.data[5] = CANFrame1->data[5];
	g_txmsg.data[6] = CANFrame1->data[6];
	g_txmsg.data[7] = CANFrame1->data[7];
	g_txmsg.one_shot = FALSE;       		              // Do normal retries when sending
	g_txmsg.log_history = FALSE;    		             // Do not log this message in history FIFO
	R_CAN_SendMsg(CAN_BOX_TXMBX_2, &g_txmsg);		     // Send the CAN frame over the Network
}


#endif /* SMC_GEN_CAN_C_ */


