/*
 * Flash.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

/************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018(2019) Renesas Electronics Corporation. All rights reserved.
*************************************************************************************************/
/************************************************************************************************
* File Name    : r_datfrx_rx_main.c
* Version      : 2.01
* Description  : DATFRX interface source file
*************************************************************************************************/
/************************************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 28.09.2018 2.00     First Release
*              : 25.01.2019 2.01     English PDF added, Fixed blank check processing
*************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_datfrx_rx_config.h"
#include "platform.h"
#include "r_flash_dm_rx_if.h"
#include "Flash.h"
#include "globals.h"
#include "All_Header.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Please set the number of loops. */
#define LOOP_CNT (1)
/* Please set the maximum data size. */
//#define TEST_BUFF_NUM (255)
extern void Clr_WatchDog();
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum _datfrx_status
{
    DATFRX_IDLE,
    DATFRX_RUN_FORMAT,
    DATFRX_SUCCESS_INIT,
    DATFRX_FINISH_FORMAT,
    DATFRX_FINISH_WRITE,
    DATFRX_FINISH_ERASE,
    DATFRX_FINISH_RECLAIM,
    DATFRX_ERR
} e_datfrx_status_t;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Private variables and functions
***********************************************************************************************************************/
static void trap(uint32_t test_no);
//static void test_data_set(uint8_t * p_buf, uint32_t cnt, uint32_t inc);
//static void testinit(void);
////static void testmain(void);
//static void testmain(uint8_t gs_test_w_buff[]);
//static void testwrite(void);

static void testwrite(uint32_t gs_test_w_buff[]);
static void ucb_function(void* error_code);
void erase(void);
void open_dataflash();

#if(FLASH_TYPE == FLASH_TYPE_1)
static uint32_t gs_flash_dm_work[140/sizeof(uint32_t)];
#else
static uint32_t gs_flash_dm_work[(261 + (FLASH_DM_CFG_DF_DATA_NUM * 2))/sizeof(uint32_t)+1];
#endif

//uint8_t gs_test_w_buff[TEST_BUFF_NUM]={'q','w','e','r','t','y','u','i'};

uint32_t gs_test_w_buff[TEST_BUFF_NUM];

uint32_t gs_test_r_buff[TEST_BUFF_NUM];

st_flash_dm_info_t g_flash_dm_info;
uint16_t g_data_num = FLASH_DM_CFG_DF_DATA_NUM - 1;
volatile uint32_t g_loop_cnt = 0;
volatile uint32_t g_proc_flag = DATFRX_IDLE;

/**********************************************************************************************************************
* Outline      : ERROR Processing
* Function Name: trap
* Description  : Error
* Arguments    : -
* Return Value : -
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
static void trap(uint32_t test_no)
{
    while(test_no)
    {
        /* Do Nothing. */
        nop();
    };
}

/**********************************************************************************************************************
* Outline      : Test Data Setting Processing
* Function Name: test_data_set
* Description  : Sets test data.
* Arguments    : uint32_t * p_buf       ; Pointer of test buffer.
*              : uint32_t   cnt         ; Test block number.
*              : uint32_t   inc         ; Loop count
* Return Value : None
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
/*static void test_data_set(uint8_t * p_buf, uint32_t cnt, uint32_t inc)
{
    uint32_t  i;

    for (i = 0; i < cnt; i++)
    {

        *p_buf++ = (uint8_t)(i + inc);
    }
}
*/
/**********************************************************************************************************************
* Function Name: testwrite
* Description  : testwrite
* Arguments    : void
* Return Value : void
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
static void testwrite(uint32_t gs_test_w_buff[])
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    /* ==== WRITE ==== */
    //test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
    g_flash_dm_info.data_no = g_data_num;
    /* cast from uint32_t to uint8_t* */
    g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
    ret = R_FLASH_DM_Write(&g_flash_dm_info);

    if(ret == FLASH_DM_ERR_REQUEST_ERASE)
    {
        ret = R_FLASH_DM_Erase();
        if(ret != FLASH_DM_ACCEPT)
        {
            trap(1);
        }
    }


    #if(FLASH_TYPE == 1)
    else if(ret == FLASH_DM_ERR_REQUEST_RECLAIM)
    {
        ret = R_FLASH_DM_Reclaim();
        if(ret == FLASH_DM_ERR_REQUEST_ERASE)
        {
            ret = R_FLASH_DM_Erase();
            if(ret != FLASH_DM_ACCEPT)
            {
                trap(2);
            }
        }
        else if(ret != FLASH_DM_ACCEPT)
        {
            trap(3);
        }
        else
        {
            // Do Nothing
        }
    }
