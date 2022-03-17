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
* File Name    : r_cg_userdefine.h
* Version      : 1.1.104
* Device(s)    : R5F52315AxFL
* Description  : User header file for code generation.
* Creation Date: 2021-10-01
***********************************************************************************************************************/

#ifndef CG_USER_DEF_H
#define CG_USER_DEF_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/* Start user code for register. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Start user code for macro define. Do not edit comment generated here */
#define ENB_FB	PORTB.PODR.BIT.B5	// Enable Pin for Stepper 1
#define ENB_WB	PORTB.PODR.BIT.B3	// Enable Pin for Stepper 2

#define CLK_FB	PORT2.PODR.BIT.B7	// Clock Pin of the Stepper 1
#define CLK_WB	PORT2.PODR.BIT.B6	// Clock Pin of the Stepper 2

#define DIR_FB	PORTB.PODR.BIT.B0	// Direction pin of the Stepper 1
#define DIR_WB	PORTA.PODR.BIT.B6	// Direction pin of the Stepper 2

#define HOP_FB	PORTA.PODR.BIT.B4	// Homing output signal for the Stepper
#define HOP_WB	PORTA.PODR.BIT.B3	// Homing output signal for the Stepper

#define HIN_WB	PORT3.PIDR.BIT.B1	// Homing input signal from the Photo-interrupter
#define HIN_FB	PORT3.PIDR.BIT.B5	// Homing input signal from the Photo-interrupter

#define SCS_Pin		PORT4.PODR.BIT.B6	// Chip select Pin for the CS5532
#define SCLK_Pin	PORTE.PODR.BIT.B4	// Clock pin for the CS5532, Micro-Controller = OUT, CS5532 ADC = IN
#define SDI_Pin		PORT1.PODR.BIT.B6	// Receive Pin of the CS5532, Micro-Controller = OUT, CS5532 ADC = IN
#define SDO_Pin		PORT1.PIDR.BIT.B7	// Transmit pin of the CS5532, Micro-Controller = IN, CS5532 ADC = OUT

#define DIP1		PORTC.PIDR.BIT.B6	// Slave Address Pin of the card
#define DIP2		PORTC.PIDR.BIT.B5	// Slave Address Pin of the card
#define DIP3		PORTC.PIDR.BIT.B4	// Slave Address Pin of the card
#define DIP4		PORTA.PIDR.BIT.B1	// Slave Address Pin of the card

#define CPin		PORTE.PODR.BIT.B1
//#define ZCIP		PORT3.PIDR.BIT.B0
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Start user code for type define. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif

