/*
 * PWM.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#ifndef PWM_H_
#define PWM_H_


#ifndef VAR_PWM
# define _PWM extern
# define _PWM_INIT(x)
#else
# define _PWM
# define _PWM_INIT(x)  = x
#endif


//_PWM unsigned char 	Pulses_SCR;

void PWM_ISR(void);

//_PWM unsigned int 	VBT_Cntr;
//_PWM unsigned char 	Pulses_SCR;

//void PWM_Start(void);
//void PWM_Stop(void);

//void PWM_ISR(void);


#endif /* PWM_H_ */