#endif
    else if(ret != FLASH_DM_ACCEPT)
    {
        trap(4);
    }
    else
    {
        // Do Nothing
    }
}

/**********************************************************************************************************************
* Outline      : testinit
* Function Name: testinit
* Description  : Error
* Arguments    : void
* Return Value : void
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
static void init_dataflash(void)
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

#if(FLASH_TYPE == FLASH_TYPE_1)
    /* ==== INITIALIZE ==== */
    ret = R_FLASH_DM_Init();

    if(ret == FLASH_DM_SUCCESS)
    {
        g_proc_flag = DATFRX_SUCCESS_INIT;
    }
    else if(ret == FLASH_DM_SUCCESS_REQUEST_ERASE)
    {
        ret = R_FLASH_DM_Erase();
        if(ret != FLASH_DM_ACCEPT)
        {
            trap(5);
        }
    }
    else if(ret == FLASH_DM_ERR_BUSY)
    {
        /* === CONTINUE TO LOOP ===*/
        /* Do Nothing */
        nop();
    }
    else if(ret == FLASH_DM_ERR_REQUEST_FORMAT)
    {
        ret = R_FLASH_DM_Format();
        if(ret != FLASH_DM_ACCEPT)
        {
            trap(6);
        }
        else
        {
            g_proc_flag = DATFRX_RUN_FORMAT;
        }
    }
    else
    {
        trap(7);
    }

#else/* FLASH_TYPE */

    while(1)
    {
        /* ==== INITIALIZE ==== */
        ret = R_FLASH_DM_Init();
       if(ret == FLASH_DM_ADVANCE)
        {
            break;
        }
       if(ret == FLASH_DM_SUCCESS_REQUEST_ERASE)
        {
            ret = R_FLASH_DM_Erase();
            if(ret != FLASH_DM_ACCEPT)
            {
                trap(8);
            }
        }
        else if(ret == FLASH_DM_ERR_BUSY)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else
        {
            trap(9);
        }
    }

    while(1)
    {
        ret = R_FLASH_DM_InitAdvance();
        if(ret == FLASH_DM_SUCCESS)
        {
            g_proc_flag = DATFRX_SUCCESS_INIT;
            break;
        }
        else if(ret == FLASH_DM_ADVANCE)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else if(ret == FLASH_DM_ERR_BUSY)
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            nop();
        }
        else if(ret == FLASH_DM_ERR_REQUEST_FORMAT)
        {
            ret = R_FLASH_DM_Format();
            if(ret != FLASH_DM_ACCEPT)
            {
                trap(10);
            }
            else
            {
                g_proc_flag = DATFRX_RUN_FORMAT;
            }
            break;
        }
        else
        {
            /* === CONTINUE TO LOOP ===*/
            /* Do Nothing */
            trap(11);
        }
    }
#endif /* FLASH_TYPE */
}

/**********************************************************************************************************************
* Function Name: testmain
* Description  : testmain.
* Arguments    : void
* Return Value : void
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/

void write_calib_data(uint32_t gs_test_w_buff[])
{
	Clr_WatchDog();
    /* === OPEN ===*/
    if(FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        trap(12);
    }

    do
    {
    	init_dataflash();                  //initialising dataflash
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);

    g_data_num = 0;

    testwrite(gs_test_w_buff);

    do
    {
        // Do nothing. wait for dataflash to write
    }
    while(g_loop_cnt < LOOP_CNT);


    R_FLASH_DM_Close();
    Clr_WatchDog();
}

