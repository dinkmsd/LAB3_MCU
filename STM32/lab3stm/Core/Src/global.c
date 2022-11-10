/*
 * global.c
 *
 *  Created on: Nov 10, 2022
 *      Author: xanlo
 */


#include "global.h"

int status = 0;
int start = 0;
int index_mode = 0;

int CURRENT_STATE[2] = {0, 2};
int SEG7_CLOCK[2] = {5000, 2000};
int led_seg_buffer[4] = {0};
int LED_TIME[3] = {5000, 2000, 3000};
int TIMES_INC = 0;


