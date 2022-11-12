/*
 * seg7_handle.c
 *
 *  Created on: 12 Nov 2022
 *      Author: xanlo
 */

#include "seg7_handle.h"
#include "main.h"
#include "global.h"

static uint8_t led7seg[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void led_init() {
	GPIOB->BSRR = 0x3F00;
}

void led_clear() {
	HAL_GPIO_WritePin(GPIOA, D1_Pin | D2_Pin | D3_Pin | D4_Pin | D5_Pin | D6_Pin, 1);
}


void display7SEG(int num) {
	for (int i = 0; i < 7; i++) {
		HAL_GPIO_WritePin(GPIOB , GPIO_PIN_0 << i, (led7seg[num] >> i) & 1);
	}
}

void update_buffer() {
	led_seg_buffer[0] = (SEG7_CLOCK[0] - TIME_UNIT) / (10*TIME_UNIT);
	led_seg_buffer[1] = ((SEG7_CLOCK[0] - TIME_UNIT) % (10*TIME_UNIT))/TIME_UNIT;
	led_seg_buffer[2] = (SEG7_CLOCK[1]  - TIME_UNIT) / (10*TIME_UNIT);
	led_seg_buffer[3] = ((SEG7_CLOCK[1]  - TIME_UNIT) % (10*TIME_UNIT))/TIME_UNIT;
}

void update_buffer_no() {
	led_seg_buffer[0] = SEG7_CLOCK[0] / (10*TIME_UNIT);
	led_seg_buffer[1] = (SEG7_CLOCK[0] % (10*TIME_UNIT))/TIME_UNIT;
	led_seg_buffer[2] = SEG7_CLOCK[1] / (10*TIME_UNIT);
	led_seg_buffer[3] = (SEG7_CLOCK[1] % (10*TIME_UNIT))/TIME_UNIT;
}


void update7SEG(int index){
	switch(index) {
		case 0:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, ON_7SEG); // turn on the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, OFF_7SEG); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, OFF_7SEG); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, OFF_7SEG); // turn off the fourth SEG
			display7SEG(led_seg_buffer[0]);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, OFF_7SEG); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, ON_7SEG); // turn on the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, OFF_7SEG); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, OFF_7SEG); // turn off the fourth SEG
			display7SEG(led_seg_buffer[1]);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, OFF_7SEG); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, OFF_7SEG); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, ON_7SEG); // turn on the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, OFF_7SEG); // turn off the fourth SEG
			display7SEG(led_seg_buffer[2]);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOA, EN0_Pin, OFF_7SEG); // turn off the first SEG
			HAL_GPIO_WritePin(GPIOA, EN1_Pin, OFF_7SEG); // turn off the second SEG
			HAL_GPIO_WritePin(GPIOA, EN2_Pin, OFF_7SEG); // turn off the third SEG
			HAL_GPIO_WritePin(GPIOA, EN3_Pin, ON_7SEG); // turn on the fourth SEG
			display7SEG(led_seg_buffer[3]);
			break;
		default:
			break;
	}
}