void read_calib_data(void)
{
	Clr_WatchDog();
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    /* === OPEN ===*/
    if (FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
    {
        trap(13);
    }

    do
    {
    	init_dataflash();
        /* Do Nothing */
        while(g_proc_flag == DATFRX_RUN_FORMAT)
        {
            /* Do Nothing */
        }
    }
    while(g_proc_flag != DATFRX_SUCCESS_INIT);

    g_data_num = 0;

    do
    {
        /* ====  VERYFY ==== */
        g_flash_dm_info.data_no = g_data_num;
        /* cast from uint32_t to uint8_t* */
        g_flash_dm_info.p_data  = (uint8_t *)&gs_test_r_buff[0];
        ret = R_FLASH_DM_Read(&g_flash_dm_info);

        if(ret != FLASH_DM_SUCCESS)
        {
            trap(14);
        }
        else if(ret == FLASH_DM_ERR_DATA_NOT_PRESENT)
        {

            trap(15);
        }
        else
        {
            /* Do Nothing. */
            nop();
        }
        g_data_num++;
    }while(g_data_num < LOOP_CNT);
    /*IN ONE LOOP COUNT 255 DATABYTE CAN BE READ WRITE
    dataflash type 1
    block 0 real start address 0x0010 0000
    block 0 real end address 0x0010 03FF*/
    /* ==== CLOSE ==== */
    R_FLASH_DM_Close();
    Clr_WatchDog();
}

void erase(void)
{
	uint8_t i;
	for(i=0;i<TEST_BUFF_NUM;i++)
	{
		gs_test_w_buff[i] = 0xFF;
	}
	write_calib_data(gs_test_w_buff);
}

void open_dataflash()
{
	Clr_WatchDog();
	    /* === OPEN ===*/
	    if(FLASH_DM_SUCCESS != R_FLASH_DM_Open(gs_flash_dm_work, &ucb_function))
	    {
	        trap(12);
	    }

	    do
	    {
	    	init_dataflash();                  //initialising dataflash
	        /* Do Nothing */
	        while(g_proc_flag == DATFRX_RUN_FORMAT)
	        {
	            /* Do Nothing */
	        }
	    }
	    while(g_proc_flag != DATFRX_SUCCESS_INIT);

	    g_data_num = 0;

	    R_FLASH_DM_Close();
	    Clr_WatchDog();
}
/**********************************************************************************************************************
* Function Name: main
* Description  : main.
* Arguments    : void
* Return Value : void
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
/*void main(void)
{


	//erase();
    testmain(gs_test_w_buff);
    testmain_restoration();

   // erase();
    //testmain_restoration();
    while(1);
}*/

/**********************************************************************************************************************
* Function Name: ucb_function
* Description  : callback function.
* Arguments    : void
* Return Value : void
*----------------------------------------------------------------------------------------------------------------------
* Notes        : None
**********************************************************************************************************************/
static void ucb_function(void* error_code)
{
    e_flash_dm_status_t ret = FLASH_DM_SUCCESS;

    uint32_t i;
    uint32_t* pcfg;
    uint32_t data_size = 0;

    pcfg = &data_size;

    /* ==== SUCCESS ==== */
    /* cast from void* to e_flash_dm_status_t*/
    switch((e_flash_dm_status_t)error_code)
    {
        case FLASH_DM_FINISH_FORMAT:
        {
            g_proc_flag = DATFRX_FINISH_FORMAT;
            break;
        }
        break;

        case FLASH_DM_FINISH_WRITE :
        {
            g_proc_flag = DATFRX_FINISH_WRITE;
            /* ====  VERYFY ==== */
            g_flash_dm_info.data_no = g_data_num;
            /* cast from uint32_t to uint8_t* */
            g_flash_dm_info.p_data  = (uint8_t *)&gs_test_r_buff[0];
            ret = R_FLASH_DM_Read(&g_flash_dm_info);
            *pcfg = g_data_num;
            ret = R_FLASH_DM_Control(FLASH_DM_GET_DATA_SIZE, pcfg);
            //test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);

            for(i = 0; i < data_size ; i++)
            {
                if(gs_test_w_buff[i] != gs_test_r_buff[i])
                {
                    trap(16);
                }
            }

            /* ==== INCREASE COUNT & CLOSE CONFIRMATION ==== */
            if((++g_loop_cnt) >= LOOP_CNT)
            {
                break;
            };

            /* ==== Switch WRITTING DATANUMBER ==== */
            g_data_num = g_loop_cnt % FLASH_DM_CFG_DF_DATA_NUM;

            /* ==== WRITE ==== */
            //test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
            g_flash_dm_info.data_no = g_data_num;
            /* cast from uint32_t to uint8_t* */
            g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
            ret = R_FLASH_DM_Write(&g_flash_dm_info);
            if(ret == FLASH_DM_ERR_REQUEST_ERASE)
            {
                ret = R_FLASH_DM_Erase();
                if(ret != FLASH_DM_ACCEPT)
                {
                    trap(17);
                }
            }
#if(FLASH_TYPE == FLASH_TYPE_1)
            else if(ret == FLASH_DM_ERR_REQUEST_RECLAIM)
            {
                ret = R_FLASH_DM_Reclaim();
                if(ret == FLASH_DM_ERR_REQUEST_ERASE)
                {
                    ret = R_FLASH_DM_Erase();
                    if(ret != FLASH_DM_ACCEPT)
                    {
                        trap(18);
                    }
                }
                else if(ret != FLASH_DM_ACCEPT)
                {
                    trap(19);
                }
                else
                {
                    /* Do Nothing */
                }
            }
#endif/* FLASH_TYPE_1 */
            else if(ret != FLASH_DM_ACCEPT)
            {
                trap(20);
            }
            else
            {
                /* Do Nothing */
            }
        }
        break;

        case FLASH_DM_FINISH_ERASE :
        {
            g_proc_flag = DATFRX_FINISH_ERASE;
            /* ==== ERASE ==== */
            ret = R_FLASH_DM_Erase();
            if(ret == FLASH_DM_NO_INVALID_BLOCK)
            {
                /* ==== Switch WRITTING DATANUMBER ==== */
                g_data_num = g_loop_cnt % FLASH_DM_CFG_DF_DATA_NUM;

                /* ==== WRITE ==== */
                //test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
                g_flash_dm_info.data_no = g_data_num;
                /* cast from uint32_t to uint8_t* */
                g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
                ret = R_FLASH_DM_Write(&g_flash_dm_info);
#if(FLASH_TYPE == FLASH_TYPE_1)
                if(ret == FLASH_DM_ERR_REQUEST_RECLAIM)
                {
                    ret = R_FLASH_DM_Reclaim();
                    if(ret == FLASH_DM_ERR_REQUEST_ERASE)
                    {
                        ret = R_FLASH_DM_Erase();
                        if(ret != FLASH_DM_ACCEPT)
                        {
                            trap(21);
                        }
                    }
                    else if(ret != FLASH_DM_ACCEPT)
                    {
                        trap(22);
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else
#endif/* FLASH_TYPE_1 */
                if(ret != FLASH_DM_ACCEPT)
                {
                    trap(23);
                }
                else
                {
                    /* Do Nothing */
                }
            }
            else if(ret != FLASH_DM_ACCEPT)
            {
                trap(24);
            }
            else
            {
                /* Do Nothing */
            }
        }
        break;

#if(FLASH_TYPE == FLASH_TYPE_1)
        case FLASH_DM_FINISH_RECLAIM :
        {
            g_proc_flag = DATFRX_FINISH_RECLAIM;
            /* ==== WRITE ==== */
            //test_data_set(&gs_test_w_buff[0], TEST_BUFF_NUM, g_loop_cnt);
            g_flash_dm_info.data_no = g_data_num;
            /* cast from uint32_t to uint8_t* */
            g_flash_dm_info.p_data  = (uint8_t *)&gs_test_w_buff[0];
            ret = R_FLASH_DM_Write(&g_flash_dm_info);
            if(ret == FLASH_DM_ERR_REQUEST_ERASE)
            {
                ret = R_FLASH_DM_Erase();
                if(ret != FLASH_DM_ACCEPT)
                {
                    trap(25);
                }
            }
            else if(ret != FLASH_DM_ACCEPT)
            {
                trap(26);
            }
            else
            {
                /* Do Nothing */
            }
        }
        break;
#endif/* FLASH_TYPE_1 */

        /* ==== FAILD ==== */
        case FLASH_DM_ERR_FORMAT:
        case FLASH_DM_ERR_WRITE :
        case FLASH_DM_ERR_ERASE :
        case FLASH_DM_ERR_RECLAIM:
        {
            g_proc_flag = DATFRX_ERR;
            trap(27);
        }
        break;
        default :
        {
            trap(28);
        }
        break;
    }
}



