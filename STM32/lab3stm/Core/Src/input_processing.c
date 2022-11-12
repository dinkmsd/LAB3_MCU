/*
 * input_processing.c
 *
 *  Created on: Nov 3, 2022
 *      Author: xanlo
 */


#include "main.h"
#include "input_reading.h"
#include "global.h"
#include "software_timer.h"
#include "seg7_handle.h"

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState = BUTTON_RELEASED;

int WhichButtonIsPressed() {
	if (is_button_pressed(0)) return 1;
	if (is_button_pressed(1)) return 2;
	if (is_button_pressed(2)) return 3;

	return 0; // None of these buttons are pressed
}

void clear_vertical() {
	HAL_GPIO_WritePin(GPIOB, D1_Pin | D2_Pin | D3_Pin, GPIO_PIN_SET);
}

void clear_horizontal() {
	HAL_GPIO_WritePin(GPIOB, D4_Pin | D5_Pin | D6_Pin, GPIO_PIN_SET);
}

void vertical_processing() {
	clear_vertical();
	switch (CURRENT_STATE[0]) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, D1_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, D2_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, D3_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void horizontal_processing() {
	clear_horizontal();
	switch (CURRENT_STATE[1]) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, D4_Pin, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, D5_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, D6_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void state_update(int idx) {
	if (idx == 0) {
		CURRENT_STATE[idx] = (CURRENT_STATE[idx] + 1) % 3;
	} else {
		CURRENT_STATE[idx] = (CURRENT_STATE[idx] - 1 + 3) % 3;
	}
	SEG7_CLOCK[idx] = LED_TIME[CURRENT_STATE[idx]];
}

void check_state() {
	if (SEG7_CLOCK[0] <= 0) {
		state_update(0);
		vertical_processing();
	}

	if (SEG7_CLOCK[1] <= 0) {
		state_update(1);
		horizontal_processing();
	}
}

void update_clock() {
	if (timer2_flag == 1) {
		SEG7_CLOCK[0] = SEG7_CLOCK[0] - 1000;
		SEG7_CLOCK[1] = SEG7_CLOCK[1] - 1000;
		check_state();
		update_buffer();
		setTimer2(1000);
	}
}

void reset() {
	LED_TIME[0] = 5000;
	LED_TIME[1] = 2000;
	LED_TIME[2] = 3000;
	CURRENT_STATE[0] = 0;
	CURRENT_STATE[1] = 2;
	SEG7_CLOCK[0] = LED_TIME[CURRENT_STATE[0]];
	SEG7_CLOCK[1] = LED_TIME[CURRENT_STATE[1]];
}

void restart(){
	status = 0;
}

void confirm_action(int mode) {
	switch (mode) {
	case 0: //Normal mode -> do nothing
		return;
	case 1: // Inc red time mode
		LED_TIME[0] = LED_TIME[0] + (TIMES_INC * TIME_UNIT);
		LED_TIME [2] = LED_TIME[2] + (TIMES_INC * TIME_UNIT);
		break;
	case 2: // Inc yellow time mode
		LED_TIME[0] = LED_TIME[0] + (TIMES_INC * TIME_UNIT);
		LED_TIME[1] = LED_TIME[1] + (TIMES_INC * TIME_UNIT);
		break;
	case 3: // Inc green time
		LED_TIME[0] = LED_TIME[0] + (TIMES_INC * TIME_UNIT);
		LED_TIME [2] = LED_TIME[2] + (TIMES_INC * TIME_UNIT);
		break;
	default:
		break;
	}
	HAL_GPIO_TogglePin(GPIOB, TEST_Pin);

}

void state_handle() {
	switch (index_mode) {
	case 0:
		SEG7_CLOCK[0] = 0;
		SEG7_CLOCK[1] = 0;
		break;
	case 1:
		SEG7_CLOCK[0] = 1 * TIME_UNIT;
		SEG7_CLOCK[1] = LED_TIME[0] + TIMES_INC * TIME_UNIT;
		break;
	case 2:
		SEG7_CLOCK[0] = 2  * TIME_UNIT;
		SEG7_CLOCK[1] = LED_TIME[1] + TIMES_INC * TIME_UNIT;
		break;
	case 3:
		SEG7_CLOCK[0] = 3  * TIME_UNIT;
		SEG7_CLOCK[1] = LED_TIME[2] + TIMES_INC * TIME_UNIT;
	default:
		break;
	}
	update_buffer_no();
}

void traffic_processing() {
	switch (status) {
	case 0:
		CURRENT_STATE[0] = 0;
		CURRENT_STATE[1] = 2;
		SEG7_CLOCK[0] = LED_TIME[CURRENT_STATE[0]];
		SEG7_CLOCK[1] = LED_TIME[CURRENT_STATE[1]];
		update_buffer();
		vertical_processing();
		horizontal_processing();
		status = 1;
		break;
	case 1:
		update_clock();
		break;
	case 2:
		state_handle();
		break;
	default:
		break;
	}
}

void input_processing() {
	// Switch button
	if (is_button_pressed(0)) {
		status = 2;
		index_mode = (index_mode + 1) % 4;
		TIMES_INC = 0;
	}

	// Add button
	if (is_button_pressed(1) && index_mode != 0) {
		TIMES_INC++;
	}

	// Confirm button
	if (is_button_pressed(2) && index_mode != 0) {
		if (TIMES_INC != 0) {
			confirm_action(index_mode);
		}
		TIMES_INC = 0;
		index_mode = 0;
		restart();
	}

	// Reset button
	if (start == 0) {
		reset();
		start = 1;
	}
}

void fsm_simple_button_run() {
	switch (buttonState) {
	case BUTTON_RELEASED:
		if (WhichButtonIsPressed()) {
			buttonState = BUTTON_PRESSED;
			HAL_GPIO_TogglePin(GPIOB, TEST_Pin);

			input_processing();
		}
	case BUTTON_PRESSED:
		if (!WhichButtonIsPressed()) {
			buttonState = BUTTON_RELEASED;
		}
	default:
		break;
	}
}
