/*
 * Timer.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#ifndef TIMER_H_
#define TIMER_H_

#ifndef TIM_VAR
# define _TIM extern
# define _TIM_INIT(x)
#else
# define _TIM
# define _TIM_INIT(x)  = x
#endif



_TIM unsigned int	mS_Cnt;
_TIM unsigned int mscount;
_TIM volatile _Bool ms100_flag;
_TIM volatile _Bool msflag;

//_TIM unsigned int 	VBT_Cntr;



/////zcdip/////
//_TIM unsigned int 	VBT_Cntr;
//_TIM unsigned int	SD_LF_TMR;				// Linear feeder Start Delay Timer
		// Start Delay of Time of the Linear feeder
			// Number cycle to be fired
//_TIM unsigned int lf_time_taken_flag;


//_TIM _Bool VBRT_Half;


void Timer0_IT_ISR(void);
void Init_Vals(void);
//void Clr_WatchDog(void);
void Timer2_FBucket_ISR(void);
void mS_Delay(unsigned int mS);
void Timer1_FAngle_ISR(void);

void ISR_ZCIP(void);
void PWM_ISR(void);

#endif /* TIMER_H_ */
