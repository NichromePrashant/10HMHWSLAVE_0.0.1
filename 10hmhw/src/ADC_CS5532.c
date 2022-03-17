/*
 * ADC_CS5532.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */
#define ADC_VAR
#include "ADC_CS5532.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_port.h"
#include <stdio.h>              // sprintf()
#include <string.h>             // strlen()
#include "platform.h"           // Located in the FIT BSP module
#include "r_sci_rx_if.h"        // The SCI FIT module API interface file.
#include "r_rscan_rx_if.h"
#include "r_cg_wdt.h"
#include "r_cg_cmt.h"
#include "Config_ICU.h"
#include "Timer.h"
#include "globals.h"
#include "can.h"
#include "math.h"
#include "ADC_CS5532_Variable.h"
#include "All_Header.h"
#include "can_Varib.h"
#include "r_rscan_rx_if.h"



unsigned int  disp,disp2;
const char GainTable[8]    = {0x00,0x08,0x10,0x18,0x20,0x28,0x30};
const char SpeedTableH[10] = {0x02,0x01,0x01,0x00,0x00,0x06,0x05,0x05,0x04,0x04};
const char SpeedTableL[10] = {0x00,0x80,0x00,0x80,0x00,0x00,0x80,0x00,0x80,0x00};
unsigned long int	adc_buff[300+1],sort_buff[300+1];
unsigned int 		adptr;
unsigned long int 	asic_value,last_asic_value;

extern can_txmsg_t         g_txmsg;
extern can_rxmsg_t         g_rxmsg;

//signed int last_adc_count;
//unsigned char 		adc_stable;
unsigned char 		fluct_count;
//unsigned int	mS_Cnt;





void CS5532_WaitDelay(char delaycnt)
{
	unsigned char i;

	for(i=0;i<delaycnt;i++)
	{

		Clr_WatchDog();			// Clear watch dog timer
	}
}

void Reset_Asic(void)
{
	unsigned int i;
	unsigned long int 	temp0;

	CS5532_WaitDelay(2);				//5

	for(i=0;i<16;i++)
	{
		Trans_byte(0xFF);			 	// Reset ADC
	}

	Trans_byte(0xFE);
	TransRec_5b(0x03,0x22,0,0,0);		// write to configuration register RS bit = 1
	for(i=0;i<1000;i++);				// Wait here for 1000 machine cycles
	TransRec_5b(0x03,0x02,0,0,0);		// write to configuration register RS bit = 0
	for(i=0;i<1000;i++);				// Wait here for 1000 machine cycles
	temp0 = 0;
	while((temp0&0x10)==0)
	{
		 temp0 = TransRec_5b(0x0B,0x02,0,0,0);			//Wait for RV  bit to set, i.e. end of reset
		 temp0>>=16;				                  	//m_rcv[1]
	     Clr_WatchDog();    ///10032022			                    // Clear Watch dog timer and reset

	}
	GUI_state =6;
}



void init_asic(void)
{
	unsigned int  idx;
	unsigned char var1,var2;
	var1=GainTable[AUI_GAIN-1]|SpeedTableH[AUI_SPEED-1];
	var2=SpeedTableL[AUI_SPEED-1]|0x40;
	TransRec_5b(0x05,var1,var2,var1,var2);	            //Initialize ADC for Gain = 16 , word rate = 30sps (0000)
	for(idx=0;idx<1000;idx++);
	TransRec_5b(0x02,0x01,0x00,0x00,0x00);	            //Store Gain = 1.0000000
	GUI_state = 7;
}


unsigned long int TransRec_5b(unsigned char mtrs0, unsigned char mtrs1, unsigned char mtrs2, unsigned char mtrs3, unsigned char mtrs4)
{
	unsigned char 	i,maskdata,readdata;
	unsigned char 	m_rcv[5],m_trs[5],opr_data[4];
	unsigned long int 	temp0,temp1;
	m_trs[0]=mtrs0;
	m_trs[1]=mtrs1;
	m_trs[2]=mtrs2;
	m_trs[3]=mtrs3;
	m_trs[4]=mtrs4;
	for(i=0; i<5; i++)
	{
		 m_rcv[i] = 0x00;		// Reset the receive buffer
	}
	asicvarsign = 0;
	SCS_Pin=0;		// 1
	SCLK_Pin=1;
	SDI_Pin=1;
	CS5532_WaitDelay(5);
	SCS_Pin=1;		// 0
	CS5532_WaitDelay(3);
	for(i=0;i<5;i++)
	{
		maskdata=0x80;
		while (maskdata)
		{
			readdata = m_rcv[i] | maskdata;
			if (m_trs[i]& maskdata) 		// Actual "H" output
			 SDI_Pin = 0;					// Actual SDI_Pin = "H"
			else
			 SDI_Pin = 1;					// Actual SDI_Pin = "L"
			if(SDO_Pin == 0)				// Actual SDO_Pin = "H"
			 m_rcv[i] = readdata;
			maskdata >>= 1;
			SCLK_Pin=0;						// Actual SCLK_Pin = "H"
	 	CS5532_WaitDelay(5);
			SCLK_Pin=1;						// Actual SCLK_Pin = "L"
			CS5532_WaitDelay(3);
		}
	}
	SCS_Pin=1;		                    // 0
	m_rcv[0]=0;				            // Unknown byte received from the CS5532
	opr_data[3] = 0x00;
	opr_data[2] = m_rcv[1];
	opr_data[1] = m_rcv[2];
	opr_data[0] = m_rcv[3];
	temp1 = 0x00;
	temp1 = opr_data[3];
	temp1 <<=8;
	temp0 = opr_data[2];
	temp1 = temp1 | temp0;
	temp1 <<=8;
	temp0 = opr_data[1];
	temp1 = temp1 | temp0;
	temp1 <<=8;
	temp0 = opr_data[0];
	temp0 = temp1 | temp0;
	return temp0;
}


