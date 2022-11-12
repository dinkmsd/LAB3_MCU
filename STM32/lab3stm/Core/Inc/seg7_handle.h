/*
 * seg7_handle.h
 *
 *  Created on: 12 Nov 2022
 *      Author: xanlo
 */

#ifndef INC_SEG7_HANDLE_H_
#define INC_SEG7_HANDLE_H_

void led_init();
void led_clear();

void display7SEG(int num);
void update_buffer();
void update_buffer_no();
void update7SEG(int index);

#endif /* INC_SEG7_HANDLE_H_ */
