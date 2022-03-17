/*
 * ADC_CS5532.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#ifndef ADC_CS5532_H_
#define ADC_CS5532_H_

#ifndef ADC_VAR
# define _ADC extern
# define _ADC_INIT(x)
#else
# define _ADC
# define _ADC_INIT(x)  = x
#endif

//////////////////////////


/*struct bit_define
{
    char  f0:1;
    char  f1:1;
    char  f2:1;
    char  f3:1;
    char  f4:1;
    char  f5:1;
    char  f6:1;
    char  f7:1;
};

union  byte_define
{
  	struct bit_define f_bit;
  	unsigned char   f_byte;
}_ADC CS5532_Flag;
*/
/*union
{
unsigned int temp_ch1;
unsigned char temp_ch2, temp_ch3
}temp_explain;

temp_explain.temp_ch1= 0xFFAA;
*/

extern union  byte_define     segsnew,segsold,gPhaseNo,ledbits,flag1,tmpbits;
//union byte_define	CS5532_Flag;
/*
#define	read_asic_f    		CS5532_Flag.f_bit.f0
#define	ad_time_out_flag	CS5532_Flag.f_bit.f1
#define	adflag				CS5532_Flag.f_bit.f2
//#define	adc_stable    		CS5532_Flag.f_bit.f3
#define	asicvarsign    		CS5532_Flag.f_bit.f4
*/
/*Changes regarding the Speed and the Gain of the ADC Sample for  the Load Cell*/


void Reset_Asic(void);
void init_asic(void);
unsigned long int TransRec_5b(unsigned char mtrs0, unsigned char mtrs1, unsigned char mtrs2, unsigned char mtrs3, unsigned char mtrs4);
unsigned long int Read_Asic(void);
void Trans_byte(char trnsbyte);
void Asic_start(void);
void read_adc(void);
void check_stable(void);
unsigned long int  absolute_diff(unsigned long int Value1,unsigned long int Value2);
void CS5532_WaitDelay(char delaycnt);
void mS_Delay(unsigned int mS);
void calculate_weight(void);
void sampling();
//void Clr_WatchDog(void);

void Delay_Loop(unsigned long int Cnt);



#endif /* ADC_CS5532_H_ */