void Delay_Loop(unsigned long int Cnt)
{
	unsigned int i,j;
	for(i=0; i<=Cnt;i++)
	 for(j = 0; j <= 100; j++)
      Clr_WatchDog();  //
}

unsigned long int Read_Asic(void)
{
	unsigned long int temp0;
	temp0 = TransRec_5b(0,0,0,0,0);
	return temp0;
}


void Trans_byte(char trnsbyte)
{
	char maskdata;

	SCS_Pin=0;
	SCLK_Pin=1;
	SDI_Pin=1;
	CS5532_WaitDelay(5);	//5
	SCS_Pin=1;
	CS5532_WaitDelay(3);	//2
	maskdata=0x80;
	while(maskdata)
	{
	   Clr_WatchDog();    //100320222			// Clear Watch Dog Timer and Reset
		if(trnsbyte & maskdata)	// Mask the output bit to be send over SPI
			SDI_Pin=0;			// Yes SDA="H"
		else
			SDI_Pin=1;			// No  SDA="L"
		maskdata >>= 1;
		SCLK_Pin=0;				// Set clock pin high
		CS5532_WaitDelay(5);	//5
		SCLK_Pin=1;				// Set clock pin low
		CS5532_WaitDelay(3);	//2
	}
	    CS5532_WaitDelay(3);		//2
	SCS_Pin=0;				// Set chip select pin
}


void Asic_start(void)
{
	Trans_byte(0xC0);				 //Start Conversion r phase
	GUI_state = 8;
}

void read_adc(void)
{
		unsigned char 	ad_time_out_count;
		//unsigned char 	adci;

		ad_time_out_count=250;
		ad_time_out_flag = 0;
		read_asic_f=0;
		SCS_Pin=1;
		CS5532_WaitDelay(5);		//waits till the adc is ready

		while(SDO_Pin == 0)
		{

			Clr_WatchDog();     ///10032022
			if(ad_time_out_flag!=0)
			{
				ad_time_out_flag=0;
				ad_time_out_count--;

				if(ad_time_out_count==0)
				{
					SCS_Pin=0;
					Delay_Loop(6000);                  //
					Reset_Asic();                      //
					Delay_Loop(6000);                  //
					init_asic();                       //
					Asic_start();                      //
					Delay_Loop(6000);                  //
					fluct_count=0;
					return;
				}
			}
			Clr_WatchDog();         //10032022

		}

		read_asic_f=1;
		asic_value=Read_Asic();								   // Read the ADC count for the Load Cell Operation.
		asic_value=asic_value>>0;				               //4	// Changes Need to be done for the ADC resolution.
		read_asic_f=0;
		asic_value=asic_value*100;
		asic_value=asic_value/5269;
		adc_buff[adptr]=asic_value;
		adptr++;

		if(adptr>(ADSAMPLES-1))
		{
			adptr=0;
		}
		   sampling();
	       adflag=1;		                           //find effective count and call check_stable
}

void calculate_weight(void)
{

	CurrentWt = (signed int)(((ASI_adc_count - CSI_TareCnt)*3000)/CSI_CalibSlope);

}

void sampling()
{
	int k;
	for(k=0;k<4;k++)                               ///4
	{
		disp+=adc_buff[k];
	}

	  disp  = disp/4;                              ///4
	  disp2 = disp;
	  disp  = 0;
	  //disp2=disp2-22368;
	  ASI_adc_count = disp2;
}

unsigned long int  absolute_diff(unsigned long int Value1,unsigned long int Value2)
{
	if(Value1>Value2)
	return Value1-Value2;
	else return Value2-Value1;
}


/*The function used to check wheather the ADC Count are in range*/

void check_stable(void)
{
	int diff_cnt;

	if(adflag==1)
	{
		adflag = 0;

		diff_cnt = absolute_diff(ASI_adc_count,ASI_last_adc_count);       //sg for test asic_value== adc count;

   	if((diff_cnt < Diff_Cnt_Val)&&(AUI_adc_stable==0))
		{
			if(stable_count<250)
				stable_count++;

	if(stable_count > Stable_Count_Val)
			{
		AUI_adc_stable = 1;
			}
		}

		if((diff_cnt > (Diff_Cnt_Val*2))&&(AUI_adc_stable==1))         // this is original code
		//if((diff_cnt > (Diff_Cnt_Val ))&&(adc_stable==1))             // written by Dnyaneshwar 1/12/21
		{
			AUI_adc_stable      = 0;
			auto_zero_count = 0;
			stable_count    = 0;
		}
		ASI_last_adc_count= ASI_adc_count;                       //done asic_value to adc count
	}
}



/*
void sort_buffer(unsigned long int *maxwt_bf,char cnt)		// to sort the buffer in the descending order
{
	unsigned char i,j;
	unsigned long int temp;

	for(i=0;i<cnt;i++)
	{
		sort_buff[i]=*(maxwt_bf+i);		    // Copy the received buffer into sort buffer
	}
	for(i=1;i<(cnt-1);i++)				    // To sort the complete sort buffer
	{
		for(j=0;j<(cnt-i);j++)			    // to sort single entry of the sort buffer
		{
			if(sort_buff[j]>sort_buff[j+1])
			{
				temp=sort_buff[j];
				sort_buff[j]=sort_buff[j+1];
				sort_buff[j+1]=temp;
			}
		}
	}
}

*/

