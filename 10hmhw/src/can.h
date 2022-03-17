/*
 * can.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#ifndef CAN_H_
#define CAN_H_

/*
 * Can.h
 *
 *  Created on: Feb 8, 2022
 *      Author: Pustake
 */

#ifndef CAN_VAR
# define _CAN extern
# define _CAN_INIT(x)
#else
# define _CAN
# define _CAN_INIT(x)  = x
#endif

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <stdio.h>              // sprintf()
#include <string.h>             // strlen()
#include "platform.h"           // Located in the FIT BSP module
#include "r_sci_rx_if.h"        // The SCI FIT module API interface file
#include "r_rscan_rx_if.h"      // The RSCAN FIT module API interface file
#include "r_cg_userdefine.h"

//#include "main.h"               // MSG and STATE enums


/************************************************************
 #define

 ************************************************************/
#define RX_BUFSIZE      40
#define TX_BUFSIZE      60




/******************************************************************************/


_CAN sci_hdl_t    g_sci_handle;
_CAN char         g_txbuf[];
_CAN can_txmsg_t  g_txmsg;
_CAN uint32_t            g_ovfl_cnt _CAN_INIT(10);
_CAN can_filter_t        g_filter;

//_CAN unsigned int a;
_CAN unsigned int wait;
_CAN _Bool Flag_CalibOperation;
_CAN _Bool ManOpr_Vib_Flag;
//_CAN unsigned int LongTime_Not_In_Combi_Count,LongTime_Not_In_Combi_flag;



//_CAN unsigned  int 	CAN_SlaveID  _CAN_INIT(0);
//_CAN signed int      GSI_TareCnt _CAN_INIT(0);
//_CAN unsigned int    Auto_Tare_Flag;





typedef enum e_state
{
    STATE_CONNECTING_UART,
    STATE_CONNECTING_CAN,
    STATE_CAN_TO_UART,
    STATE_UART_TO_CAN
} state_t;






void init_can(void);
void init_can_again(void);
void can_rx231_init_ports(void);
void wait_can_network(void);
void MainCallback(can_cb_evt_t event, void *p_args);
void ChanCallback(uint8_t chan, can_cb_evt_t event, void *p_args);
//void Delay_Loop(unsigned int time_sec);
void  process_uart_msg(void);
//void  Clr_WatchDog(void);
void CAN_SEND_MEG(struct CFrame *CANFrame1);
void Check_CAN_Status(void);
void process_can_msg(can_rxmsg_t *rxmsg);
void Send_data(void);
void Create_Send_CAN_Frame(void);
void Send_Tarecount();
void Send_Calibcount();
void wait_can_network(void);
void Delay_Loop(unsigned long int Cnt);

#endif /* CAN_H_ */
