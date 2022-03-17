/*
 * Flash.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Pustake
 */

#ifndef FLASH_H_
#define FLASH_H_


#define TEST_BUFF_NUM (5)



void read_calib_data(void);
void write_calib_data(uint32_t gs_test_w_buff[]);
void open_dataflash();
void erase();

void r_flash_dm_d1_format(void);




#endif /* FLASH_H_ */
