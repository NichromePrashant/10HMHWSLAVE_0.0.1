/*
 * Calibration_Varib.h
 *
 *  Created on: Mar 9, 2022
 *      Author: Pustake
 */

#ifndef CALIBRATION_VARIB_H_
#define CALIBRATION_VARIB_H_


#ifndef CALIBRATION_VAR
# define _CALIBRATION extern
# define _CALIBRATION_INIT(x)
#else
# define _CALIBRATION
# define _CALIBRATION_INIT(x)  = x
#endif





//_CALIBRATION _Bool Calibeate_Flag;


//_CALIBRATION signed int 	CSI_TareCnt _CALIBRATION_INIT(0);

//_CALIBRATION signed int	CSI_CalibSlope;
//_CALIBRATION signed int	CSI_CalibCnt;



#endif /* CALIBRATION_VARIB_H_ */
