/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Config_MTU0.c
* Version      : 1.10.0
* Device(s)    : R5F52315AxFL
* Description  : This file implements device driver for Config_MTU0.
* Creation Date: 2021-10-01
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_MTU0.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MTU0_Create
* Description  : This function initializes the MTU0 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU0_Create(void)
{
    /* Release MTU channel 0 from stop state */
    MSTP(MTU0) = 0U;

    /* Stop MTU channel 0 counter */
    MTU.TSTR.BIT.CST0 = 0U;

    /* Set TGIA/TGIB/TGIC/TGID interrupt priority level */
    IPR(MTU0, TGIA0) = _0D_MTU_PRIORITY_LEVEL13;

    /* MTU channel 0 is used as PWM mode 1 */
    MTU.TSYR.BIT.SYNC0 = 0U;
    MTU0.TCR.BYTE = _01_MTU_PCLK_4 | _00_MTU_CKEG_RISE | _20_MTU_CKCL_A;
    MTU0.TIER.BYTE = _01_MTU_TGIEA_ENABLE | _00_MTU_TGIEB_DISABLE | _00_MTU_TGIEC_DISABLE | _00_MTU_TGIED_DISABLE | 
                     _00_MTU_TCIEV_DISABLE | _00_MTU_TTGE_DISABLE;
    MTU0.TIER2.BYTE = _00_MTU_TGIEE_DISABLE | _00_MTU_TGIEF_DISABLE;
    MTU0.TMDR.BYTE = _02_MTU_PWM1;
    MTU0.TIORH.BYTE = _00_MTU_IOA_DISABLE;
    MTU0.TIORL.BYTE = _05_MTU_IOC_HL | _70_MTU_IOD_HT;
    MTU0.TGRA = _0F9F_TGRA0_VALUE;
    MTU0.TGRB = _0001_TGRB0_VALUE;
    MTU0.TGRC = _0BB8_TGRC0_VALUE;
    MTU0.TGRD = _0001_TGRD0_VALUE;
    MTU0.TGRE = _000A_TGRE0_VALUE;
    MTU0.TGRF = _000A_TGRF0_VALUE;

    /* Set MTIOC0C pin */
    MPC.PB1PFS.BYTE = 0x01U;
    PORTB.PMR.BYTE |= 0x02U;

    R_Config_MTU0_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU0_Start
* Description  : This function starts the MTU0 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU0_Start(void)
{
    /* Enable TGIA0 interrupt in ICU */
    IEN(MTU0, TGIA0) = 1U;
    
    /* Start MTU channel 0 counter */
    MTU.TSTR.BIT.CST0 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU0_Stop
* Description  : This function stops the MTU0 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU0_Stop(void)
{
    /* Disable TGIA0 interrupt in ICU */
    IEN(MTU0, TGIA0) = 0U;
    
    /* Stop MTU channel 0 counter */
    MTU.TSTR.BIT.CST0 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
