/*
 * Stepper_Motor_Varib.h
 *
 *  Created on: Mar 9, 2022
 *      Author: Pustake
 */

#ifndef STEPPER_MOTOR_VARIB_H_
#define STEPPER_MOTOR_VARIB_H_

#ifndef STEPPER_VAR
# define _STEPPER extern
# define _STEPPER_INIT(x)
#else
# define _STEPPER
# define _STEPPER_INIT(x)  = x
#endif




#endif /* STEPPER_MOTOR_VARIB_H_ */
