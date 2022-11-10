/*
 * global.h
 *
 *  Created on: Nov 3, 2022
 *      Author: xanlo
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <main.h>

#define INIT 					0
#define NORMAL_RED 				1
#define NORMAL_GREEN 			2
#define NORMAL_YELLOW 			3
#define MAN_RED 		4
#define MAN_YELLOW 		5
#define MAN_GREEN		6

#define ON_7SEG                  GPIO_PIN_RESET
#define OFF_7SEG                 GPIO_PIN_SET

#define RED_TIME		500
#define GREEN_TIME		300
#define YELLOW_TIME 	200

#define RED_NORMAL_TIME  	500
#define YELLOW_NORMAL_TIME 	200
#define GREEN_NORMAL_TIME 	300


#define MAN_RED_TIME	1000
#define MAN_GREEN_TIME	700
#define MAN_YELLOW_TIME	500

extern int index_mode;
extern int time0;
extern int time1;
extern int status;
extern int CURRENT_STATE[2];
extern int SEG7_CLOCK[2];
extern int led_seg_buffer[4];
extern int LED_TIME[3];
extern int TIMES_INC;
extern int start;


#define RED 		12
#define GREEN 		13
#define YELLOW		14


#endif /* INC_GLOBAL_H_ */
