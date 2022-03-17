/*
 * RUN_OP.h
 *
 *  Created on: Feb 17, 2022
 *      Author: Pustake
 */

#ifndef RUN_OP_H_
#define RUN_OP_H_

#ifndef RUN_VAR
# define _RUN extern
# define _RUN_INIT(x)
#else
# define _RUN
# define _RUN_INIT(x)  = x
#endif





void RunOperation(void);
#endif /* RUN_OP_H_ */
